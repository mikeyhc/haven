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
	unsigned x, z;

	assert(chunk && tileset);

	for(z = 0; z < CHUNK_Z; z++)
		for(x = 0; x < CHUNK_X; x++)
			render_tile(get_chunk_tile(chunk, x, level, z),
					tileset, sx, sy + z * tileset->height);
}
