#pragma once
#include <SFML/Graphics.hpp>
#include <exception>
#include <type_traits>

//Slider class that generates a slide which can be positioned and rotated.
//A Slider can be drawn via the function window.draw(slider), but must first
//be updated by the update(window) function.
//it also takes a pointer to the variable it changes, which must necessarily
//be an integral value or a floating point value. Because of this, Slider is a
//template class. If T does not represent a number, undefined behaviour is going
//to occour
template<typename T>
class Slider : public sf::Drawable, public sf::Transformable {
private:
	
	//private members:
	const float width{};
	const float height{};
	const float centerRad{};
	const float max{};
	const float min{};
	T* const pointingVar{};
	float pos{};

	//graphical elements:
	sf::RectangleShape rect;
	sf::CircleShape center;

	

public:
	//disabled default constructor (it doesn't make sense to create an
	//empty slider)
	Slider() = delete;
	
	//base constructor: always called by other constructors
	Slider(float _width, float _height, float _centerRad, float _max, 
		float _min, T* _pointingVar) :
		//members assignemnt
		width{ _width },
		height{ _height },
		centerRad{ _centerRad },
		max{ _max },
		min{ _min },
		pointingVar{ _pointingVar }
	{
		//argument checking
		if (_width <= 0 || _height <= 0 || centerRad <= 0) 
			throw std::invalid_argument("width, height, and radius must be more than 0");
		if (_min >= _max) 
			throw std::invalid_argument("min cannot be greater or equal than max");
		if (!pointingVar) 
			throw std::invalid_argument("pointing var cannot be nullptr");
		if (*_pointingVar > _max || *_pointingVar < _min) 
			throw std::invalid_argument("var must be between min and max");

		//setup of the graphical interface
		rect.setFillColor(sf::Color::White);
		rect.setSize(sf::Vector2f(width, height));
		center.setRadius(centerRad);
		center.setOrigin(centerRad / 2, centerRad / 2);
		center.setFillColor(sf::Color::Red);
	}

	//constructor override that also takes the starting position as a vector2
	Slider(float _width, float _height , float _centerRad, float _max, float _min, 
		T* _pointingVar, const sf::Vector2f& _screenPos) :
		Slider(_width, _height, _centerRad, _max, _min, _pointingVar)
	{
		setPosition(_screenPos);
	}
	//constructor override that takes the starting pos as two floats
	Slider(float _width, float _height, float _centerRad, float _max, float _min,
		T* _pointingVar, float xPos, float yPos) :
		Slider(_width, _height, _centerRad, _max, _min, _pointingVar)
	{
		setPosition(xPos, yPos);
	}

	//actually draws the slider
	virtual void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();

		target.draw(rect, states);
		target.draw(center, states);
	}

	//updates the slider on a window
	void update(const sf::RenderWindow& window) {
		
		//sets the position of the slider based on pointingVar
		try {
			pos = (*pointingVar - min) / (max - min);
		}
		catch (...) {
			throw std::exception("error: not valid type for Slider");
		}

		//sets the position to the limits if it overflows/underflows
		if (pos > 1) pos = 1;
		else if (pos < 0) pos = 0;

		//gets the bound area of the slider
		sf::FloatRect boundArea = getTransform().transformRect(rect.getLocalBounds());

		//if the slider is dragged
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		if (boundArea.contains(mousePos)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

				//recalculates pos and pointingVar
				pos = (mousePos.x - getPosition().x) / width;
				*pointingVar = pos * max + min;
			}
		}

		//sets the new position
		center.setPosition(sf::Vector2f(pos * width - centerRad / 2, height / 2 - centerRad / 2));
	}

	//getters
	const int getWidth() const {
		return width;
	}
	const int getHeight() const {
		return height;
	}
	const int getCenterRad() const {
		return centerRad;
	}
};