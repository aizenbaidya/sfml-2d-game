#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player() {
	if (!texture.loadFromFile("assets/Character-Spritesheet.png")) {
		std::cout << "Texture failed to load!" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(PLAYER_OFFSET, PLAYER_OFFSET, ORIGINAL_PLAYER_SIZE, ORIGINAL_PLAYER_SIZE));
	sprite.setScale(ENLARGEMENT_SCALE, ENLARGEMENT_SCALE);
	sprite.setPosition((GameWorld::MAP_WIDTH - SCALED_PLAYER_SIZE) / 2.0f, (GameWorld::MAP_HEIGHT - SCALED_PLAYER_SIZE) / 2.0f);

	hitbox.setSize(sf::Vector2f(static_cast<float>(SCALED_PLAYER_SIZE), static_cast<float>(SCALED_PLAYER_SIZE)));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2.0f);
	hitbox.setPosition(sprite.getPosition());
}

void Player::update(sf::Time deltaTime) {
	handleInput();
	normalizeMovement();
	updateState();
	move(deltaTime);
	updateAnimation(deltaTime);
}

void Player::drawHitbox(sf::RenderWindow& window) {
	window.draw(hitbox);
}

void Player::handleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y += MOVEMENT_SPEED;
		spriteSheetRowIndex = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= MOVEMENT_SPEED;
		spriteSheetRowIndex = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += MOVEMENT_SPEED;
		spriteSheetRowIndex = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= MOVEMENT_SPEED;
		spriteSheetRowIndex = 2;
	}
}

void Player::normalizeMovement() {
	// Normalize movement vector if necessary.
	if (movement.x != 0.0f && movement.y != 0.0f) {
		movement /= std::sqrt(2.0f);
	}
}

void Player::updateState() {
	if (movement.x != 0 || movement.y != 0) {
		currentState = State::Walking;
	}
	else {
		currentState = State::Idle;
	}
}

void Player::move(sf::Time deltaTime) {
	sprite.move(movement * deltaTime.asSeconds());
	hitbox.move(movement * deltaTime.asSeconds());

	// Reset the movement vector to 0 to ensure the player only moves when pressing the movement keys.
	// Without resetting, the player would keep moving even when no keys are pressed
	movement.x = 0;
	movement.y = 0;
}

void Player::updateAnimation(sf::Time deltaTime) {
	timeSinceLastAnimation += deltaTime.asSeconds();

	// Check if it's time to update the animation frame.
	if (timeSinceLastAnimation >= ANIMATION_UPDATE_INTERVAL_SEC) {
		timeSinceLastAnimation = 0.0f;

		// Calculate the starting column for the sprite sheet based on the player's state.
		int startingSpriteSheetCol = (currentState == State::Walking) ? WALKING_SPRITE_START_COL : IDLE_SPRITE_START_COL;

		// Update the sprite sheet column index for the next frame, wrapping around if needed.
		spriteSheetColIndex = (spriteSheetColIndex + 1) % SPRITE_FRAME_COUNT + startingSpriteSheetCol;

		sprite.setTextureRect(sf::IntRect(spriteSheetColIndex * ORIGINAL_FRAME_SIZE + PLAYER_OFFSET,
			spriteSheetRowIndex * ORIGINAL_FRAME_SIZE + PLAYER_OFFSET,
			ORIGINAL_PLAYER_SIZE,
			ORIGINAL_PLAYER_SIZE));
	}
}