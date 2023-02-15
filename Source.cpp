#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Slider.h"

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
	int stringLeng = 200;
	const int stringThickness = 10;
	float g = 9.8f;
	int pendulumRadius = 50;
	unsigned int timeSpeed = 100;
	const sf::Vector2f stringStartPos = sf::Vector2f(500, 200);
	const sf::Vector2f pendulumStartPos = sf::Vector2f(stringStartPos.x - stringLeng, 200 + stringThickness/2);

	//UI:
	//Sliders:
	Slider<float> gSlider(30, -10, &g, 150, sf::Vector2f(50, 100), "g");
	Slider<unsigned int> timeSpeedSlider(500, 0, &timeSpeed, 150, sf::Vector2f(50, 150), "TimeSpeed");

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
	float angle = 0;

	_clock.restart();
	//window loop
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
		for (int i = 0; i < timeSpeed; i++) {

			angle = -PI / 2 + atan2f(pendulum.getPosition().y - string.getPosition().y,
				pendulum.getPosition().x - string.getPosition().x);
			string.setRotation(angle * 180 / PI);

			accelleration = g * sinf(angle);

			velocity += accelleration * deltaTime;

			float xVelocity = velocity * cosf(angle);
			float yVelocity = velocity * sinf(angle);

			pendulum.setPosition(pendulum.getPosition().x + xVelocity * deltaTime,
				pendulum.getPosition().y + yVelocity * deltaTime);
		}

		window.draw(pendulum);
		window.draw(string);

		//draws and updates UI
		gSlider.update(window);
		window.draw(gSlider);
		timeSpeedSlider.update(window);
		window.draw(timeSpeedSlider);

		window.display();
	}

	return 0;
}