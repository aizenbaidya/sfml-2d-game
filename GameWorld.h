#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "GameTile.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief This class represents the game world as a collection of game tiles.
 *
 * It loads the map from a text file and updates the view based on the player's position.
 */
class GameWorld : public sf::Drawable {
public:
	GameWorld(const std::string& mapFile);

	static constexpr int MAP_TILE_ROWS = 32;
	static constexpr int MAP_TILE_COLS = 32;

	static constexpr int MAP_HEIGHT = GameTile::SCALED_TILE_SIZE * MAP_TILE_ROWS;
	static constexpr int MAP_WIDTH = GameTile::SCALED_TILE_SIZE * MAP_TILE_COLS;

	void updateView(const sf::Vector2f& playerPosition);
	sf::View& getView();

private:
	std::vector<std::vector<GameTile>> tiles;
	sf::Texture grassTexture;
	sf::Texture waterTexture;
	sf::View view;

	bool loadTextures();
	void loadMap(const std::string& mapFile);
	std::pair<sf::IntRect, const sf::Texture*> getTextureRectAndTexture(int tileNumber) const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif