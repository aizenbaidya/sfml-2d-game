#include "GameDriver.h"
#include "GameWorld.h"
#include <fstream>
#include <iostream>

GameWorld::GameWorld(const std::string& mapFile) : view(sf::FloatRect(0, 0, GameDriver::WINDOW_WIDTH, GameDriver::WINDOW_HEIGHT)) {
	if (!loadTextures()) {
		std::cerr << "The textures failed to load!" << std::endl;
		return;
	}
	loadMap(mapFile);

	view.setSize(GameDriver::WINDOW_WIDTH, GameDriver::WINDOW_HEIGHT);
	view.setCenter(GameDriver::WINDOW_WIDTH / 2.0f, GameDriver::WINDOW_HEIGHT / 2.0f);
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

	// Row to hold tiles temporarily
	std::vector<GameTile> row;

	// Read each tile number from the file
	while (file >> tileNumber) {
		sf::IntRect textureRect;
		const sf::Texture* texture = nullptr;

		// Get texture rectangle and texture for the current tile number
		std::tie(textureRect, texture) = getTextureRectAndTexture(tileNumber);

		if (texture) {
			row.emplace_back(*texture, textureRect, sf::Vector2f(static_cast<float>(x * GameTile::SCALED_TILE_SIZE),
				static_cast<float>(y * GameTile::SCALED_TILE_SIZE)));
		}
		x++;

		// Reached the end of the row
		if (file.peek() == '\n') {
			tiles.push_back(row);
			row.clear();
			x = 0;
			y++;
		}
	}

	// Add any remaining tiles in the last row
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
	target.setView(view);

	for (const auto& row : tiles) {
		for (const auto& tile : row) {
			target.draw(tile);
		}
	}
}

void GameWorld::updateView(const sf::Vector2f& playerPosition) {
	const float VIEW_HALF_WIDTH = view.getSize().x / 2.0f;
	const float VIEW_HALF_HEIGHT = view.getSize().y / 2.0f;

	const int MAP_WIDTH = MAP_TILE_COLS * GameTile::SCALED_TILE_SIZE;
	const int MAP_HEIGHT = MAP_TILE_ROWS * GameTile::SCALED_TILE_SIZE;

	const float PLAYER_OFFSET = Player::SCALED_PLAYER_SIZE / 2.0f;

	// View center coordinates clamped within the map boundaries
	const float VIEW_CENTER_X = std::max(VIEW_HALF_WIDTH, std::min(playerPosition.x + PLAYER_OFFSET, MAP_WIDTH - VIEW_HALF_WIDTH));
	const float VIEW_CENTER_Y = std::max(VIEW_HALF_HEIGHT, std::min(playerPosition.y + PLAYER_OFFSET, MAP_HEIGHT - VIEW_HALF_HEIGHT));

	view.setCenter(VIEW_CENTER_X, VIEW_CENTER_Y);
}

sf::View& GameWorld::getView() {
	return view;
}