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

	glm::vec2 GetTilePosition(int xId, int yId);
	void PlayInTilemap(const std::string& tilemapPath);

	void DrawFloor();
	void DrawBoundaries();
	void DrawBackground();
	void DrawBaseTilemap(); //Used when editing tilemaps

	bool IsValidTilemap(std::vector<std::vector<char>> tilemap);
	std::vector<std::vector<char>> ReadFile(const std::string& filePath);

	void LoadTilemapEditor(std::vector<std::vector<char>> tilemap);
	void LoadTilemapGameplay(std::vector<std::vector<char>> tilemap);

	void SaveTile(char tileType, glm::vec2 pos);
	void SaveFile(const std::string& mapTitle);
public:
	static TilemapManager* GetInstance();
	TilemapManager(TilemapManager&) = delete;
	void operator=(const TilemapManager&) = delete;

	bool PlayInCustomTilemap(const std::string& tilemapName);
	void Replay();
	void PlayInDefaultTilemap();
	void FillIn();
	std::array<glm::vec2, 2> GetStartPoints();

	void ReloadTilemap();
	void OpenEditor();
	bool EditTilemap(const std::string& filePath);
	bool Save(const std::string& mapTitle);
	void SelectTile(TileType tileType);
	void PlaceTile(glm::vec2 pos);
	bool IsValidPosition(glm::vec2 mousePos);

	void Clear();
};

