/* texture.h
 * a simple interface for managing textures
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL.h>

struct texture {
	SDL_Texture *texture;
	int width, height;
};

void new_texture(struct texture *texture);
void delete_texture(struct texture *texture);
char load_from_file(struct texture *texture, const char *path);
void render(struct texture *texture, int x, int y, SDL_Rect *clip);

#endif /* _TEXTURE_H */
