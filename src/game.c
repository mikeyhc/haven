/* game.c
 * implementation of core game functionality
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <chunk.h>
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
	unsigned x, y, z;
	SDL_Event e;
	char quit;
	struct tileset tileset;
	struct chunk chunk;
	struct tile tile;

	if(!new_tileset_from_file(&tileset, "images/tileset.png",
				5, 15, 64, 50)) {
		fprintf(stderr, "failed to load texure image\n");
		return 1;
	}

	new_chunk(&chunk);
	new_tile(&tile, 0, 0, 0, 0, 0, 0);
	for(x = 0; x < CHUNK_X; x++)
		for(y = 0; y < CHUNK_Y; y++)
			for(z = 0; z < CHUNK_Z; z++)
				set_chunk_tile(&chunk, &tile, x, y, z);
	delete_tile(&tile);


	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0xFF);
	quit = 0;
	while(!quit) {
		while(SDL_PollEvent(&e))
			if(e.type == SDL_QUIT) quit = 1;

		SDL_RenderClear(g_renderer);
		render_chunk(&chunk, &tileset, 100, 100, 0);
		SDL_RenderPresent(g_renderer);
	}

	delete_chunk(&chunk);
	delete_tileset(&tileset);

	return 0;
}
