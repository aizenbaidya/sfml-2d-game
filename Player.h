#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "GameDriver.h"
#include <SFML/Graphics.hpp>

class Player : public Entity {
public:
	Player();

	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow& window);
	void setPosition(float x, float y) override;
	sf::Vector2f getPosition() const override;

private:
	enum State { Idle, Walking };
	State currentState = Idle;
	int currentRow = 0;

	// Width and height of a single frame in the sprite sheet
	const int ORIGINAL_FRAME_WIDTH = 48;
	const int ORIGINAL_FRAME_HEIGHT = 48;

	// The scale factor for enlarging the frame
	const float ENLARGEMENT_SCALE = 3.0f;

	// Dimensions of the frame after scaling
	const int SCALED_FRAME_WIDTH = static_cast<int>(std::round(ORIGINAL_FRAME_WIDTH * ENLARGEMENT_SCALE));
	const int SCALED_FRAME_HEIGHT = static_cast<int>(std::round(ORIGINAL_FRAME_HEIGHT * ENLARGEMENT_SCALE));

	// 
	const float ANIMATION_SPEED = 0.25f;

	// 
	const float MOVEMENT_SPEED = 150.0f;

	int currentFrame = 0;
	float elapsedTime = 0.0f;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape hitbox;
	sf::RectangleShape hitbox2;
};

#endif