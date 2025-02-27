#pragma once
#include <iostream>
using namespace std;
using namespace sf;
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Pea
{
public:
	sf::Sprite pea;
	int speed;
	int x;
	int y;

	int first_x;
	int first_y;
	int covered_distance;
public:
	Pea() :speed(0), x(0), y(0) {}
	Pea(int sp, int initial_x, int initial_y)
	{
		speed = sp;
		x = initial_x;
		y = initial_y;

		first_x = x;
		first_y = y;

		Image pea_i;
		pea_i.loadFromFile("Assets/Images/Plants/pea.png");
		Texture pea_t;
		pea_t.loadFromImage(pea_i);
		pea.setTexture(pea_t);
	}
	Pea(int sp, int initial_x, int initial_y, string s)
	{
		speed = sp;
		x = initial_x;
		y = initial_y;

		first_x = x;
		first_y = y;

		Image spea_i;
		spea_i.loadFromFile("Assets/Images/Plants/spea.png");
		Texture spea_t;
		spea_t.loadFromImage(spea_i);
		pea.setTexture(spea_t);
	}
	void set(int new_x, int new_y)
	{
		x = new_x;
		y = new_y;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	void draw_on(RenderWindow& window, int x, int y, string s)
	{
		Image pea_i;
		pea_i.loadFromFile("Assets/Images/Plants/spea.png");
		Texture pea_t;
		pea_t.loadFromImage(pea_i);
		pea.setTexture(pea_t);
		pea.setPosition(x, y);
		window.draw(pea);
	}
	void draw_on(RenderWindow& window, int x, int y)
	{
		Image pea_i;
		pea_i.loadFromFile("Assets/Images/Plants/pea.png");
		Texture pea_t;
		pea_t.loadFromImage(pea_i);
		pea.setTexture(pea_t);
		pea.setPosition(x, y);
		window.draw(pea);
	}
	void update(RenderWindow& window, string s, bool alpha)
	{
		x += speed;
		if (alpha)
			draw_on(window, x, y, s);
	}
	void update(RenderWindow& window, bool alpha)
	{
		x += speed;
		if (alpha)
			draw_on(window, x, y);
	}
	void setY(int a)
	{
		y = a;
	}
	void setX(int b)
	{
		x = b;
	}
};