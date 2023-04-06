//creates the pendulum class definition

#pragma once

#include <SFML\Graphics.hpp>

class Pendulum : public sf::Transformable,  public sf::Drawable {
    private:
        int         _stringLeng        { 200 };
	    const int   _stringThickness   { 10 };
        int         _centreRadius      { 50 };

        float       _stringColor[3]    = {1.0f, 1.0f, 1.0f};
        float       _centreColor[3]    = {1.0f, 1.0f, 1.0f};

	    sf::CircleShape _centre;
	    sf::RectangleShape _string;

        //inherited draw function
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        //keeps track of the pendulum's motion
	    float _velocity = 0;
	    float _accelleration = 0;
	    float _angle = 0;

    public:
        Pendulum(size_t stringLength, size_t centreRadius, const sf::Vector2f& startPosition, 
            sf::Color centreColor = sf::Color::White, sf::Color stringColor = sf::Color::White) :
            
            _stringLeng{ static_cast<int>(stringLength)}, 
            _centreRadius{ static_cast<int>(centreRadius)},
            _stringColor{ stringColor.r / 256.0f,stringColor.b / 256.0f,stringColor.g / 256.0f},
            _centreColor{ centreColor.r / 256.0f,centreColor.b / 256.0f,centreColor.g / 256.0f}
            {
                
            //applies the transform
            setPosition(startPosition);

            //creates the pendulum
	        _centre.setOrigin(_centreRadius, _centreRadius);
	        _centre.setPosition( sf::Vector2f(startPosition.x - stringLength, startPosition.y));
	        _centre.setRadius(_centreRadius);

	        //creates the string
            _string.setSize(sf::Vector2f(_stringThickness, _stringLeng));
	        _string.setPosition(startPosition);
            _string.setOrigin(_stringThickness / 2, 0);
        }

        Pendulum(size_t stringLength, size_t centreRadius, float xstartPosition, float ystartPosition, 
            sf::Color centreColor = sf::Color::White, sf::Color stringColor = sf::Color::White) : Pendulum(
                stringLength, centreRadius, sf::Vector2f(xstartPosition, ystartPosition), centreColor, stringColor) {}

        void processPhysics(int timeSpeed, float deltaTime, float g);
        void updateColors();
};