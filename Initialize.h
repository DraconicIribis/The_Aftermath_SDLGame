#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"


//Structs
struct Player
{
	int revives = 3;
	bool hasKey = false;
	int xCoord = 0;
	int	yCoord = 0;
	int level = 1;
	bool key = false;
};

struct Enemy
{
	int type, level; //1-3, 1 is Golem, 2 is Bombdude, 3 is Rockmage
	bool fastReact, fastMove; //fastReact is whether they determine their move before player moves or after. fastMove is whether they move before or after the player
	int xCoord, yCoord, animate;
};

struct Level
{
	int rows, columns;
	std::vector<SDL_Texture*> tileMap = {};
};

extern Player player;

extern Enemy golem1, golem2, golem3, golem4, bombdude, rockmage;

//Functions
std::vector<SDL_Texture*> initTextures(SDL_Renderer* pRender);

std::vector<Level> initMap(std::vector<SDL_Texture*> textureLib);