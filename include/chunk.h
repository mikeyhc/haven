/* chunk.h
 * chunks contain tiles and are contained in superchunks, they are best
 * thought of as a map section
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#ifndef _HAVEN_CHUNK_H
#define _HAVEN_CHUNK_H

#include <tile.h>

#define CHUNK_X 16
#define CHUNK_Y 16
#define CHUNK_Z 16

/* per tile offset */
#define MAGIC_X 0
// #define MAGIC_Y -3
#define MAGIC_Y 0

#define TILE_EDGE_HEIGHT 0.4

struct chunk {
	struct tile tiles[CHUNK_X * CHUNK_Y * CHUNK_Z];
};

void new_chunk(struct chunk *chunk);
void delete_chunk(struct chunk *chunk);

struct tile *get_chunk_tile(struct chunk *chunk, unsigned x, unsigned y,
		unsigned z);
void set_chunk_tile(struct chunk *chunk, struct tile *tile, unsigned x,
		unsigned y, unsigned z);

void render_chunk(struct chunk *chunk, struct tileset *tileset, int x, int y,
		unsigned level);

unsigned chunk_height(struct tileset *tileset);
unsigned chunk_width(struct tileset *tileset);

#endif /* _HAVEN_CHUNK_H */
