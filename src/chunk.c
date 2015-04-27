/* chunk.h
 * implementation of the chunk interface
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <chunk.h>
#include <string.h>

void new_chunk(struct chunk *chunk)
{
	memset(chunk->tiles, 0, sizeof(chunk->tiles));
}

void delete_chunk(struct chunk *chunk)
{
	memset(chunk->tiles, 0, sizeof(chunk->tiles));
}


struct tile *get_chunk_tile(struct chunk *chunk, unsigned x, unsigned y,
		unsigned z)
{
	return &chunk->tiles[x + CHUNK_X * z + CHUNK_X * CHUNK_Z * y];
}

void set_chunk_tile(struct chunk *chunk, struct tile *tile, unsigned x,
		unsigned y, unsigned z)
{
	memcpy(&chunk->tiles[x + CHUNK_X * z + CHUNK_X * CHUNK_Z * y], tile,
			sizeof(struct tile));
}
