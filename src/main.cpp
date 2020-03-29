#include "Asteroids.h"

int main()
{
	Asteroids game{ 1280, 720, 8, 8 };
	if (game.Construct(game.GetScreenWidth(), game.GetScreenHeight(), game.GetPixelWidth(), game.GetPixelHeight()))
		game.Start();
	return 0;
}