#include "GameDriver.h"

void GameDriver::run() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML 2D Game");

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

		sf::Time deltaTime = clock.restart();
		player.update(deltaTime);

		window.clear();
		window.draw(gameWorld);
		player.draw(window);
		window.display();
	}
}