/* texture.c
 * implementation of the texture structure helper methods
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>
#include <texture.h>

extern SDL_Renderer *g_renderer;

void new_texture(struct texture *texture)
{
	assert(texture);

	texture->texture = NULL;
	texture->width = texture->height = -1;
}

void delete_texture(struct texture *texture)
{
	assert(texture);

	if(texture->texture)
		SDL_DestroyTexture(texture->texture);
	texture->texture = NULL;
	texture->width = texture->height = -1;
}

char load_from_file(struct texture *texture, const char *path)
{
	SDL_Surface *loaded_surface;

	loaded_surface = IMG_Load(path);
	if(!loaded_surface) {
		fprintf(stderr, "Unable to load image %s! "
				"SDL_Image Error: %s\n", path,
				IMG_GetError());
		return 0;
	}

	texture->texture = SDL_CreateTextureFromSurface(g_renderer,
			loaded_surface);
	if(!texture->texture) {
		fprintf(stderr, "Unable to create texture from %s! "
				"SDL Error: %s\n", path, SDL_GetError());
	}

	texture->width = loaded_surface->w;
	texture->height = loaded_surface->h;

	SDL_FreeSurface(loaded_surface);
	return 1;
}

void render(struct texture *texture, int x, int y, SDL_Rect *clip)
{
	SDL_Rect render_quad;

	assert(texture);

	render_quad.x = x;
	render_quad.y = y;

	if(clip) {
		render_quad.w = clip->w;
		render_quad.h = clip->h;
	} else {
		render_quad.w = texture->width;
		render_quad.h = texture->height;
	}

	if(render_quad.x + render_quad.w < 0 ||
			render_quad.y + render_quad.h < 0)
		return;

	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(g_renderer,
			x,
			y + render_quad.h * 0.4,
			x,
			y + render_quad.h);
	SDL_RenderDrawLine(g_renderer,
			x,
			y + render_quad.h,
			x + render_quad.w / 2,
			y + render_quad.h * 1.4);
	SDL_RenderDrawLine(g_renderer,
			x + render_quad.w / 2,
			y + render_quad.h * 1.4,
			x + render_quad.w,
			y + render_quad.h);
	SDL_RenderDrawLine(g_renderer,
			x + render_quad.w,
			y + render_quad.h,
			x + render_quad.w,
			y + render_quad.h * 0.4);
	SDL_RenderDrawLine(g_renderer,
			x + render_quad.w / 2,
			y + render_quad.h * 1.4,
			x + render_quad.w /2,
			y + render_quad.h * 0.8);
	SDL_RenderCopy(g_renderer, texture->texture, clip, &render_quad);
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawLine(g_renderer,
			x,
			y + render_quad.h  * 0.4,
			x + render_quad.w / 2, y);
	SDL_RenderDrawLine(g_renderer,
			x + render_quad.w / 2,
			y,
			x + render_quad.w,
			y + render_quad.h * 0.4);
	SDL_RenderDrawLine(g_renderer,
			x + render_quad.w,
			y + render_quad.h * 0.4,
			x + render_quad.w / 2,
			y + render_quad.h * 0.8);
	SDL_RenderDrawLine(g_renderer,
			x + render_quad.w / 2,
			y + render_quad.h * 0.8,
			x,
			y + render_quad.h * 0.4);
}
