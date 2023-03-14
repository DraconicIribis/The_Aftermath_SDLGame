#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "Initialize.h"

std::vector<SDL_Rect> renderMap(SDL_Renderer* pRender, std::vector<SDL_Texture*> textureLib, std::vector<Level> levels);

void renderPlayer(SDL_Renderer* pRender, std::vector<SDL_Texture*> textureLib, std::vector<SDL_Rect> walls);

bool renderEnemies(SDL_Renderer* pRender, std::vector<SDL_Texture*> textureLib, Enemy &enemy, std::vector<SDL_Rect> walls, bool win);