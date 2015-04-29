/* chunk.c
 * implementation of the chunk interface
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <assert.h>
#include <chunk.h>
#include <string.h>

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
	assert(y < CHUNK_Y);
	assert(z < CHUNK_Z);

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
	unsigned x, z, h; int offset;

	assert(chunk && tileset);

	h = tileset->height * TILE_EDGE_HEIGHT;
	for(z = 0; z < CHUNK_Z; z++)
		for(x = 0; x < CHUNK_X; x++) {
			offset = sx - z * (tileset->width / 2) + z * MAGIC_X;
			render_tile(get_chunk_tile(chunk, x, level, z),
					tileset,
					offset + tileset->width * x,
					sy + z * h + z * MAGIC_Y);
		}
}

unsigned chunk_height(struct tileset *tileset)
{
	return (CHUNK_Z - 1) * tileset->height * TILE_EDGE_HEIGHT
		+ CHUNK_Z * MAGIC_Y + tileset->height;
}

unsigned chunk_width(struct tileset *tileset)
{
	return CHUNK_Z * MAGIC_X + tileset->width * CHUNK_X;
}
