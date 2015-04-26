/* tileset.h
 * a tileset allows provides an interface for accessing specific
 * parts of a texture in a uniform manner
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#ifndef _TILESET_H
#define _TILESET_H

#include <SDL.h>
#include <texture.h>

struct tileset {
	struct texture *texture;
	unsigned row_length;
	unsigned top_offset;
	unsigned offset;
	unsigned width;
	unsigned height;
	unsigned char loaded_from_file;
};

void new_tileset(struct tileset *tileset, struct texture *texture,
		unsigned top_offset, unsigned offset, unsigned width,
		unsigned height);
char new_tileset_from_file(struct tileset *tileset, const char *path,
		unsigned top_offset, unsigned offset, unsigned width,
		unsigned height);
void delete_tileset(struct tileset *tileset);
void render_tileset(struct tileset *tileset, int x, int y, unsigned count);

#endif /* _TILESET_H */
