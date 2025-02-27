#pragma once
#pragma once
#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "HomeScreen.h"
#include "BrightnessBar.h"
#include "Screen_class.h"
using namespace sf;
using namespace std;

#include  "Button.h"
#include "TextBox.h"

void back_end_settings_page(RenderWindow& win, BrightnessBar& brightnessBar, BrightnessBar& VolumeBar, Event& ev,Music& homescreen_music,RectangleShape& brightnessrect)
{
	//createBackground_Homescreen(win);
	Screen settings_Background("Assets/Images/Menu/settings_background.jpg");
	settings_Background.draw_on(win);

	Font font;
	if (!font.loadFromFile("Burbank Big Condensed Font.otf"))
	{
		cout << "Error loading font file/n";
		return;
	}

	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Assets/Images/Menu/settings.png"))
	{
		cout << "Error loading background image/n";
		return;
	}
	Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setPosition((win.getSize().x - backgroundSprite.getLocalBounds().width) / 2, (win.getSize().y - backgroundSprite.getLocalBounds().height) / 2);
	backgroundSprite.setScale(1.0f, 1.0f);
	win.draw(backgroundSprite);

	Image Back_image;
	if (!Back_image.loadFromFile("Assets/Images/Buttons/back_2.png")) {
		cout << "asidhua";
	}
	Texture Back;
	Back.loadFromImage(Back_image);

	Image main_menu;
	main_menu.loadFromFile("Assets/Images/Buttons/main_menu.png");
	Texture main_menu_text;
	main_menu_text.loadFromImage(main_menu);

	Image restart_im;
	restart_im.loadFromFile("Assets/Images/Buttons/restart.png");
	Texture restart_text;
	restart_text.loadFromImage(restart_im);

	int x = 500;
	int y = 500;

	Button bu("", x - 17, y, 310, 70, Color::White, font, Color::White, 20);

	BrightnessBar replace_bright(510, 280, 250, 25, Color(0, 128, 0), Color::White, 1.0f);
	BrightnessBar replace_volume(525, 360, 220, 25, Color(0, 128, 0), Color::White, 1.0f);

	if (win.pollEvent(ev))
	{
		if (ev.type == Event::MouseButtonPressed)
		{
			if (ev.mouseButton.button == Mouse::Left)
			{
				float x = static_cast<float>(ev.mouseButton.x);
				float y = static_cast<float>(ev.mouseButton.y);

				if (brightnessBar.get_bar().getGlobalBounds().contains(x, y))
				{
					float newWidth = x - brightnessBar.getPosition().x;
					brightnessBar.setSize(newWidth, brightnessBar.getSize().y);
				}
				else if (replace_bright.get_bar().getGlobalBounds().contains(x, y))
				{
					float newWidth = brightnessBar.getSize().x + 10;
					brightnessBar.setSize(newWidth, brightnessBar.getSize().y);
				}
				else if (VolumeBar.get_bar().getGlobalBounds().contains(x, y))
				{
					float newWidth = x - VolumeBar.getPosition().x;
					VolumeBar.setSize(newWidth, VolumeBar.getSize().y);
				}
				else if (replace_volume.get_bar().getGlobalBounds().contains(x, y))
				{
					float newWidth = VolumeBar.getSize().x + 10;
					VolumeBar.setSize(newWidth, VolumeBar.getSize().y);
				}
			}
		}
		else if (ev.type == Event::Closed)
		{
			win.close();
		}
	}

	homescreen_music.setVolume(VolumeBar.getSize().x / 2.2f);
	
	brightnessrect.setFillColor(Color(0, 0, 0, 255 - brightnessBar.getSize().x));
	//cout << brightnessBar.getSize().x / 2.5f << endl;
	win.draw(brightnessrect);

	x = 560;
	y = 230;

	Button BrightButton("Brightness", x, y, 100, 30, Color::Black, font, Color::Transparent, 20);
	BrightButton.setlocation_text(x + 15, y + 5);
	BrightButton.increase_text_size(30, 30);
	BrightButton.getText().setStyle(Text::Regular);

	Button SoundButton("Volume", x, y - 80, 100, 30, Color::Black, font, Color::Transparent, 20);
	SoundButton.setlocation_text(x + 35, y + 85);
	SoundButton.increase_text_size(30, 30);
	SoundButton.getText().setStyle(Text::Regular);

	Button MainMenu("", x - 17, y + 214, 200, 40, Color::White, font, Color::White, 20);

	Button Restart("", x - 17, y + 170, 202, 40, Color::White, font, Color::White, 20);

	brightnessBar.drawTo(win);

	VolumeBar.drawTo(win);

	BrightButton.drawTo(win);

	SoundButton.drawTo(win);

	bu.increase_text_size(60, 20);
	bu.setTexture(&Back);

	MainMenu.setTexture(&main_menu_text);

	Restart.setTexture(&restart_text);

	bu.setlocation_text(x, y);
	bu.drawTo(win);

	MainMenu.drawTo(win);

	Restart.drawTo(win);

	bu.on_button(win);
	bu.on_click(win, previous_stage, currrent_stage, previous_stage);

	MainMenu.on_button(win);
	MainMenu.on_click(win, "Homescreen", currrent_stage, previous_stage);
}