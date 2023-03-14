#define SDL_MAIN_HANDLED

#include <iostream>
#include <windows.h>
#include <vector>
#include "SDL.h"
#include "Initialize.h"
#include "Get_Input.h"
#include "Render.h"

void close(SDL_Window* pWindow, SDL_Renderer* pRender, std::vector<SDL_Texture*> textures)
{
	for (SDL_Texture* texture : textures)
	{
		SDL_DestroyTexture(texture);
	}

	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRender);
	SDL_Quit;
}

int main()
{
	//Initialize window/renderer and get this baby started
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* pWindow = SDL_CreateWindow("The Aftermath: 2D Dungeon Game", 50, 50, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* pRender = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Initialize game and materials
	std::vector<SDL_Texture*> textureLib = initTextures(pRender);
	std::vector<Level> levels = initMap(textureLib);
	std::vector<Enemy> enemies = {golem1, golem2, golem3, golem4, bombdude, rockmage};

	bool go = true;
	bool win = true;
	int level = 1;

	while (go)
	{
		//Get Player Input
		go = getInput(go, pRender);

		if (!go)
		{
			break;
		}

		//Render Game
		std::vector<SDL_Rect> walls = renderMap(pRender, textureLib, levels);

		for (Enemy& enemy : enemies)
		{
			if (enemy.level == player.level && win)
			{
				win = renderEnemies(pRender, textureLib, enemy, walls, win);
			}
		}
		
		if(player.level != 4)
		{
			renderPlayer(pRender, textureLib, walls);
		}

		if (player.level == 4 && win)
		{
			SDL_Event e;

			SDL_Rect winSrc = { 0, 0, 500, 120 };
			SDL_Rect winDest = { 450, 250, 500, 120 };

			SDL_Surface* winSur = SDL_LoadBMP("win.bmp");
			SDL_SetColorKey(winSur, SDL_TRUE, SDL_MapRGB(winSur->format, 0, 255, 0));
			SDL_Texture* winText = SDL_CreateTextureFromSurface(pRender, winSur);
			SDL_FreeSurface(winSur);

			SDL_RenderCopy(pRender, winText, &winSrc, &winDest);

			if (SDL_PeepEvents(&e, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) != 0 && e.type == SDL_KEYDOWN)
			{
				go = false;
			}

			textureLib.push_back(winText);
		}
		else if (!win)
		{
			SDL_Event e;

			SDL_Rect winSrc = { 0, 0, 500, 120 };
			SDL_Rect winDest = { 450, 250, 500, 120 };

			SDL_Surface* winSur = SDL_LoadBMP("lose.bmp");
			SDL_SetColorKey(winSur, SDL_TRUE, SDL_MapRGB(winSur->format, 0, 255, 0));
			SDL_Texture* winText = SDL_CreateTextureFromSurface(pRender, winSur);
			SDL_FreeSurface(winSur);

			SDL_RenderCopy(pRender, winText, &winSrc, &winDest);

			if (SDL_PeepEvents(&e, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) != 0 && e.type == SDL_KEYDOWN)
			{
				go = false;
			}

			textureLib.push_back(winText);
		}

		SDL_RenderPresent(pRender);

		SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
	}

	//Nuke everything and erase all the evidence (destroy everything)
	close(pWindow, pRender, textureLib);

	return 0;
}