#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//constants
constexpr float PI = 3.14159265f;

//global settings
constexpr unsigned int width = 800;
constexpr unsigned int height = 800;
const std::string title = "Pendulum";

int main() {

	//creates the window and its settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(width,height),title, sf::Style::Close, settings);

	//starting settings
	const float stringLeng = 100;
	const float g = 9.8f;
	const float pendulumRadius = 100;
	const float pendulumMass = 10;
	const sf::Vector2f pendulumStartPos = sf::Vector2f(200, 200);
	const sf::Vector2f stringStartPos = sf::Vector2f(500, 200);

	//creates the pendulum
	sf::CircleShape pendulum;
	pendulum.setFillColor(sf::Color::White);
	pendulum.setOrigin(pendulumRadius, pendulumRadius);
	pendulum.setPosition(pendulumStartPos);
	pendulum.setRadius(pendulumRadius);

	//creates the string
	sf::RectangleShape string;
	string.setSize(sf::Vector2f(10, stringLeng));
	string.setFillColor(sf::Color::White);
	string.setPosition(stringStartPos);


	//window loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			} window.clear();

			//physics simulation:
			float angle = atan2f(pendulum.getPosition().y, pendulum.getPosition().x);
			string.setRotation(angle);

			pendulum.setPosition(pendulum.getPosition().x + 0.1f, 200);

			window.draw(pendulum);
			window.draw(string);
			
			window.display();
		}
	}
	return 0;
}
