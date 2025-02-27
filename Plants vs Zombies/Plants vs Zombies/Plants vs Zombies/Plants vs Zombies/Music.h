#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;
using namespace std;


sf::Music Homescreen_Music;
Homescreen_Music.openFromFile("C:/Users/Saad/Desktop/Projects/Plants vs Zombies/Plants vs Zombies/Assets/Music/Homescreen_Grasswalk.ogg"))
    ///std::cerr << "Failed to load background music" << std::endl;
    //return 0;

bool music_home = true;