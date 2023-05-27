#include "TilemapManager.h"

#include "WallTile.h"
#include "FloorTile.h"
#include "BackgroundTile.h"
#include "EndTile.h"
#include "BoxTile.h"
#include "SpawnPoint.h"
#include "TilemapConfig.h"
#include "EntityManager.h"

TilemapManager* TilemapManager::instance;

TilemapManager::TilemapManager()
{
    defaultMapPath = "Assets/Levels/default.map";
}

void TilemapManager::DrawBoundaries()
{
    for (int y = 0; y <= TilemapConfig::yTileNumber; y++)
    {
        EntityManager::GetInstance()->AddGameObject(std::make_unique<WallTile>(GetTilePosition(-1, y - 1)));
    }
    for (int y = 0; y <= TilemapConfig::yTileNumber; y++)
    {
        EntityManager::GetInstance()->AddGameObject(std::make_unique<WallTile>(GetTilePosition(TilemapConfig::xTileNumber, y - 1)));
    }
    for (int x = 0; x <= TilemapConfig::xTileNumber; x++)
    {
        EntityManager::GetInstance()->AddGameObject(std::make_unique<WallTile>(GetTilePosition(x - 1, -1)));
    }
    for (int x = 0; x <= TilemapConfig::xTileNumber + 1; x++)
    {
        EntityManager::GetInstance()->AddGameObject(std::make_unique<WallTile>(GetTilePosition(x - 1, TilemapConfig::yTileNumber)));
    }
}

void TilemapManager::DrawBackground()
{
    int xTiles = std::ceil(TilemapConfig::screenWidth / TilemapConfig::tileSize);
    int yTiles = std::ceil(TilemapConfig::screenHeight / TilemapConfig::tileSize);

    //To avoid placing background tiles where the tilemap and its boundary is going to be
    int yGapStart = std::floor(yTiles - TilemapConfig::yTileNumber - 1) * 0.5f;
    int yGapEnd = yTiles - yGapStart;
    int xGapStart = std::floor(xTiles - TilemapConfig::xTileNumber - 1) * 0.5f;
    int xGapEnd = xTiles - xGapStart;

    float xDiff = (float)TilemapConfig::xTilemapOffset / TilemapConfig::tileSize - (int)(TilemapConfig::xTilemapOffset / TilemapConfig::tileSize);
    float yDiff = (float)TilemapConfig::yTilemapOffset / TilemapConfig::tileSize - (int)(TilemapConfig::yTilemapOffset / TilemapConfig::tileSize);

    glm::vec2 offset = glm::vec2(xDiff > 0 ? TilemapConfig::tileSize * xDiff - TilemapConfig::tileSize * 0.5f : TilemapConfig::tileSize * 0.5f,
        yDiff > 0 ? TilemapConfig::tileSize * yDiff - TilemapConfig::tileSize * 0.5f : TilemapConfig::tileSize * 0.5f);

    for (int y = 0; y <= yTiles; y++)
    {
        for (int x = 0; x <= xTiles; x++)
        {
            if (y >= yGapStart && y < yGapEnd && x >= xGapStart && x < xGapEnd)
                continue;
          
            EntityManager::GetInstance()->AddGameObject(
                std::make_unique<BackgroundTile>(glm::vec2(TilemapConfig::tileSize * x, TilemapConfig::tileSize * y) + offset,
                TilemapConfig::tileSize));
        }
    }
}

void TilemapManager::DrawFloor()
{
    for (int y = 0; y < TilemapConfig::yTileNumber; y++)
    {
        std::vector<char> row;
        std::vector<GameObject*> objRow;

        for (int x = 0; x < TilemapConfig::xTileNumber; x++)
        {
            std::unique_ptr<GameObject> tile = std::make_unique<FloorTile>(GetTilePosition(x, y));
            objRow.emplace_back(tile.get());
            EntityManager::GetInstance()->AddGameObject(std::move(tile));
            row.emplace_back('F');
        }

        currentTilemap.emplace_back(row);
        tilemapObjects.emplace_back(objRow);
    }
}

void TilemapManager::Clear()
{
    currentTilemap.clear();
    tilemapObjects.clear();
}

void TilemapManager::DrawBaseTilemap()
{
    Clear();
    DrawBoundaries();
    DrawFloor();
}

