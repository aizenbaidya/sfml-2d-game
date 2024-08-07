#ifndef GAMETILE_H
#define GAMETILE_H

#include <SFML/Graphics.hpp>

/**
 * @brief Represents a drawable tile in the game
 */
class GameTile : public sf::Drawable {
public:
	GameTile(const sf::Texture& texture, sf::IntRect textureRect, sf::Vector2f position);

	void setPosition(float x, float y);
	void setTextureRect(sf::IntRect textureRect);
	sf::Vector2f getPosition() const;

	static constexpr int TILE_SIZE = 16;
	static constexpr float TILE_SCALE = 3.0f;
	static constexpr int SCALED_TILE_SIZE = static_cast<int>(TILE_SIZE * TILE_SCALE);

private:
	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif