#include <stdlib.h>
#include "SDL/include/SDL.h"

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Event event;
	
	bool loop = true;
	
	SDL_Window *win = SDL_CreateWindow("RedSquare",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		850,
		800,
		SDL_WINDOW_RESIZABLE);

	SDL_Renderer* renderer = SDL_CreateRenderer(win, 0, 0);

	
	SDL_Rect rect = { 100,100,100,100 };

	while (loop)
	{	//				  {pos.x,pos.y,w,h}
		SDL_Rect bullet = { rect.x+50,rect.y+50, 10, 10 };

		if (SDL_PollEvent(&event) != 0) {
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					if (rect.y > 0) {
						rect.y -= 20;
					}
					break;
				case SDLK_DOWN:
					if (rect.y < 800 - rect.h) {
						rect.y += 20;
					}
					break;
				case SDLK_RIGHT:
					if (rect.x < (850 - rect.w)) {
						rect.x += 20;
					}
					break;
				case SDLK_LEFT:
					if (rect.x > 0) {
						rect.x -= 20;
					}
					break;
				case SDLK_ESCAPE:
					loop = false;
					break;
				case SDLK_SPACE:
					bullet.x += 20;
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
		SDL_RenderFillRect(renderer, &bullet);
		SDL_RenderPresent(renderer);
	}


	SDL_Quit();
	return 0;
}