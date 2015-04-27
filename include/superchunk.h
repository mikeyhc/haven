/* superchunk.h
 * a chunk of chunks
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#ifndef _SUPERCHUNK_H
#define _SUPERCHUNK_H

#include <chunk.h>

#define SCHUNK_X 16
#define SCHUNK_Y 16
#define SCHUNK_Z 16

struct superchunk {
	struct chunk *chunks[SCHUNK_X * SCHUNK_Y * SCHUNK_Z];
};

void new_superchunk(struct superchunk *chunk);
void delete_superchunk(struct superchunk *chunk);

struct chunk *get_superchunk_chunk(struct superchunk *chunk, unsigned x,
		unsigned y, unsigned z);
/* return the old chunk */
struct chunk *set_superchunk_chunk(struct superchunk *chunk, struct chunk *c,
		unsigned x, unsigned y, unsigned z);

#endif /* _SUPERCHUNK_H */
