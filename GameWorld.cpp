#include "GameWorld.h"
#include <iostream>
#include <fstream>

const float GameWorld::SCALE = 3.0f;

GameWorld::GameWorld(const std::string& mapFile) {
	if (!loadTextures()) {
		std::cerr << "The textures failed to load!" << std::endl;
		return;
	}
	loadMap(mapFile);
}

bool GameWorld::loadTextures() {
	if (!grassTexture.loadFromFile("assets/Grass-Tileset.png")) {
		std::cerr << "The grass tile set failed to load!" << std::endl;
		return false;
	}

	if (!waterTexture.loadFromFile("assets/Water-Tileset.png")) {
		std::cerr << "The water tile set failed to load!" << std::endl;
		return false;
	}

	return true;
}

void GameWorld::loadMap(const std::string& mapFile) {
	std::ifstream file(mapFile);
	if (!file.is_open()) {
		std::cerr << "The map file failed to open!" << std::endl;
		return;
	}

	int tileNumber;
	int x = 0, y = 0;
	std::vector<GameTile> row;

	while (file >> tileNumber) {
		sf::IntRect textureRect;
		const sf::Texture* texture = nullptr;

		std::tie(textureRect, texture) = getTextureRectAndTexture(tileNumber);

		if (texture) {
			row.emplace_back(*texture, textureRect, sf::Vector2f(x * TILE_SIZE * SCALE, y * TILE_SIZE * SCALE));
		}
		x++;

		if (file.peek() == '\n') {
			tiles.push_back(row);
			row.clear();
			x = 0;
			y++;
		}
	}

	if (!row.empty()) {
		tiles.push_back(row);
	}

	file.close();
}

std::pair<sf::IntRect, const sf::Texture*> GameWorld::getTextureRectAndTexture(int tileNumber) const {
	switch (tileNumber) {
	case 0:
		return { sf::IntRect(0, 80, 16, 16), &grassTexture };
	case 1:
		return { sf::IntRect(0, 0, 16, 16), &waterTexture };
	default:
		return {};
	}
}

void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const auto& row : tiles) {
		for (const auto& tile : row) {
			target.draw(tile);
		}
	}
}