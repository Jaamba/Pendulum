#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>

#include "imgui.h"
#include "imgui-SFML.h"

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

    //initializes IMGui window
    ImGui::SFML::Init(window);

	//starting settings
	int stringLeng = 200;
	const int stringThickness = 10;
	float g = 9.8f;
	int pendulumRadius = 50;
	unsigned int timeSpeed = 100;
	const sf::Vector2f stringStartPos = sf::Vector2f(500, 200);
	const sf::Vector2f pendulumStartPos = sf::Vector2f(stringStartPos.x - stringLeng, 200 + stringThickness/2);
    float stringColor[3] = {0.0f, 0.0f, 0.0f};
    float pendulumColor[3] = {0.0f, 0.0f, 0.0f};

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

		sf::Event event;
		while (window.pollEvent(event)) {
            
            ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		} window.clear();
        ImGui::SFML::Update(window, _clock.restart());

        //Imgui interface
        ImGui::Begin("Window");
        ImGui::SliderInt("TimeSpeed", (int*)&timeSpeed, 0, 1000);
        ImGui::ColorEdit3("String Color", stringColor);
        ImGui::ColorEdit3("Pendulum Color", pendulumColor);
        string.setFillColor(sf::Color(
            (int)(stringColor[0] * 255),
            (int)(stringColor[1] * 255),
            (int)(stringColor[2] * 255)));
        pendulum.setFillColor(sf::Color(
            (int)(pendulumColor[0] * 255),
            (int)(pendulumColor[1] * 255),
            (int)(pendulumColor[2] * 255)));
        ImGui::End();

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

		window.draw(string);
		window.draw(pendulum);
        ImGui::SFML::Render(window);

		window.display();
	}

    ImGui::SFML::Shutdown();
	return 0;
}