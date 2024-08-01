#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
public:
	virtual ~Entity() = default;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void setPosition(float x, float y) = 0;
	virtual sf::Vector2f getPosition() const = 0;

protected:
	sf::Texture texture;
	sf::Sprite sprite;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif