/* chunk.c
 * implementation of the chunk interface
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <assert.h>
#include <chunk.h>
#include <SDL.h>
#include <string.h>

extern SDL_Renderer *g_renderer;

void new_chunk(struct chunk *chunk)
{
	assert(chunk);

	memset(chunk->tiles, 0, sizeof(chunk->tiles));
}

void delete_chunk(struct chunk *chunk)
{
	assert(chunk);

	memset(chunk->tiles, 0, sizeof(chunk->tiles));
}


struct tile *get_chunk_tile(struct chunk *chunk, unsigned x, unsigned y,
		unsigned z)
{
	assert(chunk);
	assert(x < CHUNK_X);
	assert(y < CHUNK_Y); assert(z < CHUNK_Z);

	return &chunk->tiles[x + CHUNK_X * z + CHUNK_X * CHUNK_Z * y];
}

void set_chunk_tile(struct chunk *chunk, struct tile *tile, unsigned x,
		unsigned y, unsigned z)
{
	assert(chunk && tile);
	assert(x < CHUNK_X);
	assert(y < CHUNK_Y);
	assert(z < CHUNK_Z);

	memcpy(&chunk->tiles[x + CHUNK_X * z + CHUNK_X * CHUNK_Z * y], tile,
			sizeof(struct tile));
}

void render_chunk(struct chunk *chunk, struct tileset *tileset, int sx, int sy,
		unsigned level)
{
	int x, z, iz, x_offset, z_offset;
	struct chunk_bounds bounds;
	SDL_Point point_list[5];

	assert(chunk && tileset);

	z_offset = -(tileset->height / 2);
	for(z = CHUNK_Z - 1; z >= 0; z--){
		z_offset += tileset->height / 2;
		x_offset = (CHUNK_Z - z) * tileset->width / 2;
		for(x = 0, iz = z; iz < CHUNK_Z; iz++, x++){
			render_tile(get_chunk_tile(chunk, x, level, iz),
					tileset,
					sx - x_offset + x * tileset->width,
					sy + z_offset);
		}
	}

	for(z = 1; z < CHUNK_Z; z++){
		z_offset += tileset->height / 2;
		x_offset = (CHUNK_Z - z) * tileset->width / 2;
		for(x = 0, iz = z; iz < CHUNK_Z; iz++, x++) {
			render_tile(get_chunk_tile(chunk, x, level, iz),
					tileset,
					sx - x_offset + x * tileset->width,
					sy + z_offset);
		}
	}

	bounds = chunk_bounds(tileset, sx, sy);
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawLine(g_renderer, bounds.top.x, bounds.top.y,
			bounds.bottom.x, bounds.bottom.y);
	SDL_RenderDrawLine(g_renderer, bounds.left.x, bounds.left.y,
			bounds.right.x, bounds.right.y);

	point_list[0] = bounds.top;
	point_list[1] = bounds.left;
	point_list[2] = bounds.bottom;
	point_list[3] = bounds.right;
	point_list[4] = bounds.top;
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawLines(g_renderer, point_list, 5);
}

struct chunk_bounds chunk_bounds(struct tileset *tileset, int x, int y)
{
	struct chunk_bounds bounds;

	bounds.top.x = x;
	bounds.top.y = y;
	bounds.bottom.x = x;
	bounds.bottom.y = y + CHUNK_Z * tileset->height;
	bounds.left.x = x - CHUNK_X / 2 * tileset->width;
	bounds.left.y = y + CHUNK_Z * tileset->height / 2;
	bounds.right.x = x + CHUNK_X / 2 * tileset->width;
	bounds.right.y = bounds.left.y;

	return bounds;
}
