#pragma once
#include <iostream>
#include "Player.h"
using namespace std;

#ifndef STAGE_H
#define STAGE_H



class Players
{
	string name;
	int levels;

public:
	bool checked;
	Players() : name(""), levels(0), checked(0) {}
	void setname(string a)
	{
		name = a;
	}
	void setLevels(int b)	
	{
		levels = b;
	}
	string getname()
	{
		return name;
	}
	int getLevels()
	{
		return levels;
	}
};
string currrent_stage = "Homescreen";
string previous_stage = "";
player admin;

#endif