/* Fills in the tilemap at the end of the match with the tiles moving like this:
*  ---->
*  ^-->|
*  |  ||
*  |<-vv
*  <----
*/
void TilemapManager::FillIn()
{
    switch (currentDir)
    {
    case CloseInDirection::LEFT:
        EntityManager::GetInstance()->AddGameObject(std::make_unique<EndTile>(GetTilePosition(xFillId, yFillId)));
        if (xFillId == xFillLoops)
        {
            currentDir = CloseInDirection::UP;
            xFillLoops++;
            yFillId--;
        }
        else
        {
            xFillId--;
        }
        break;
    case CloseInDirection::RIGHT:
        EntityManager::GetInstance()->AddGameObject(std::make_unique<EndTile>(GetTilePosition(xFillId, yFillId)));
        if (xFillId == TilemapConfig::xTileNumber - xFillLoops - 1)
        {
            currentDir = CloseInDirection::DOWN;
            yFillId++;
        }
        else
        {
            xFillId++;
        }
        break;
    case CloseInDirection::UP:
        EntityManager::GetInstance()->AddGameObject(std::make_unique<EndTile>(GetTilePosition(xFillId, yFillId)));
        if (yFillId == yFillLoops + 1)
        {
            currentDir = CloseInDirection::RIGHT;
            yFillLoops++;
            xFillId++;
        }
        else
        {
            yFillId--;
        }
        break;
    case CloseInDirection::DOWN:
        EntityManager::GetInstance()->AddGameObject(std::make_unique<EndTile>(GetTilePosition(xFillId, yFillId)));
        if (yFillId == TilemapConfig::yTileNumber - yFillLoops - 1)
        {
            currentDir = CloseInDirection::LEFT;
            xFillId--;
        }
        else
        {
            yFillId++;
        }
        break;
    }
}

bool TilemapManager::IsValidPosition(glm::vec2 mousePos)
{
    glm::vec2 lowerBoundary = GetTilePosition(0, 0) - glm::vec2(TilemapConfig::tileSize * 0.5f, TilemapConfig::tileSize * 0.5f);
    glm::vec2 upperBoundary = GetTilePosition(TilemapConfig::xTileNumber - 1, TilemapConfig::yTileNumber - 1) + glm::vec2(TilemapConfig::tileSize * 0.5f, TilemapConfig::tileSize * 0.5f);
    return mousePos.x >= lowerBoundary.x && mousePos.x <= upperBoundary.x && mousePos.y >= lowerBoundary.y && mousePos.y <= upperBoundary.y;
}

bool TilemapManager::Save(const std::string& mapTitle)
{
    if (IsValidTilemap(currentTilemap))
    {
        SaveFile(mapTitle);
        return true;
    }
    return false;
}

std::vector<std::vector<char>> TilemapManager::ReadFile(const std::string& filePath)
{
    std::vector<std::vector<char>> tilemap;
    std::fstream file(filePath);
    std::string line;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::vector<char> row;
            for (const auto& c : line)
            {
                row.push_back(c);
            }
            tilemap.push_back(row);
        }
        file.close();
    }
    return tilemap;
}

void TilemapManager::SaveFile(const std::string& mapTitle)
{
    std::ofstream file;
    file.open("Assets/Levels/Custom/" + mapTitle + ".map");
    if (file.is_open())
    {
        for (int i = 0; i < currentTilemap.size(); i++)
        {
            for (int j = 0; j < currentTilemap[i].size(); j++)
            {
                file << currentTilemap[i][j];
            }
            file << '\n';
        }
        file.close();
    }
}

bool TilemapManager::IsValidTilemap(std::vector<std::vector<char>> tilemap)
{
    if (tilemap.size() != TilemapConfig::yTileNumber)
    {
        return false;
    }

    int p1SpawnPoints = 0;
    int p2SpawnPoints = 0;

    for (int y = 0; y < tilemap.size(); y++)
    {
        for (int x = 0; x < tilemap[y].size(); x++)
        {
            if (tilemap[y].size() != TilemapConfig::xTileNumber)
            {
                return false;
            }
            if (tilemap[y][x] == '1')
            {
                p1SpawnPoints++;
                if (p1SpawnPoints > 1)
                {
                    return false;
                }
            }
            else if (tilemap[y][x] == '2')
            {
                p2SpawnPoints++;
                if (p2SpawnPoints > 1)
                {
                    return false;
                }
            }
            else if (tilemap[y][x] != 'W' && tilemap[y][x] != 'F' && tilemap[y][x] != 'B')
            {
                return false;
            }
        }
    }
    return p1SpawnPoints == 1 && p2SpawnPoints == 1;
}

