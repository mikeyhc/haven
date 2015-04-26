/* gui.c
 * implementation of high level gui control functions
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <gui.h>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <shader_utils.h>
#include <stdio.h>

#define PROGRAM_NAME  "Haven Game"
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

static SDL_Window *g_window = NULL;
/* TODO: make this static again */
SDL_Renderer *g_renderer = NULL;
static SDL_GLContext *g_gl_context = NULL;

char initialize_gui(void)
{
	int img_flags;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL could not Initialize! SDL Error: %s\n",
				SDL_GetError());
		return 0;
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		fprintf(stderr, "Warning: Linear texture filtering not "
				"enabled!\n");
	if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0
			|| SDL_GL_SetAttribute(
				SDL_GL_CONTEXT_MINOR_VERSION, 2) < 0
			|| SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0
			|| SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) <0) {
		fprintf(stderr, "Failed to initialize OpenGL: %s\n",
				SDL_GetError());
		return 0;
	}

	g_window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(!g_window) {
		fprintf(stderr, "Window could not be created! SDL Error: %s\n",
				SDL_GetError());
		return 0;
	}
	
	g_gl_context = SDL_GL_CreateContext(g_window);
	if(!g_gl_context) {
		fprintf(stderr, "Could not create SDL GL Context! "
				"SDL Error: %s\n", SDL_GetError());
		return 0;
	}
	SDL_GL_SetSwapInterval(1);

	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC);
	if(!g_renderer) {
		fprintf(stderr, "Renderer could not be created! SDL Error: "
				"%s\n", SDL_GetError());
		return 0;
	}

	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	img_flags = IMG_INIT_PNG;
	if(!(IMG_Init(img_flags) & img_flags)) {
		fprintf(stderr, "SDL_image could not initialize. SDL_image "
				"Error: %s\n", IMG_GetError());
		return 0;
	}

	return 1;
}

void quit_gui(void)
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	g_renderer = NULL;
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

void render_screen(void)
{
	SDL_RenderPresent(g_renderer);
}

void gl_swap_window(void)
{
	SDL_GL_SwapWindow(g_window);
}
