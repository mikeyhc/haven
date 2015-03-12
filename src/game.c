/* game.c
 * implementation of core game functionality
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <game.h>
#include <gui.h>
#include <SDL.h>

int main_loop(void)
{
	SDL_Event e;
	char quit;

	quit = 0;
	while(!quit) {
		while(SDL_PollEvent(&e)) 
			if(e.type == SDL_QUIT) quit = 1;
		render_screen();
	}

	return 0;
}
