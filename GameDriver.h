#ifndef GAMEDRIVER_H
#define GAMEDRIVER_H

#include "GameWorld.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

/**
 * @brief Responsible for managing the main game loop
 */
class GameDriver {
public:
	static const int WINDOW_NUM_ROWS = 12;
	static const int WINDOW_NUM_COLS = 16;

	static const int WINDOW_WIDTH = WINDOW_NUM_COLS * GameTile::SCALED_TILE_SIZE;
	static const int WINDOW_HEIGHT = WINDOW_NUM_ROWS * GameTile::SCALED_TILE_SIZE;

	static void run();
};

#endif