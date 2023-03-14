#include <iostream>
#include "SDL.h"
#include "Get_Input.h"
#include "Initialize.h"

bool getInput(bool go, SDL_Renderer* pRender) //Get player input by keys
{
	SDL_Event e = {};

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			go = false;
			break;
		}
		else if (e.type == SDL_KEYUP)
		{
			SDL_Keycode key = e.key.keysym.sym;

			switch (key)
			{
				case SDLK_ESCAPE:
					go = false;
					break;

				case SDLK_w:
				case SDLK_UP:
					player.yCoord++;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					player.xCoord++;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					player.yCoord--;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					player.xCoord--;
					break;
			}
		}
	}

	SDL_PushEvent(&e); //Pollevent removes the event from the queue, so push it back into the queue for later use

	return go;
}