#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include "SDL.h"
#include "Render.h"
#include "Initialize.h"

std::vector<SDL_Rect> renderMap(SDL_Renderer* pRender, std::vector<SDL_Texture*> textureLib, std::vector<Level> levels)
{
	//Render the background
	SDL_Rect backSrc = { 0, 0, 1280, 720 };
	SDL_Rect backDest = { 0, 0, 1280, 720 };

	SDL_RenderCopy(pRender, textureLib[0], &backSrc, &backDest);

	std::vector<SDL_Rect> walls;

	//Render the levels in order
	for (int index = 0; index < levels.size(); index++)
	{
		for (int i = 0; i < levels[index].tileMap.size(); i++)
		{
			SDL_Rect srcRect = { 0, 0, 60, 60 };
			SDL_Rect destRect = { 60 * (i % (levels[index].columns)) + 360 + (player.xCoord * 60) + (780 * index), 60 * (i / levels[index].columns) - 60 + (player.yCoord * 60), 60, 60}; //Place the maps dependent upon player coords (move instead of moving the player character), object coords (found by row and column number in the vector/level object), what level it is (shifted by 780 pixels index number of times), and subtracted accordingly depending upon level offset

			if (levels[index].tileMap[i] == textureLib[3] || levels[index].tileMap[i] == textureLib[1] || levels[index].tileMap[i] == textureLib[7])
			{
				walls.push_back(destRect);
			}

			SDL_RenderCopy(pRender, levels[index].tileMap[i], &srcRect, &destRect);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		SDL_Rect srcRect = { 0, 0, 40, 40 };
		SDL_Rect destRect;

		SDL_Rect doorSrc = { 0, 0, 60, 60 };
		SDL_Rect doorDest;

		switch (i)
		{
			case 0:
				destRect = { 839 + (player.xCoord * 60), (player.yCoord * 60), 60, 60 };
				doorDest = { 599 + (player.xCoord * 60), (player.yCoord * 60), 60, 60 };
				break;

			case 1:
				destRect = { 1439 + (player.xCoord * 60), (player.yCoord * 60) + 180, 60, 60 };
				doorDest = { 1199 + (player.xCoord * 60), 660 + (player.yCoord * 60), 60, 60 };
				break;

			case 2:
				destRect = { 2099 + (player.xCoord * 60), (player.yCoord * 60) + 420, 60, 60 };
				doorDest = { 2219 + (player.xCoord * 60), (player.yCoord * 60) - 60, 60, 60 };
				break;
		}

		if(!player.key && player.level - 1 == i)
		{
			//Render key
			SDL_RenderCopy(pRender, textureLib[9], &srcRect, &destRect);

			//Render lock
			SDL_RenderCopy(pRender, textureLib[11], &doorSrc, &doorDest);
		}
	}

	//Render the HUD
	SDL_Surface* pLevelsSur = SDL_LoadBMP("levels.bmp");
	SDL_Texture* pLevels = SDL_CreateTextureFromSurface(pRender, pLevelsSur);
	SDL_FreeSurface(pLevelsSur);

	SDL_Rect levelSrc = { 0, 0, 320, 80 };
	SDL_Rect levelDest = { 300, 600, 500, 120 };

	SDL_RenderCopy(pRender, pLevels, &levelSrc, &levelDest);

	SDL_Surface* pCountSur = SDL_LoadBMP("level_count.bmp");
	SDL_Texture* pCount = SDL_CreateTextureFromSurface(pRender, pCountSur);
	SDL_FreeSurface(pCountSur);

	SDL_Rect countSrc = { 0, 0, 109, 64 };
	SDL_Rect countDest = { 870, 640, 109, 64 };

	SDL_RenderCopy(pRender, pCount, &countSrc, &countDest);


	std::string levelFile = std::to_string(player.level) + ".bmp";
	const char* lvlFile = levelFile.c_str();

	SDL_Surface* pLvlCountSur = SDL_LoadBMP(lvlFile);
	SDL_Texture* pLvlCount = SDL_CreateTextureFromSurface(pRender, pLvlCountSur);
	SDL_FreeSurface(pLvlCountSur);

	SDL_Rect lvlCountSrc = { 0, 0, 109, 64 };
	SDL_Rect lvlCountDest = { 790, 630, 109, 64 };

	SDL_RenderCopy(pRender, pLvlCount, &lvlCountSrc, &lvlCountDest);

	return walls;
}

void renderPlayer(SDL_Renderer* pRender, std::vector<SDL_Texture*> textureLib, std::vector<SDL_Rect> walls)
{
	//Set player rects in the middle of the screen
	SDL_Rect playerSrc = { 0, 0, 46, 96 };
	SDL_Rect playerDest = { 599, 260, 46, 96 };
	SDL_Rect playerHitbox = { 600, 322, 39, 30 };

	switch (player.level) //Check to see if the player picked up a key
	{
		case 1:
			if (player.xCoord == -4 && player.yCoord == 5)
			{
				player.key = true;
			}
			break;

		case 2:
			if (player.xCoord == -14 && player.yCoord == 2)
			{
				player.key = true;
			}
			break;
		case 3:
			if (player.xCoord == -25 && player.yCoord == -2)
			{
				player.key = true;
			}
			break;
	}

	switch (player.level) //Check to see if the player is attempting to enter the portal after grabbing the key, then, if so, change the level
	{
	case 1:
		if (player.xCoord == 0 && player.yCoord == 5 && player.key)
		{
			player.level++;
			player.xCoord = -12;
			player.yCoord = -4;
			player.key = false;
		}
		break;

	case 2:
		if (player.xCoord == -10 && player.yCoord == -6 && player.key)
		{
			player.level++;
			player.xCoord = -30;
			player.yCoord = -3;
			player.key = false;
		}
		break;

	case 3:
		if (player.xCoord == -27 && player.yCoord == 6 && player.key)
		{
			player.level++;
			player.xCoord = 10;
			player.yCoord = 10;
		}
		break;
	}

	for (SDL_Rect wall : walls) //Check to see if a wall is where the player should be
	{
		if (SDL_HasIntersection(&playerHitbox, &wall)) //If a wall overlaps with the player, change the coords back to their original position.
		{
			SDL_Event prevInput;

			SDL_RenderClear(pRender);

			SDL_PeepEvents(&prevInput, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT); //Read the event in the queue, which was put there during player input detection

			switch (prevInput.key.keysym.sym)
			{
				case SDLK_w:
				case SDLK_UP:
					player.yCoord--;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					player.xCoord--;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					player.yCoord++;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					player.xCoord++;
					break;
			}

			renderMap(pRender, textureLib, initMap(textureLib));

			break;
		}
	}

	SDL_RenderCopy(pRender, textureLib[4], &playerSrc, &playerDest);
}

bool renderEnemies(SDL_Renderer* pRender, std::vector<SDL_Texture*> textureLib, Enemy &enemy, std::vector<SDL_Rect> walls, bool win)
{
	SDL_Event prevInput;
	bool playerMove = false;
	std::vector<SDL_Keycode> playerEvents = { SDLK_w, SDLK_UP, SDLK_a, SDLK_LEFT, SDLK_s, SDLK_DOWN, SDLK_d, SDLK_RIGHT };
	
	SDL_PeepEvents(&prevInput, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);

	for (SDL_Keycode keyEvent : playerEvents)
	{
		if (prevInput.key.keysym.sym == keyEvent && prevInput.type == SDL_KEYUP)
		{
			playerMove = true;
		}
	}

	//Initialize Enemy Id to Correct Sprite
	int textureId = 0;

	switch (enemy.type)
	{
		case 1:
			textureId = 6;
			break;

		case 2:
			textureId = 5;
			break;

		case 3:
			textureId = 10;
			break;
	}

	SDL_Rect enemySrc = { 0, 0, 64, 94 };

	std::vector<int> origCoords = { enemy.xCoord, enemy.yCoord };

	if(playerMove)
	{
		switch (enemy.type)
		{
			case 1: //Golem
				if (player.level == enemy.level)
				{
					if (-player.yCoord == enemy.yCoord)
					{
						if (-player.xCoord > 1 + enemy.xCoord)
						{
							enemy.xCoord++;
						}
						else if (-player.xCoord < enemy.xCoord - 1)
						{
							enemy.xCoord--;
						}
					}
					else if (((-player.xCoord == 1 + enemy.xCoord || -player.xCoord == enemy.xCoord - 1) && -player.yCoord == enemy.yCoord) || ((-player.yCoord == 1 + enemy.yCoord || -player.yCoord == enemy.yCoord - 1) && -player.xCoord == enemy.xCoord))
					{
						enemy.xCoord = -player.xCoord;
						enemy.yCoord = -player.yCoord;
					}
					else
					{
						if (-player.yCoord > 1 + enemy.yCoord || (-player.yCoord == 1 + enemy.yCoord && enemy.xCoord != -player.xCoord))
						{
							enemy.yCoord++;
						}
						else if (-player.yCoord < enemy.yCoord - 1 || (-player.yCoord == enemy.yCoord - 1 && enemy.xCoord != -player.xCoord))
						{
							enemy.yCoord--;
						}
					}
				}

				break;

			case 2: //Bombdude
				if (enemy.animate == 1)
				{
					enemy.animate++;
				}

				if (player.level == enemy.level && enemy.animate == 0)
				{
					if (-player.yCoord == enemy.yCoord)
					{
						if (-player.xCoord > 1 + enemy.xCoord)
						{
							enemy.xCoord++;
						}
						else if (-player.xCoord < enemy.xCoord - 1)
						{
							enemy.xCoord--;
						}
					}
					else if (((-player.xCoord == 1 + enemy.xCoord || -player.xCoord == enemy.xCoord - 1) && -player.yCoord == enemy.yCoord) || ((-player.yCoord == 1 + enemy.yCoord || -player.yCoord == enemy.yCoord - 1) && -player.xCoord == enemy.xCoord))
					{
						enemy.animate++;
					}
					else
					{
						if (-player.yCoord > 1 + enemy.yCoord || (-player.yCoord == 1 + enemy.yCoord && enemy.xCoord != -player.xCoord))
						{
							enemy.yCoord++;
						}
						else if (-player.yCoord < enemy.yCoord - 1 || (-player.yCoord == enemy.yCoord - 1 && enemy.xCoord != -player.xCoord))
						{
							enemy.yCoord--;
						}
					}
				}

				break;

			case 3:
				if (abs(-player.yCoord - enemy.yCoord) == abs(-player.xCoord - enemy.xCoord))
				{
					if (-player.xCoord < enemy.xCoord + 1)
					{
						if (-player.yCoord < enemy.yCoord + 1)
						{
							enemy.xCoord--;
							enemy.yCoord--;
						}
						else
						{
							enemy.xCoord--;
							enemy.yCoord++;
						}
					}
					else if (-player.xCoord > enemy.xCoord - 1)
					{
						if (-player.yCoord > enemy.yCoord + 1)
						{
							enemy.xCoord++;
							enemy.yCoord++;
						}
						else
						{
							enemy.xCoord++;
							enemy.yCoord--;
						}
					}
				}
				else if (((-player.xCoord == 1 + enemy.xCoord || -player.xCoord == enemy.xCoord - 1) && -player.yCoord == enemy.yCoord) || ((-player.yCoord == 1 + enemy.yCoord || -player.yCoord == enemy.yCoord - 1) && -player.xCoord == enemy.xCoord))
				{
					enemy.xCoord = -player.xCoord;
					enemy.yCoord = -player.yCoord;
				}

				break;
		}
	}

	if (enemy.animate == 1)
	{
		textureId = 8;
	}
	else if (enemy.animate == 2)
	{
		if ((abs(-player.xCoord - enemy.xCoord) == 1 && abs(-player.yCoord - enemy.yCoord) == 1) || (-player.xCoord == enemy.xCoord && abs(-player.yCoord - enemy.yCoord) == 1) || (-player.yCoord == enemy.yCoord && abs(-player.xCoord - enemy.xCoord) == 1) || (-player.yCoord == enemy.yCoord && -player.xCoord == enemy.xCoord))
		{
			win = false;
		}

		enemy.type = 0;
		enemy.xCoord = 100;
		enemy.yCoord = 100;
	}

	//Initialize Enemy Hitbox
	SDL_Rect enemyHit = { 609 + (enemy.xCoord * 60) + (player.xCoord * 60), 304 + (enemy.yCoord * 60) + (player.yCoord * 60), 30, 30 };

	for (SDL_Rect wall : walls)
	{
		if (SDL_HasIntersection(&enemyHit, &wall))
		{
			enemy.xCoord = origCoords[0];
			enemy.yCoord = origCoords[1];
		}
	}

	SDL_Rect playerRect = { 600, 322, 39, 30 };

	if (SDL_HasIntersection(&enemyHit, &playerRect))
	{
		win = false;
	}

	SDL_Rect enemyDest = { 599 + (enemy.xCoord * 60) + (player.xCoord * 60), 260 + (enemy.yCoord * 60) + (player.yCoord * 60), 64, 94 };

	SDL_RenderCopy(pRender, textureLib[textureId], &enemySrc, &enemyDest);

	return win;
}