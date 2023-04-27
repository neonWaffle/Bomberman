#pragma once
#include "Subject.h"
#include <unordered_map>
#include <memory>
#include <fstream>
#include <glm.hpp>

enum class TileType { WALL, FLOOR, BOX, SPAWN_POINT_P1, SPAWN_POINT_P2 };

class TilemapManager : public Subject
{
private:
	static TilemapManager* instance;
	TileType selectedTile;
	std::vector<std::vector<char>> currentTilemap;
	std::vector<std::vector<GameObject*>> tilemapObjects;
	int xFillId;
	int yFillId;
	int xFillLoops;
	int yFillLoops;
	enum class CloseInDirection { LEFT, RIGHT, UP, DOWN };
	CloseInDirection currentDir;
	std::array<glm::vec2, 2> playerStartPoints;
	std::string currentMapPath; //Used for restarting the level
	std::string defaultMapPath;
	TilemapManager();
	std::vector<std::vector<char>> ReadFile(std::string filePath);
	glm::vec2 GetTilePosition(int xId, int yId);
	void DrawBoundaries();
	void DrawBackground();
	bool IsValidTilemap(std::vector<std::vector<char>> tilemap);
	void SaveFile(std::string mapTitle);
	void DrawFloor();
	void SaveTile(char tileType, glm::vec2 pos);
	void PlayInTilemap(std::string tilemapPath);
	void DrawBaseTilemap(); //Used when editing tilemaps
	void LoadTilemapEditor(std::vector<std::vector<char>> tilemap);
	void LoadTilemapGameplay(std::vector<std::vector<char>> tilemap);
public:
	static TilemapManager* GetInstance();
	TilemapManager(TilemapManager& other) = delete;
	void operator=(const TilemapManager&) = delete;
	void FillIn();
	void SelectTile(TileType tileType);
	void PlaceTile(glm::vec2 pos);
	std::array<glm::vec2, 2> GetStartPoints();
	bool PlayInCustomTilemap(std::string tilemapName);
	void OpenEditor();
	void ReloadTilemap();
	void PlayInDefaultTilemap();
	void Replay();
	bool IsValidPosition(glm::vec2 mousePos);
	bool Save(std::string mapTitle);
	bool EditTilemap(std::string filePath);
	void Clear();
};


/*#pragma once
#include "Subject.h"
#include <unordered_map>
#include <memory>
#include <fstream>
#include <glm.hpp>

enum class TileType { WALL, FLOOR, BOX, SPAWN_POINT_P1, SPAWN_POINT_P2 };

class TilemapManager : public Subject
{
private:
	static TilemapManager* instance;
	TileType selectedTile;
	std::vector<std::vector<char>> currentTilemap;
	std::vector<std::vector<GameObject*>> tilemapObjects;
	int xFillId;
	int yFillId;
	int xFillLoops;
	int yFillLoops;
	enum class CloseInDirection { LEFT, RIGHT, UP, DOWN };
	CloseInDirection currentDir;
	std::array<glm::vec2, 2> playerStartPoints;
	std::string currentMapName; //Used for restarting the level
	std::string defaultMapPath;
	TilemapManager();
	std::vector<std::vector<char>> ReadFile(std::string filePath);
	void LoadTilemap(std::vector<std::vector<char>> tilemap, bool inEditor);
	glm::vec2 GetTilePosition(int xId, int yId);
	void DrawBoundaries();
	void DrawBackground();
	bool IsValidTilemap(std::vector<std::vector<char>> tilemap);
	void SaveFile(std::string mapTitle);
	void DrawFloor();
	void SaveTile(char tileType, glm::vec2 pos);
	void PlayInTilemap(std::string tilemapPath);
	void DrawBaseTilemap(); //Used when editing tilemaps
public:
	static TilemapManager* GetInstance();
	TilemapManager(TilemapManager& other) = delete;
	void operator=(const TilemapManager&) = delete;
	void FillIn();
	void SelectTile(TileType tileType);
	void PlaceTile(glm::vec2 pos);
	std::array<glm::vec2, 2> GetStartPoints();
	bool PlayCustomTilemap(std::string tilemapName);
	void OpenEditor();
	void ReloadTilemap();
	void PlayDefaultTilemap();
	void Replay();
	bool IsValidPosition(glm::vec2 mousePos);
	bool Save(std::string mapTitle);
	bool EditTilemap(std::string filePath);
	void Clear();
};*/