#pragma once
#include <iostream>
#include "Levels.h"
#include "Sun.h"
#include "Screen_class.h"
#include "PlantFactory.h"
#include "PlantFactory.h"
#include "Football Zombie.h"
#include "Zombie Factoryr.h"
#include "Seed.h"
#include "Button.h"
#include "settingsh.h"
using namespace std;


class Level2 : public Levels
{
    Seed** seed;
    Screen* lawn;
    bool a;
    int score;
    int plants;

public:
    Level2(RenderWindow& window) : Levels(1,3)
    {
        window.setFramerateLimit(60);
        types_of_zombies = 1;
        plants = 2;
        total_plants = 5;
        num_of_LawnMowers = 4;
        
        seed = new Seed * [total_plants];
        int seeds_x = 33;
        sf::Font font;
        /////////////////////////////////////////////Back Button//////////////////////////////////////////////////////
        Button Back_btn("", 1050, 0, 200, 100, sf::Color::Green, font, sf::Color::White, 28);
        Back_btn.setlocation_text(1110, 10);

        sf::Image back_btn_image;
        back_btn_image.loadFromFile("Assets/Images/Buttons/back.png");

        sf::Texture back_btn_texture;
        back_btn_texture.loadFromImage(back_btn_image);

        Back_btn.setTexture(&back_btn_texture);

        /////////////////////////////////////////////Settings Page//////////////////////////////////////////////////////
        BrightnessBar brightnessBar(510, 280, 250, 25, Color(0, 128, 0), Color::White, 1.0f);
        BrightnessBar VolumeBar(525, 360, 220, 25, Color(0, 128, 0), Color::White, 1.0f);
        sf::Music Homescreen_Music;
        Homescreen_Music.openFromFile("C:/Users/MK/OneDrive/Desktop/Plants vs Zombies/Project/Music/Homescreen_Grasswalk.ogg");
        bool music_home = true;
        sf::RectangleShape brightnessRect(sf::Vector2f(window.getSize().x, window.getSize().y));
        brightnessRect.setFillColor(sf::Color(0, 0, 0, 0));

        /////////////////////////////////////////////        Seeds           //////////////////////////////////////////////////////
        seed[0] = new Seed("Assets/Images/Cards/peacard.png", seeds_x, 110, "Pea");
        seed[1] = new Seed("Assets/Images/Cards/sunflowercard.png", seeds_x, 203, "Sun");
        seed[2] = new Seed("Assets/Images/Cards/repeatercard.png", seeds_x, 296, "Rep");
        seed[3] = new Seed("Assets/Images/Cards/card_wallnut.png", seeds_x, 388, "Wall");
        seed[4] = new Seed("Assets/Images/Cards/snowcard.png", seeds_x, 482, "Snow");
        seed[5] = new Seed("Assets/Images/Cards/cherrycard.png", seeds_x, 575, "Cherry");
        score = 0;
        a = true;
        bool settings_page = false;
        lawn = new Screen("Assets/Images/Maps/3 patch.png");

        TextBox txt("", 30, (window.getSize().x - (300.0 / 2)), 30, 30, 300, Color::Black, font, Color::White, Color::Black, false);
        String Score = "";
        score = 50;

        Dancer_Zombie db(grid);
        Screen bg("Assets/Images/Maps/3 patch.png");
        //level_timer.restart();
        while (a)
        {
            window.clear();
            Score = to_string(score);
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            draw_BackGround(window);
            //bg.draw_on(window);
            drawBar(window);

            txt.drawTo(window);
            txt.setText(Score);

            Back_btn.drawTo(window);
            Back_btn.on_button(window);
            Back_btn.on_click(window, "Settings Page", currrent_stage, previous_stage);
            if (currrent_stage == "Settings Page")
            {
                settings_page = true;

            }
            while (settings_page)
            {
                window.display();
                back_end_settings_page(window, brightnessBar, VolumeBar, event, Homescreen_Music, brightnessRect);
                if (currrent_stage == "Level 2")
                    settings_page = false;
                if (currrent_stage == "Homescreen")
                {
                    cout << "Home" << endl;
                    settings_page = false;
                    a = false;
                }
            }
            for (int i = 0;i < plants;i++)
            {
                seed[i]->draw_on(window);
                seed[i]->drag_seed();
                if (seed[i]->drop_seed() && seed[i]->enough(score))
                {
                    
                    int* cor = set_Coordinates(Mouse::getPosition(window).x, Mouse::getPosition(window).y, grid);
                    if (seed[i]->getName() != "Wall")
                    {
                        if (can_be_placed(grid, cor))
                        {
                            seed[i]->Decrement_Score(score);
                            Run_Plant_Factory(i, window, cor);
                        }
                    }
                    else
                    {
                        //Revolving only for Wallnut
                        if (can_be_placed(grid, cor))
                        {
                            if (can_be_placed(grid, cor, 1))
                            {
                                seed[i]->Decrement_Score(score);
                                Run_Plant_Factory(i, window, cor);
                            }
                        }
                    }
                }
                draw_Plants(window, i, types_of_zombies, zfac, grid, score);
            }
            /*db.move_zombie();
            db.draw_zombie(window);*/


            for (int i = 0; i < types_of_zombies; i++) {
                zfac[i]->run_factory(window);
            }


            sfac.run_factory(window, score);

            for (int i = 0;i < num_of_LawnMowers;i++)
            {   
                if (i == 0) {
                
                }
                else {
                    mowers[i]->draw_on(window);
                    mowers[i]->update(window, zfac, types_of_zombies, grid);
                }
            }

            if (level_timer.getElapsedTime().asSeconds() >= limit) {
                a = false;
                currrent_stage = "Game Won";
                admin.increaseLevelsUnlocked(3);
                level_timer.restart();
            }


            zombie_interaction(zfac, pfac, types_of_zombies, plants, grid,a);

            window.display();
        }


        for (int i = 0; i < types_of_zombies; i++)
        {
            for (int j = 0; j < zfac[i]->numZombies; j++) {
                delete zfac[i]->zombies[j];
            }
        }
        delete[] zfac;

        for (int i = 0; i < plants; i++)
        {
            for (int j = 0; j < pfac[i]->size; j++) {
                delete pfac[i]->plants[j];
            }
        }
        delete[] pfac;

        for (int i = 0; i < num_of_LawnMowers; i++)
        {
            delete mowers[i];
        }
        delete[] mowers;

        delete[] seed;
    }
    void draw_BackGround(RenderWindow& window)
    {
        lawn->draw_on(window);
    }
    void Run_Plant_Factory(int plant_no, RenderWindow& window, int* cor)
    {
        pfac[plant_no]->Run_factory(window, cor);
    }
    void drawBar(RenderWindow& window)
    {
        bar_texture.loadFromImage(bar_image);
        bar.setTexture(bar_texture);
        bar.setScale(0.79, 0.77);
        bar.setPosition(bar_x, bar_y);
        window.draw(bar);
        window.draw(replace);
        window.draw(box);
    }
    void draw_Plants(RenderWindow& window, int a, int types_of_zombies, Zombie_Factory** zfac, patch grid[][9], int& score)
    {
        pfac[a]->draw_Factory(window, types_of_zombies, zfac, grid, score);
        pfac[a]->move_plant(window, grid);
    }


};