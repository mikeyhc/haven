/* game.c
 * implementation of core game functionality
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <game.h>
#include <global.h>
#include <gui.h>
#include <SDL.h>
#include <tile.h>
#include <tileset.h>
#define GL3_PROTOTYPES 1

extern SDL_Renderer *g_renderer;

int main_loop(void)
{
	unsigned i;
	SDL_Event e;
	char quit;
	struct tileset tileset;
	int tile_vals[][3] =
		{ { 0,  50, 50},
		  { 1,  80, 65},
		  { 2,  20, 65},
		  { 4,  50, 80},
		  { 1, 108, 80},
		  {12,  78, 96},
		};
	struct tile tile[6];

	if(!new_tileset_from_file(&tileset, "images/tileset.png",
				5, 15, 64, 50)) {
		fprintf(stderr, "failed to load texure image\n");
		return 1;
	}

	for(i = 0; i < 6; i++)
		new_tile(tile + i, tile_vals[i][0], 0, 0, 0, 0, 0);

	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0xFF);
	quit = 0;
	while(!quit) {
		while(SDL_PollEvent(&e))
			if(e.type == SDL_QUIT) quit = 1;

		SDL_RenderClear(g_renderer);
		for(i = 0; i < 6; i++)
			render_tile(tile + i, &tileset, tile_vals[i][1],
					tile_vals[i][2]);
		SDL_RenderPresent(g_renderer);
	}

	delete_tileset(&tileset);

	return 0;
}
