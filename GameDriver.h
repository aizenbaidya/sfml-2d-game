#ifndef GAMEDRIVER_H
#define GAMEDRIVER_H

#include "Player.h"
#include "GameWorld.h"
#include <SFML/Graphics.hpp>

class GameDriver {
public:
	static const int WINDOW_WIDTH = 768;
	static const int WINDOW_HEIGHT = 576;

	static void run();
};

#endif