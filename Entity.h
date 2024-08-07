#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

/**
 * @brief This class represents a drawable entity.
 *
 * Derived classes must implement update logic.
 */
class Entity : public sf::Drawable {
public:
	virtual sf::Vector2f getPosition() const;

protected:
	sf::Texture texture;
	sf::Sprite sprite;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(sf::Time deltaTime) = 0;
};

#endif