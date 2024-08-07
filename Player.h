#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "GameDriver.h"
#include <SFML/Graphics.hpp>

/**
 * @brief The Player class represents the character in the game, handling movement, animations, and interaction with the game world.
 */
class Player : public Entity {
public:
	Player();

	void update(sf::Time deltaTime) override;
	void drawHitbox(sf::RenderWindow& window);

	// Size of the player within a single sprite frame (in pixels)
	static constexpr int ORIGINAL_PLAYER_SIZE = 16;

	// The scale factor for enlarging the player
	static constexpr float ENLARGEMENT_SCALE = 3.0f;

	// Dimensions of the player after scaling
	static constexpr int SCALED_PLAYER_SIZE = static_cast<int>(ORIGINAL_PLAYER_SIZE * ENLARGEMENT_SCALE);

private:
	void handleInput();
	void normalizeMovement();
	void updateState();
	void move(sf::Time deltaTime);
	void updateAnimation(sf::Time deltaTime);

	enum class State { Idle, Walking };
	State currentState = State::Idle;

	sf::RectangleShape hitbox;
	sf::Vector2f movement{ 0.0f, 0.0f };

	// Width and height of a single frame in the sprite sheet
	const int ORIGINAL_FRAME_SIZE = 48;

	// Row index in the sprite sheet corresponding to movement direction: 0 = Down, 1 = Up, 2 = Left, 3 = Right
	int spriteSheetRowIndex = 0;

	// The column index in the sprite sheet corresponding to idle or walking sprites: 0 & 1 for Idle, 2 & 3 for Walking
	int spriteSheetColIndex = 0;

	// Duration (in seconds) between animation frame updates
	const float ANIMATION_UPDATE_INTERVAL_SEC = 0.25f; // Every 1/4th of a second

	// The speed at which the player moves (pixels per second)
	const float MOVEMENT_SPEED = 150.0f; // 150 pixels/second

	// Time elapsed since the last animation change (in seconds)
	float timeSinceLastAnimation = 0.0f;

	// In the 192x192 sprite sheet, each frame is 48x48 pixels. 
	// The player is (centered) in a 16x16 area in the frame, so this constant adjusts drawing positions.
	const int PLAYER_OFFSET = 16;

	// Starting column index for walking sprites (first is at index 2)
	const int WALKING_SPRITE_START_COL = 2;

	// Starting column index for idle sprites (first is at index 0)
	const int IDLE_SPRITE_START_COL = 0;

	// Total number of frames in each animation cycle (walking and idle animations use the identical count)
	const int SPRITE_FRAME_COUNT = 2;
};

#endif