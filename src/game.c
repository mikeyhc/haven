/* game.c
 * implementation of core game functionality
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <game.h>
#include <global.h>
#include <gui.h>
#include <SDL.h>
#include <texture.h>
#define GL3_PROTOTYPES 1

extern SDL_Renderer *g_renderer;

int main_loop(void)
{
	SDL_Event e;
	char quit;
	struct texture texture;
	SDL_Rect sprite_clips[4];
	int i;

	new_texture(&texture);
	if(!load_from_file(&texture, "images/tileset.png")) {
		fprintf(stderr, "failed to load texure image\n");
		return 1;
	}

	for(i = 0; i < 4; i++) {
		if(i % 2 == 0)
			sprite_clips[i].x = 100;
		else
			sprite_clips[i].x =   0;
		if(i > 1)
			sprite_clips[i].y = 100;
		else
			sprite_clips[i].y =   0;
		sprite_clips[i].w = 100;
		sprite_clips[i].h = 100;
	}

	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	quit = 0;
	while(!quit) {
		while(SDL_PollEvent(&e))
			if(e.type == SDL_QUIT) quit = 1;

		SDL_RenderClear(g_renderer);
		render(&texture, 0, 0, sprite_clips);
		render(&texture, SCREEN_WIDTH - sprite_clips[1].w, 0,
				sprite_clips + 1);
		render(&texture, 0, SCREEN_HEIGHT - sprite_clips[2].h,
				sprite_clips + 2);
		render(&texture, SCREEN_WIDTH - sprite_clips[3].w,
				SCREEN_HEIGHT - sprite_clips[3].h,
				sprite_clips + 3);
		SDL_RenderPresent(g_renderer);
	}

	delete_texture(&texture);

	return 0;
}
