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
	sf::View view = window.getDefaultView();

    //initializes IMGui window
    ImGui::SFML::Init(window);

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

        //Imgui interface 
        ImGui::Begin("Window");
        ImGui::SliderInt("TimeSpeed", (int*)&timeSpeed, 0, 1000);
        ImGui::SliderFloat("g", &g, -50, 50);
        ImGui::End();

        ImGui::SFML::Render(window);
		
		window.draw(pend);
		pend.processPhysics(timeSpeed, deltaTime, g);
		
		window.display();
	}

    ImGui::SFML::Shutdown();
	return 0;
}