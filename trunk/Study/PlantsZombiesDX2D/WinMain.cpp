#include "GameMain.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
{
	GameMain game(hInstance);
	game.Initiate();
}