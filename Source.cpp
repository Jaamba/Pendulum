#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode(900, 900), "Test");

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
	
	return 0;
}