glm::vec2 TilemapManager::GetTilePosition(int xId, int yId)
{
    return glm::vec2(glm::vec2(xId * TilemapConfig::tileSize + TilemapConfig::tileSize * 0.5f,
        yId * TilemapConfig::tileSize + TilemapConfig::tileSize * 0.5f)
        + glm::vec2(TilemapConfig::xTilemapOffset, TilemapConfig::yTilemapOffset));
}

TilemapManager* TilemapManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new TilemapManager();
    }
    return instance;
}

void TilemapManager::SelectTile(TileType tileType)
{
    selectedTile = tileType;
}

void TilemapManager::PlaceTile(glm::vec2 pos)
{
    int x = (pos.x - TilemapConfig::xTilemapOffset) / TilemapConfig::tileSize;
    int y = (pos.y - TilemapConfig::yTilemapOffset) / TilemapConfig::tileSize;
    EntityManager::GetInstance()->RemoveGameObject(tilemapObjects[y][x]);
    pos = GetTilePosition(x, y);

    switch (selectedTile)
    {
        case TileType::BOX:
        {
            std::unique_ptr<GameObject> tile = std::make_unique<BoxTile>(pos);
            tilemapObjects[y][x] = tile.get();
            EntityManager::GetInstance()->AddGameObject(std::move(tile));
            SaveTile('B', pos);
            break;
        }
        case TileType::FLOOR:
        {
            std::unique_ptr<GameObject> tile = std::make_unique<FloorTile>(pos);
            tilemapObjects[y][x] = tile.get();
            EntityManager::GetInstance()->AddGameObject(std::move(tile));
            SaveTile('F', pos);
            break;
        }
        case TileType::WALL:
        {
            std::unique_ptr<GameObject> tile = std::make_unique<WallTile>(pos);
            tilemapObjects[y][x] = tile.get();
            EntityManager::GetInstance()->AddGameObject(std::move(tile));
            SaveTile('W', pos);
            break;
        }
        case TileType::SPAWN_POINT_P1:
        {
            std::unique_ptr<GameObject> tile = std::make_unique<SpawnPoint>(pos, 1);
            tilemapObjects[y][x] = tile.get();
            EntityManager::GetInstance()->AddGameObject(std::move(tile));
            SaveTile('1', pos);
            break;
        }
        case TileType::SPAWN_POINT_P2:
        {
            std::unique_ptr<GameObject> tile = std::make_unique<SpawnPoint>(pos, 2);
            tilemapObjects[y][x] = tile.get();
            EntityManager::GetInstance()->AddGameObject(std::move(tile));
            SaveTile('2', pos);
            break;
        }
    }
}

std::array<glm::vec2, 2> TilemapManager::GetStartPoints()
{
    return playerStartPoints;
}

void TilemapManager::SaveTile(char tileType, glm::vec2 pos)
{
    int x = (pos.y - TilemapConfig::yTilemapOffset) / TilemapConfig::tileSize;
    int y = (pos.x - TilemapConfig::xTilemapOffset) / TilemapConfig::tileSize;
    currentTilemap[x][y] = tileType;
}

void TilemapManager::LoadTilemapEditor(std::vector<std::vector<char>> tilemap)
{
    for (int y = 0; y < TilemapConfig::yTileNumber; y++)
    {
        std::vector<GameObject*> row;
        for (int x = 0; x < TilemapConfig::xTileNumber; x++)
        {
            std::unique_ptr<GameObject> tile;
            switch (tilemap[y][x])
            {
            case 'W':
                tile = std::make_unique<WallTile>(GetTilePosition(x, y));
                row.emplace_back(tile.get());
                EntityManager::GetInstance()->AddGameObject(std::move(tile));
                break;
            case 'F':
                tile = std::make_unique<FloorTile>(GetTilePosition(x, y));
                row.emplace_back(tile.get());
                EntityManager::GetInstance()->AddGameObject(std::move(tile));
                break;
            case 'B':
                tile = std::make_unique<BoxTile>(GetTilePosition(x, y));
                row.emplace_back(tile.get());
                EntityManager::GetInstance()->AddGameObject(std::move(tile));
                break;
            case '1':
                tile = std::make_unique<FloorTile>(GetTilePosition(x, y));
                row.emplace_back(tile.get());
                EntityManager::GetInstance()->AddGameObject(std::move(tile));
                EntityManager::GetInstance()->AddGameObject(std::make_unique<SpawnPoint>(GetTilePosition(x, y), 1));
                break;
            case '2':
                tile = std::make_unique<FloorTile>(GetTilePosition(x, y));
                row.emplace_back(tile.get());
                EntityManager::GetInstance()->AddGameObject(std::move(tile));
                EntityManager::GetInstance()->AddGameObject(std::make_unique<SpawnPoint>(GetTilePosition(x, y), 2));
                break;
            }
        }
        tilemapObjects.emplace_back(row);
    }
    currentTilemap = tilemap;
    DrawBoundaries();
}

