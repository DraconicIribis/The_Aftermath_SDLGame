#include "Initialize.h"
#include <iostream>
#include <vector>
#include "SDL.h"

//Structs
Player player;

Enemy golem1 = { 1, 1, true, false, 4, -5 };
Enemy golem2 = { 1, 1, true, false, -3, -2 };
Enemy golem3 = { 1, 2, true, false, 10, 5 };
Enemy golem4 = { 1, 3, true, false, 33, -2 };
Enemy bombdude = { 2, 2, false, false, 12, -3, 0 };
Enemy rockmage = { 3, 3, true, true, 28, -1 };

//Functions
std::vector<SDL_Texture*> initTextures(SDL_Renderer* pRender) //Initialize textures for later use
{
	SDL_Surface* pBackSur = SDL_LoadBMP("background.bmp");
	SDL_Texture* pBackground = SDL_CreateTextureFromSurface(pRender, pBackSur);
	SDL_FreeSurface(pBackSur);

	SDL_Surface* pVoidSur = SDL_LoadBMP("void_tile.bmp");
	SDL_Texture* pVoid = SDL_CreateTextureFromSurface(pRender, pVoidSur);
	SDL_FreeSurface(pVoidSur);
	
	SDL_Surface* pFloorSur = SDL_LoadBMP("floor_tile.bmp");
	SDL_Texture* pFloor = SDL_CreateTextureFromSurface(pRender, pFloorSur);
	SDL_FreeSurface(pFloorSur);

	SDL_Surface* pWallSur = SDL_LoadBMP("wall_tile.bmp");
	SDL_Texture* pWall = SDL_CreateTextureFromSurface(pRender, pWallSur);
	SDL_FreeSurface(pWallSur);

	SDL_Surface* pPlayerSur = SDL_LoadBMP("player.bmp");
	SDL_Texture* pPlayer = SDL_CreateTextureFromSurface(pRender, pPlayerSur);
	SDL_FreeSurface(pPlayerSur);

	SDL_Surface* pBombSur = SDL_LoadBMP("bomb.bmp");
	SDL_SetColorKey(pBombSur, SDL_TRUE, SDL_MapRGB(pBombSur->format, 0, 255, 0));
	SDL_Texture* pBomb = SDL_CreateTextureFromSurface(pRender, pBombSur);
	SDL_FreeSurface(pBombSur);

	SDL_Surface* pGolemSur = SDL_LoadBMP("golem.bmp");
	SDL_SetColorKey(pGolemSur, SDL_TRUE, SDL_MapRGB(pGolemSur->format, 0, 255, 0));
	SDL_Texture* pGolem = SDL_CreateTextureFromSurface(pRender, pGolemSur);
	SDL_FreeSurface(pGolemSur);

	SDL_Surface* pPortalSur = SDL_LoadBMP("portal_tile.bmp");
	SDL_Texture* pPortal = SDL_CreateTextureFromSurface(pRender, pPortalSur);
	SDL_FreeSurface(pPortalSur);

	SDL_Surface* pBombPrimeSur = SDL_LoadBMP("bomb_primed.bmp");
	SDL_SetColorKey(pBombPrimeSur, SDL_TRUE, SDL_MapRGB(pBombPrimeSur->format, 0, 255, 0));
	SDL_Texture* pBombPrime = SDL_CreateTextureFromSurface(pRender, pBombPrimeSur);
	SDL_FreeSurface(pBombPrimeSur);

	SDL_Surface* pKeySur = SDL_LoadBMP("key.bmp");
	SDL_Texture* pKey = SDL_CreateTextureFromSurface(pRender, pKeySur);
	SDL_FreeSurface(pKeySur);

	SDL_Surface* pMageSur = SDL_LoadBMP("rockmage.bmp");
	SDL_SetColorKey(pMageSur, SDL_TRUE, SDL_MapRGB(pMageSur->format, 0, 255, 0));
	SDL_Texture* pMage = SDL_CreateTextureFromSurface(pRender, pMageSur);
	SDL_FreeSurface(pMageSur);

	SDL_Surface* pLockSur = SDL_LoadBMP("locked_tile.bmp");
	SDL_Texture* pLock = SDL_CreateTextureFromSurface(pRender, pLockSur);
	SDL_FreeSurface(pLockSur);


	std::vector<SDL_Texture*> textureLib = { pBackground, pVoid, pFloor, pWall, pPlayer, pBomb, pGolem, pPortal, pBombPrime, pKey, pMage, pLock };

	return textureLib;
}

std::vector<Level> initMap(std::vector<SDL_Texture*> textureLib)
{
	Level first = { 8, 10,
	{
		NULL,		   NULL,		  NULL,			 NULL,			NULL,		   NULL,		  NULL,			 textureLib[3], textureLib[3], textureLib[3],
		textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[7], textureLib[3], textureLib[3], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[3], textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3], textureLib[3], textureLib[1], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3], textureLib[2], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[3], textureLib[3], textureLib[2], textureLib[2], textureLib[3], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3],
		textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3]
	} };

	Level second = { 13, 7,
	{
		textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3],
		textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[2], textureLib[3], textureLib[2], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[1], textureLib[2], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[1], textureLib[2], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3],
		textureLib[3], textureLib[3], textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[3],
		textureLib[3], textureLib[7], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3]
	} };

	Level third = { 12, 13,
	{
		NULL,		   NULL,		  NULL,			 textureLib[3], textureLib[3], textureLib[7], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], NULL,
		NULL,		   NULL,		  textureLib[3], textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[3], textureLib[3], textureLib[2], textureLib[2], textureLib[3], NULL,
		NULL,		   NULL,		  textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3], NULL,
		NULL,		   textureLib[3], textureLib[3], textureLib[2], textureLib[2], textureLib[1], textureLib[1], textureLib[2], textureLib[1], textureLib[2], textureLib[2], textureLib[3], textureLib[3],
		NULL,		   textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3],
		NULL,		   textureLib[3], textureLib[2], textureLib[2], textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3], textureLib[3], textureLib[3],
		textureLib[3], textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[2], textureLib[3], textureLib[1], textureLib[2], textureLib[2], textureLib[3], NULL, NULL,
		textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3], textureLib[3], textureLib[2], textureLib[2], textureLib[3], NULL, NULL,
		textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[2], textureLib[3], NULL, NULL,
		textureLib[3], textureLib[2], textureLib[2], textureLib[2], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], textureLib[3], NULL, NULL,
		textureLib[3], textureLib[2], textureLib[2], textureLib[3], textureLib[3], NULL,		  NULL,			 NULL,			NULL,			NULL,		 NULL,			  NULL, NULL,
		textureLib[3], textureLib[3], textureLib[3], textureLib[3], NULL,		   NULL,		  NULL,			 NULL,			NULL,			NULL,		 NULL,			  NULL, NULL
	} };

	return { first, second, third };
}