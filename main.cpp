#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "imgui.h"
#include "imgui-SFML.h"

#include "pendulum.h"

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

	sf::RenderWindow window(sf::VideoMode(width, height), title, sf::Style::Default, settings);

    //initializes IMGui window
    ImGui::SFML::Init(window);

	//window parameters
	sf::View view = window.getDefaultView();
	bool isMouseDragging = false;
	sf::Vector2i lastMousePosition;
	sf::Vector2f lastViewPosition;
	sf::Vector2i deltaMouse;

	//starting settings
	float g = 9.8f;
	unsigned int timeSpeed = 5;

	//example pendulum
	Pendulum pend(100, 20, sf::Vector2f(100, 100));

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

			if(event.type == sf::Event::Resized) {
				
				//resizes the view together with the window
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        		window.setView(sf::View(visibleArea));		
			}

		} window.clear();
        ImGui::SFML::Update(window, _clock.restart());

		//updates the isMouseDragging state
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !isMouseDragging) {
			isMouseDragging = true;
			lastMousePosition = sf::Mouse::getPosition(window);
			lastViewPosition = view.getCenter();
		}
		else if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			isMouseDragging = false;
		}

		if(isMouseDragging) {
			//updates the change in the mouse position
			deltaMouse = sf::Vector2i(sf::Mouse::getPosition(window).x - lastMousePosition.x, 
				sf::Mouse::getPosition(window).y - lastMousePosition.y);
			
			//updates the view
			sf::Vector2f center = view.getCenter();
			view.setCenter(lastViewPosition.x - deltaMouse.x, lastViewPosition.y - deltaMouse.y);
			window.setView(view);
		}

        //Imgui interface 
        ImGui::Begin("Window");
        ImGui::SliderInt("TimeSpeed", (int*)&timeSpeed, 0, 1000);
        ImGui::SliderFloat("g", &g, -50, 50);
        ImGui::End();

        ImGui::SFML::Render(window);
		
		std::cout << isMouseDragging;
		window.draw(pend);
		pend.processPhysics(timeSpeed, deltaTime, g);
		
		window.display();
	}

    ImGui::SFML::Shutdown();
	return 0;
}