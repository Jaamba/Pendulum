#include <SFML/Graphics.hpp>
#include <iostream>
#include "Slider.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(900, 900), "Test");

	float var = 0;
	Slider<float> slider(100, 20, 15, 10, 0, &var, 100,100);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();

		slider.update(window);
		window.draw(slider);

		window.display();
	}
	
	return 0;
}