#include "pendulum.h"
#include <math.h>
#include <iostream>

void Pendulum::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); 

    target.draw(_centre, states);
    target.draw(_string, states);
}

void Pendulum::processPhysics(int timeSpeed, float deltaTime, float g) {
    //physics simulation:

		//calculates the angle of the string in relation to the pendulum's position
		for (int i = 0; i < timeSpeed; i++) {

			_angle = -M_PI / 2 + atan2f(_centre.getPosition().y - _string.getPosition().y,
				_centre.getPosition().x - _string.getPosition().x);
			_string.setRotation(_angle * 180 / M_PI);

			_accelleration = g * sinf(_angle);

			_velocity += _accelleration * deltaTime;

			float xVelocity = _velocity * cosf(_angle);
			float yVelocity = _velocity * sinf(_angle);

			_centre.setPosition(_centre.getPosition().x + xVelocity * deltaTime,
				_centre.getPosition().y + yVelocity * deltaTime);
		}
}

//applies colors
void Pendulum::updateColors() {
    _centre.setFillColor(sf::Color((int)(_centreColor[0]*256), (int)(_centreColor[1]*256), (int)(_centreColor[2]*256)));
    _string.setFillColor(sf::Color((int)(_stringColor[0]*256), (int)(_stringColor[1]*256), (int)(_stringColor[2]*256)));
}