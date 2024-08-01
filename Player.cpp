#include "Player.h"
#include <iostream>
#include <cmath>

Player::Player() {
	if (!texture.loadFromFile("assets/Character-Spritesheet.png")) {
		std::cout << "Texture failed to load!" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, ORIGINAL_FRAME_WIDTH, ORIGINAL_FRAME_HEIGHT));
	sprite.setScale(ENLARGEMENT_SCALE, ENLARGEMENT_SCALE);
	sprite.setPosition(GameDriver::WINDOW_WIDTH / 2.0f - SCALED_FRAME_WIDTH / 2.0f,
		GameDriver::WINDOW_HEIGHT / 2.0f - SCALED_FRAME_HEIGHT / 2.0f);

	hitbox.setSize(sf::Vector2f(static_cast<float>(SCALED_FRAME_WIDTH), static_cast<float>(SCALED_FRAME_HEIGHT)));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(2.0f);
	hitbox.setPosition(sprite.getPosition());

	hitbox2.setSize(sf::Vector2f(static_cast<float>(ORIGINAL_FRAME_WIDTH), static_cast<float>(ORIGINAL_FRAME_HEIGHT)));
	hitbox2.setFillColor(sf::Color::Transparent);
	hitbox2.setOutlineColor(sf::Color::Blue);
	hitbox2.setOutlineThickness(2.0f);
	hitbox2.setPosition(sprite.getPosition().x + ORIGINAL_FRAME_WIDTH, sprite.getPosition().y + ORIGINAL_FRAME_HEIGHT);
}

void Player::update(sf::Time deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement.y += MOVEMENT_SPEED;
		currentRow = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement.y -= MOVEMENT_SPEED;
		currentRow = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement.x += MOVEMENT_SPEED;
		currentRow = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x -= MOVEMENT_SPEED;
		currentRow = 2;
	}

	// Normalize movement vector if necessary.
	if (movement.x != 0.0f && movement.y != 0.0f) {
		movement /= std::sqrt(2.0f);
	}

	if (movement != sf::Vector2f(0.0f, 0.0f)) {
		currentState = Walking;
	}
	else {
		currentState = Idle;
	}

	sprite.move(movement * deltaTime.asSeconds());
	hitbox.move(movement * deltaTime.asSeconds());
	hitbox2.move(movement * deltaTime.asSeconds());

	elapsedTime += deltaTime.asSeconds();
	if (elapsedTime >= ANIMATION_SPEED) {
		elapsedTime = 0.0f;
		int frameStart = (currentState == Walking) ? 2 : 0;
		currentFrame = (currentFrame + 1) % 2 + frameStart;
		sprite.setTextureRect(sf::IntRect(currentFrame * ORIGINAL_FRAME_WIDTH, currentRow * ORIGINAL_FRAME_HEIGHT,
			ORIGINAL_FRAME_WIDTH, ORIGINAL_FRAME_HEIGHT));
	}
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(hitbox);
	window.draw(hitbox2);
}

void Player::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

sf::Vector2f Player::getPosition() const {
	return sprite.getPosition();
}