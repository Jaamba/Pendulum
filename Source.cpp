#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//global settings
constexpr unsigned int width = 800;
constexpr unsigned int height = 800;
const std::string title = "Pendulum";

int main() {

	//creates the window and its settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(width,height),title, sf::Style::Close, settings);

	//window loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			} window.clear();
		}
	}
	return 0;
}
