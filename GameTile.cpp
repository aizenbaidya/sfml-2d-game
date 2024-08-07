#include "GameTile.h"

GameTile::GameTile(const sf::Texture& texture, sf::IntRect textureRect, sf::Vector2f position) {
	sprite.setTexture(texture);
	sprite.setTextureRect(textureRect);
	sprite.setPosition(position);
	sprite.setScale(TILE_SCALE, TILE_SCALE);
}

void GameTile::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

sf::Vector2f GameTile::getPosition() const {
	return sprite.getPosition();
}

void GameTile::setTextureRect(sf::IntRect textureRect) {
	sprite.setTextureRect(textureRect);
}

void GameTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}