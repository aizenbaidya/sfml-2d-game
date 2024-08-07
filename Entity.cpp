#include "Entity.h"

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}

/**
 * @return The position of the top-left corner of the entity's sprite as a sf::Vector2f
 */
sf::Vector2f Entity::getPosition() const {
	return sprite.getPosition();
}