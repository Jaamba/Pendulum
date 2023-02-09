#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//constants
constexpr float PI = 3.14159265f;

//global settings
constexpr unsigned int width = 800;
constexpr unsigned int height = 800;
const std::string title = "Pendulum";

//clock
sf::Clock _clock;

int main() {

	//creates the window and its settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Close, settings);

	//starting settings
	const int stringLeng = 200;
	const int stringThickness = 10;
	const float g = 9.8f;
	const int pendulumRadius = 50;
	const int timeSpeed = 50;
	const sf::Vector2f stringStartPos = sf::Vector2f(500, 200);
	const sf::Vector2f pendulumStartPos = sf::Vector2f(stringStartPos.x - stringLeng, 200 + stringThickness/2);

	//creates the pendulum
	sf::CircleShape pendulum;
	pendulum.setFillColor(sf::Color::White);
	pendulum.setOrigin(pendulumRadius, pendulumRadius);
	pendulum.setPosition(pendulumStartPos);
	pendulum.setRadius(pendulumRadius);

	//creates the string
	sf::RectangleShape string;
	string.setSize(sf::Vector2f(stringThickness, stringLeng));
	string.setOrigin(stringThickness / 2, 0);
	string.setFillColor(sf::Color::White);
	string.setPosition(stringStartPos);

	//keeps track of the pendulum's motion
	float velocity = 0;
	float accelleration = 0;

	//window loop
	_clock.restart();
	while (window.isOpen()) {
		float deltaTime = _clock.getElapsedTime().asSeconds();
		_clock.restart();

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

		} window.clear();

		//physics simulation:

		//calculates the angle of the string in relation to the pendulum's position
		float angle = -PI / 2 + atan2f(pendulum.getPosition().y - string.getPosition().y,
			pendulum.getPosition().x - string.getPosition().x);
		string.setRotation(angle * 180 / PI);

	    accelleration = g * sinf(angle);

		velocity += accelleration * deltaTime * timeSpeed;

		float xVelocity = velocity * cosf(angle);
		float yVelocity = velocity * sinf(angle);

		pendulum.setPosition(pendulum.getPosition().x + xVelocity * deltaTime * timeSpeed,
			pendulum.getPosition().y + yVelocity * deltaTime * timeSpeed);

		window.draw(pendulum);
		window.draw(string);

		window.display();
	}

	return 0;
}