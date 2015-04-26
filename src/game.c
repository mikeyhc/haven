/* game.c
 * implementation of core game functionality
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <game.h>
#include <gui.h>
#include <SDL.h>
#include <SDL_image.h>
#define GL3_PROTOTYPES 1

extern SDL_Renderer *g_renderer;

SDL_Texture *load_texture(char *path)
{
	SDL_Texture *new_texture;
	SDL_Surface *loaded_surface;

	loaded_surface = IMG_Load(path);
	if(!loaded_surface) {
		fprintf(stderr, "Unable to load image %s! "
				"SDL_Image Error: %s\n", path,
				IMG_GetError());
		return NULL;
	}

	new_texture = SDL_CreateTextureFromSurface(g_renderer,
			loaded_surface);
	if(!new_texture) {
		fprintf(stderr, "Unable to create texture from %s! "
				"SDL Error: %s\n", path, SDL_GetError());
	}

	SDL_FreeSurface(loaded_surface);
	return new_texture;
}


int main_loop(void)
{
	SDL_Event e;
	char quit;
	SDL_Texture *texture;

	texture = load_texture("images/tileset.png");
	if(!texture) {
		fprintf(stderr, "failed to load texure image\n");
		return 1;
	}

	quit = 0;
	while(!quit) {
		while(SDL_PollEvent(&e))
			if(e.type == SDL_QUIT) quit = 1;
		SDL_RenderClear(g_renderer);
		SDL_RenderCopy(g_renderer, texture, NULL, NULL);
		SDL_RenderPresent(g_renderer);
	}

	SDL_DestroyTexture(texture);

	return 0;
}
