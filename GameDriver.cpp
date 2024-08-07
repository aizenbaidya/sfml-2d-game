#include "GameDriver.h"
#include <iostream>

void GameDriver::run() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML 2D Game", sf::Style::Titlebar | sf::Style::Close);

	sf::Image icon;
	if (!icon.loadFromFile("assets/The-Plant.jpg")) {
		return;
	}

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Player player;
	GameWorld gameWorld("map.txt");
	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Time elapsed since the last frame
		sf::Time deltaTime = clock.restart();

		player.update(deltaTime);
		gameWorld.updateView(player.getPosition());
		window.setView(gameWorld.getView());

		window.clear();

		window.draw(gameWorld);
		window.draw(player);
		player.drawHitbox(window);

		window.display();
	}
}