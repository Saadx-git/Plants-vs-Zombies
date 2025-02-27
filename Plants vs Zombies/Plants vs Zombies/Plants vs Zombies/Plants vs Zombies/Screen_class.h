#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Patch.h"
using namespace sf;
using namespace std;

#ifndef SCREEN_H
#define SCREEN_H


class Screen {
private:
	string background_path;
	sf::Image background_image;
	sf::Texture background_texture;
	sf::Sprite background_sprite;

	int length_x;
	int length_y;

	int position_x;
	int position_y;
public:

	Screen(string path, int x = 1280, int y = 720, int pos_x = 0, int pos_y = 0) {
		
		background_image.loadFromFile(path);
		background_texture.loadFromImage(background_image);
		background_sprite.setTexture(background_texture);



        length_x = x;
        length_y = y;

        position_x = pos_x;
        position_y = pos_y;

	}

    // Getters
    string getBackgroundPath() const {
        return background_path;
    }

    sf::Sprite getBackgroundSprite() const {
        return background_sprite;
    }

    int getLengthX() const {
        return length_x;
    }

    int getLengthY() const {
        return length_y;
    }

    int getPosX() const {
        return position_x;
    }

    int getPosY() const {
        return position_y;
    }

    // Setters
    void setBackgroundPath(string path) {
        background_path = path;
    }

    void setLength(int x, int y) {
        length_x = x;
        length_y = y;
    }

    void setPosition(int x, int y) {
        setPosX(x);
        setPosY(y);

        background_sprite.setPosition(x, y);
    }
    void setPosition(patch target) {
        //cout << target.getX() << " " << target.getY() << endl;

        setPosX(target.getX());
        setPosY(target.getY());
        
        background_sprite.setPosition(target.getX(), target.getY());
    }

    void setPosX(float x) {
        position_x = x;
    }

    void setPosY(float y) {
        position_y = y;
    }

    //Drawing on Widow

    void draw_on(sf::RenderWindow& window) {
        window.draw(background_sprite);
    }

};

#endif