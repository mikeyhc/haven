/* game.c
 * implementation of core game functionality
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <game.h>
#include <gui.h>
#include <SDL.h>
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

static float color_list[][3] = {
		{ 1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
	};

int main_loop(void)
{
	SDL_Event e;
	char quit;
	int count, cur_color;

	quit = 0;
	cur_color = 1;
	for(count = 0; !quit; count++) {
		while(SDL_PollEvent(&e)) 
			if(e.type == SDL_QUIT) quit = 1;
		
		glClearColor(color_list[cur_color][0],
				color_list[cur_color][1],
				color_list[cur_color][2], 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		gl_swap_window();

		if(count == 100) {
			count = 0;
			cur_color = (cur_color + 1) % 3;
		}
	}

	return 0;
}
