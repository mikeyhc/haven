/* superchunk.c
 * implementation of the superchunk interface
 *
 * author: mikey <mikeyhc@atmosia.net>
 */

#include <string.h>
#include <superchunk.h>

void new_superchunk(struct superchunk *chunk)
{
	memset(chunk, 0, sizeof(struct superchunk));
}

void delete_superchunk(struct superchunk *chunk)
{
	memset(chunk, 0, sizeof(struct superchunk));
}

struct chunk *get_superchunk_chunk(struct superchunk *chunk, unsigned x,
		unsigned y, unsigned z)
{
	return chunk->chunks[x + SCHUNK_X * z + SCHUNK_X * SCHUNK_Z * y];
}

struct chunk *set_superchunk_chunk(struct superchunk *chunk, struct chunk *c,
		unsigned x, unsigned y, unsigned z)
{
	struct chunk *ret;
	unsigned pos;

	pos = x + SCHUNK_X * z + SCHUNK_X * SCHUNK_Z * y;
	ret = chunk->chunks[pos];
	if(chunk)
		memcpy(chunk->chunks[pos], c, sizeof(struct chunk));
	else
		memset(chunk->chunks[pos], 0, sizeof(struct chunk));
	return ret;
}

