/* t/unit/chunk.c
 * a simple set of unit tests for the chunk datatype
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <component/chunk.h>
#include <stdio.h>

initialize_chunk_size(32)

static char chunk_create(void)
{
	chunk32_t c;

	printf("  testing chunk creation\n");
	printf("    creating chunk32_t.......................... ");
	initialize_chunk32(&c);
	printf("pass\n");
	printf("  all chunk creation tests passed\n");

	return 1;
}

int main(void)
{
	printf("starting chunk unit tests\n");
	if(!chunk_create()) return 1;
	printf("chunk unit tests complete\n");

	return 0;
}
