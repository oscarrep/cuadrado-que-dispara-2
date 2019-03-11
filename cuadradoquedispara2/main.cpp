#include <stdlib.h>
#include "SDL/include/SDL.h"

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#define R_SPEED 10
#define B_SPEED 10
#define N_PROJECTILES 20

struct Bullets
{
	SDL_Rect rect;
	bool draw = false;
};

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *win = SDL_CreateWindow("RedSquare",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		850,
		850,
		SDL_WINDOW_RESIZABLE);

	bool up = false, 
	   	 down = false, 
		 left = false, 
		 right = false;

	Bullets bullets[N_PROJECTILES];
	SDL_Event event;
	int index = 0;

	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
	SDL_Rect Rectangle = { 100,100,100,100 };
	bool loop = true;

	while (loop)
	{					 
		if (SDL_PollEvent(&event) != 0) 
		{
			switch (event.type)
			{
			case SDL_QUIT:loop = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) 
				{
				case SDL_SCANCODE_UP:
					up = true;
					break;

				case SDL_SCANCODE_DOWN:
					down = true;
					break;

				case SDL_SCANCODE_RIGHT:
					right = true;
					break;

				case SDL_SCANCODE_LEFT:
					left = true;
					break;

				case SDL_SCANCODE_ESCAPE:
					loop = false;
					break;

				case SDL_SCANCODE_SPACE:
					bullets[index].rect.x = Rectangle.x + 100;
					bullets[index].rect.y = Rectangle.y + 100/2 - 10/2;
					bullets[index].rect.h = bullets[index].rect.w=10;
					bullets[index].draw = true;

					if (index++ >= N_PROJECTILES)
					{
						index = 0;
					}
					
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
					up = false; 
					break;

				case SDL_SCANCODE_DOWN:
					down = false; 
					break;

				case SDL_SCANCODE_LEFT:
					left = false; 
					break;

				case SDL_SCANCODE_RIGHT:
					right = false; 
					break;

				}
				
			}
			if (up && Rectangle.y > 0)
				Rectangle.y -= R_SPEED;

			if (down && (Rectangle.y + Rectangle.h) < 850)
				Rectangle.y += R_SPEED;

			if (right && (Rectangle.x + Rectangle.w) < 850)
				Rectangle.x += R_SPEED;

			if (left && Rectangle.x > 0)
				Rectangle.x -= R_SPEED;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

		for (int i = 0; i < 21; i++) {
			SDL_RenderFillRect(renderer, &bullets[i].rect);
			bullets[i].rect.x += B_SPEED;
		}

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &Rectangle);
		SDL_RenderPresent(renderer);
		SDL_Delay(2);
	}


	SDL_Quit();
	return 0;
}