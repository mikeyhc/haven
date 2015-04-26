/* tileset.c
 * implementation of the tileset
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <assert.h>
#include <texture.h>
#include <tileset.h>

void new_tileset(struct tileset *tileset, struct texture *texture,
		unsigned top_offset, unsigned offset, unsigned width,
		unsigned height)
{
	assert(tileset && texture);

	tileset->texture = texture;
	tileset->row_length = texture->width / width;
	tileset->top_offset = top_offset;
	tileset->offset = offset;
	tileset->width = width;
	tileset->height = height;
	tileset->loaded_from_file = 0;
}

char new_tileset_from_file(struct tileset *tileset, const char *path,
		unsigned top_offset, unsigned offset, unsigned width,
		unsigned height)
{
	struct texture *t;

	assert(tileset && path);

	t = malloc(sizeof(struct texture));
	if(!t)
		return 0;

	new_texture(t);
	if(!load_from_file(t, path))
		return 0;

	new_tileset(tileset, t, top_offset, offset, width, height);
	tileset->loaded_from_file = 1;
	return 1;
}

void delete_tileset(struct tileset *tileset)
{
	assert(tileset);

	if(tileset->loaded_from_file)
		delete_texture(tileset->texture);
	tileset->texture = NULL;
	tileset->top_offset = tileset->offset = 0;
	tileset->width = tileset->height = 0;
	tileset->loaded_from_file = 0;
}

void render_tileset(struct tileset *tileset, int x, int y, unsigned count)
{
	SDL_Rect rect;
	unsigned row, col;

	assert(tileset);

	col = count % tileset->row_length;
	row = count / tileset->row_length;
	rect.x = col * tileset->width;
	rect.y = tileset->top_offset + row *
		(tileset->height + tileset->offset);
	rect.h = tileset->height;
	rect.w = tileset->width;
	render(tileset->texture, x, y, &rect);
}
