#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Static_Sun
{
	Sprite sun;
	int x;
	int y;
public:
	Static_Sun(RenderWindow& window, int initial_x, int initial_y)
	{
		Image sun_i;
		sun_i.loadFromFile("Assets/Images/Other/sun.png");
		Texture sun_t;
		sun_t.loadFromImage(sun_i);
		sun.setTexture(sun_t);
		x = initial_x;
		y = initial_y;
		sun.setOrigin(sun.getLocalBounds().width / 2, sun.getLocalBounds().height / 2);
		sun.setPosition(x, y);
	}
	Sprite getSprite()
	{
		return sun;
	}
	void spawn_Sun(RenderWindow& win)
	{
		Image sun_i;
		sun_i.loadFromFile("Assets/Images/Other/sun.png");
		Texture sun_t;
		sun_t.loadFromImage(sun_i);
		sun.setTexture(sun_t);
		sun.setPosition(x, y);
		win.draw(sun);
	}
	bool isTouched(int mouse_x, int mouse_y, Sprite sun)
	{
		float x = sun.getPosition().x;
		float y = sun.getPosition().y;

		float length = sun.getLocalBounds().height + y;
		float width = sun.getLocalBounds().width + x;

		if (mouse_x < width && mouse_x > x && mouse_y < length && mouse_y > y) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return true;
		}

		return false;
	}

};