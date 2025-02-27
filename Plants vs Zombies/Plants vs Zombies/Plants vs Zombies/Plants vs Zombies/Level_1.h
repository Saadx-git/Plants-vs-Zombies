////#pragma once
////#pragma once
////#include <iostream>
////#include <SFML/Audio.hpp>
////#include <SFML/System.hpp>
////#include <SFML/Window.hpp>
////#include <SFML/Graphics.hpp>
////#include <ctime>
////using namespace sf;
////using namespace std;
////
////
////#include "HomeScreen.h"
////#include "Level_Page.h"
////#include "Instructions Page.h"
////#include "LoginPage.h"
////#include "Screen_class.h"
////#include "BrightnessBar.h"
////#include "settingsh.h"
////#include "Patch.h"
////
////
////void backend_level1_page(sf::RenderWindow& window) {
////	patch grid[5][9];
////
////	int x_change = 98;
////	int y_change = 112;
////
////	int first_x = 325;
////	int first_y = 103;
////
////	int current_y = 103;
////
////	grid[0][0].set_coords(first_x, first_y);
////
////
////	for (int i = 0; i < 5; i++)
////	{
////		int current_x = 325;
////		for (int j = 0; j < 9; j++) {
////			grid[i][j].set_coords(current_x, current_y);
////			current_x += x_change;
////		}
////		current_y += y_change;
////	}
////
////	int mouse_x = sf::Mouse::getPosition(window).x;
////	int mouse_y = sf::Mouse::getPosition(window).y;
////	cout << "x: " << mouse_x << endl;
////	cout << "y: " << mouse_y << endl;
////
////	Screen lawn("C:/Users/MK/OneDrive/Desktop/Plants vs Zombies/Project/Images/grid.png");
////	lawn.draw_on(window);
////
////}
//
//#pragma once
//#include <iostream>
//#include <SFML/Audio.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
//#include <ctime>
//
//#include "HomeScreen.h"
//#include "Level_Page.h"
//#include "Instructions Page.h"
//#include "Login_Page.h"
//#include "Screen_class.h"
//#include "BrightnessBar.h"
//#include "settingsh.h"
//#include "Patch.h"
//
//using namespace sf;
//using namespace std;
//
//void backend_level1_page(sf::RenderWindow& window) {
//
//	/*sf::Font font;
//	if (!font.loadFromFile("Burbank Big Condensed Font.otf")) {
//		std::cerr << "Failed to load font" << std::endl;
//		return;
//	}*/
//
//	patch grid[5][9];
//
//	int x_change = 102;
//	int y_change = 124;
//
//	int first_x = 318;
//	int first_y = 98;
//
//	int current_x = 318;
//	int current_y = 98;
//
//
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 9; j++) {
//			grid[i][j].set_coords(current_x, current_y);
//			current_x += x_change;
//		}
//		current_x = first_x;
//		current_y += y_change;
//	}
//	int mouse_x = sf::Mouse::getPosition(window).x;
//	int mouse_y = sf::Mouse::getPosition(window).y;
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//		cout << "x: " << mouse_x << " " << "y: " << mouse_y << endl;
//
//
//	Screen lawn("C:/Users/Saad/Desktop/Projects/Plants vs Zombies/Plants vs Zombies/Assets/Images/Maps/Day_Full Grass.png");
//	lawn.draw_on(window);
//
//	Screen watermelon_plant("C:/Users/Saad/Desktop/Projects/Plants vs Zombies/Plants vs Zombies/Assets/Images/Icons/img3.png");
//	watermelon_plant.setPosition(4, 5);
//
//
//	/*for (int i = 0; i < 5; i++) {
//		slot[i].slot_on_click(window);
//		slot[i].drawTo(window);
//	}*/
//
//
//	watermelon_plant.draw_on(window);
//}
//
//
//
