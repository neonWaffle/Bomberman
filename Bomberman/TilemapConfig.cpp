#include "TilemapConfig.h"

const int TilemapConfig::tileSize = 60;
const int TilemapConfig::xTileNumber = 19;
const int TilemapConfig::yTileNumber = 13;
const float TilemapConfig::xTilemapOffset = (TilemapConfig::screenWidth / TilemapConfig::tileSize - TilemapConfig::xTileNumber) * 0.5f * TilemapConfig::tileSize;
const float TilemapConfig::yTilemapOffset = (TilemapConfig::screenHeight / TilemapConfig::tileSize - TilemapConfig::yTileNumber) * 0.5f * TilemapConfig::tileSize;
const int TilemapConfig::screenWidth = 1920;
const int TilemapConfig::screenHeight = 1080;