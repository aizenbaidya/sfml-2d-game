#include "Entity.h"

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}