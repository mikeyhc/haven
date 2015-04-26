/* game.c
 * implementation of core game functionality
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <game.h>
#include <global.h>
#include <gui.h>
#include <SDL.h>
#include <tileset.h>
#define GL3_PROTOTYPES 1

extern SDL_Renderer *g_renderer;

int main_loop(void)
{
	SDL_Event e;
	char quit;
	struct tileset tileset;

	if(!new_tileset_from_file(&tileset, "images/tileset.png",
				5, 15, 64, 50)) {
		fprintf(stderr, "failed to load texure image\n");
		return 1;
	}

	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0xFF);
	quit = 0;
	while(!quit) {
		while(SDL_PollEvent(&e))
			if(e.type == SDL_QUIT) quit = 1;

		SDL_RenderClear(g_renderer);
		render_tileset(&tileset, 50, 50, 0);
		render_tileset(&tileset, 80, 65, 1);
		render_tileset(&tileset, 20, 65, 2);
		render_tileset(&tileset, 50, 80, 4);
		render_tileset(&tileset, 108, 80, 1);
		render_tileset(&tileset, 78, 96, 12);
		SDL_RenderPresent(g_renderer);
	}

	delete_tileset(&tileset);

	return 0;
}