void TilemapManager::LoadTilemapGameplay(std::vector<std::vector<char>> tilemap)
{
    DrawBackground();
    for (int y = 0; y < TilemapConfig::yTileNumber; y++)
    {
        for (int x = 0; x < TilemapConfig::xTileNumber; x++)
        {
            switch (tilemap[y][x])
            {
            case 'W':
                EntityManager::GetInstance()->AddGameObject(std::make_unique<WallTile>(GetTilePosition(x, y)));
                break;
            case 'F':
                EntityManager::GetInstance()->AddGameObject(std::make_unique<FloorTile>(GetTilePosition(x, y)));
                break;
            case 'B':
                EntityManager::GetInstance()->AddGameObject(std::make_unique<FloorTile>(GetTilePosition(x, y)));
                EntityManager::GetInstance()->AddGameObject(std::make_unique<BoxTile>(GetTilePosition(x, y)));
                break;
            case '1':
                playerStartPoints[0] = GetTilePosition(x, y);
                EntityManager::GetInstance()->AddGameObject(std::make_unique<FloorTile>(GetTilePosition(x, y)));
                break;
            case '2':
                playerStartPoints[1] = GetTilePosition(x, y);
                EntityManager::GetInstance()->AddGameObject(std::make_unique<FloorTile>(GetTilePosition(x, y)));
                break;
            }
        }
    }
    currentTilemap = tilemap;
    DrawBoundaries();
}

bool TilemapManager::PlayInCustomTilemap(const std::string& tilemapName)
{
    std::string filePath = "Assets/Levels/Custom/" + tilemapName + ".map";
    std::vector<std::vector<char>> tilemap = ReadFile(filePath);
    if (IsValidTilemap(tilemap))
    {
        PlayInTilemap(filePath);
        return true;
    }
    return false;
}

void TilemapManager::OpenEditor()
{
    DrawBaseTilemap();
    Notify(Event::OPEN_EDITOR);
}

void TilemapManager::ReloadTilemap()
{
    EntityManager::GetInstance()->RemoveAllGameObjects();
    DrawBaseTilemap();
}

void TilemapManager::PlayInDefaultTilemap()
{
    PlayInTilemap(defaultMapPath);
}

bool TilemapManager::EditTilemap(const std::string& filePath)
{
    std::vector<std::vector<char>> tilemap = ReadFile(filePath);
    if (IsValidTilemap(tilemap))
    {
        LoadTilemapEditor(tilemap);
        return true;
    }
    return false;
}

void TilemapManager::PlayInTilemap(const std::string& tilemapPath)
{
    xFillId = 0;
    yFillId = 0;
    xFillLoops = 0;
    yFillLoops = 0;
    currentDir = CloseInDirection::RIGHT;
    currentMapPath = tilemapPath;

    std::vector<std::vector<char>> tilemap = ReadFile(tilemapPath);
    LoadTilemapGameplay(tilemap);
    Notify(Event::START_GAME);
}

void TilemapManager::Replay()
{
    if (currentMapPath != defaultMapPath)
    {
        std::string mapTitle = currentMapPath;
        mapTitle = currentMapPath.substr(currentMapPath.find_last_of("/") + 1);
        mapTitle = mapTitle.substr(mapTitle.find_last_of("\\") + 1);
        mapTitle = mapTitle.substr(0, mapTitle.size() - 4);
        PlayInCustomTilemap(mapTitle);
    }
    else
    {
        PlayInDefaultTilemap();
    }
    Notify(Event::START_GAME);
}
