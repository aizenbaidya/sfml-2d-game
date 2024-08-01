#ifndef GAMETILE_H
#define GAMETILE_H

#include <SFML/Graphics.hpp>

class GameTile : public sf::Drawable {
public:
	GameTile(const sf::Texture& texture, sf::IntRect textureRect, sf::Vector2f position);

	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;
	void setTextureRect(sf::IntRect textureRect);

private:
	sf::Sprite sprite;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif