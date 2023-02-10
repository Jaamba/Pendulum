#include "Slider.h"
#include <iostream>
#include <SFML/Graphics.hpp>

void Slider::update() {
	if (*pointingVar > max || *pointingVar < min) throw std::exception("var must be between min and max");

	float factor = (*pointingVar - min) / (max - min);

	center.setPosition(sf::Vector2f(factor * length - centerRad/2, width / 2 - centerRad/2));
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

