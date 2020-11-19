#include "Game.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
	Game game(hInstance);
	game.Initiate();
}