#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "GameTile.h"
#include <vector>
#include <string>
#include <utility>

class GameWorld : public sf::Drawable {
public:
	GameWorld(const std::string& mapFile);

	static const int TILE_SIZE = 16;
	static const float SCALE;

private:
	std::vector<std::vector<GameTile>> tiles;
	sf::Texture grassTexture;
	sf::Texture waterTexture;

	bool loadTextures();
	void loadMap(const std::string& mapFile);
	std::pair<sf::IntRect, const sf::Texture*> getTextureRectAndTexture(int tileNumber) const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif