#pragma once
#include <SFML/Graphics.hpp>
#include <exception>

class Slider : public sf::Drawable, public sf::Transformable {
private:
	const size_t length{};
	const size_t width{};
	const size_t centerRad{};
	const float max{};
	const float min{};
	const int* pointingVar{};
	int pos{};

	//graphical elements:
	sf::RectangleShape rect;
	sf::CircleShape center;

public:

	Slider(size_t _length, size_t _width, size_t _centerRad, float _max, float _min, int* _pointingVar) :
		length{ _length },
		width{ _width },
		centerRad{ _centerRad },
		max{ _max },
		min{ _min },
		pointingVar{ _pointingVar }
	{
		if (_min >= _max) throw std::invalid_argument("min cannot be greater or equal than max");
		if (!pointingVar) throw std::invalid_argument("pointing var cannot be nullptr");
		if (*_pointingVar > _max || *_pointingVar < _min) throw std::invalid_argument("var must be between min and max");

		rect.setFillColor(sf::Color::White);
		rect.setSize(sf::Vector2f(length, width));
		center.setRadius(centerRad);
		center.setOrigin(centerRad / 2, centerRad / 2);
		center.setFillColor(sf::Color::Red);
	}

	Slider(size_t _length, size_t _width, size_t _centerRad, float _max, float _min, int* _pointingVar, const sf::Vector2f& _screenPos) :
		Slider(_length, _width, _centerRad, _max, _min, _pointingVar)
	{
		setPosition(_screenPos);
	}

	Slider(size_t _length, size_t _width, size_t _centerRad, float _max, float _min, int* _pointingVar, float xPos, float yPos) :
		Slider(_length, _width, _centerRad, _max, _min, _pointingVar)
	{
		setPosition(xPos, yPos);
	}

	void update();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//getters
	int getLength() const;
	int getWidth() const;
	int getCenterRad() const;
};