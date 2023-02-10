#include "Slider.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void Slider::update(const sf::RenderWindow& window) {
	if (*pointingVar > max || *pointingVar < min) throw std::exception("var must be between min and max");

	pos = (*pointingVar - min) / (max - min);
	
	sf::FloatRect boundArea(getPosition().x, getPosition().y, length, width);
	if (boundArea.contains((sf::Vector2f)sf::Mouse::getPosition(window))) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			pos = (sf::Mouse::getPosition(window).x - getPosition().x) / length;
			*pointingVar = pos * max + min;
		}
	}

	center.setPosition(sf::Vector2f(pos * length - centerRad/2, width / 2 - centerRad/2));
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(rect, states);
	target.draw(center, states);
}

//getters
int Slider::getLength() const {
	return length;
}
int Slider::getWidth() const {
	return width;
}
int Slider::getCenterRad() const {
	return centerRad;
}

