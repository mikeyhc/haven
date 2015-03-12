/* t/unit/entity.c
 * a simple set of unit tests for the entity datatype
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <entity.h>
#include <stdio.h>

static char new_entity_test(void)
{
	entity_t e1, e2;

	printf("  testing new entities\n");
	printf("    creating new entity......................... ");
	e1 = new_entity();
	printf("pass\n");

	printf("    testing entity is unique.................... ");
	e2 = new_entity();
	if(e1 == e2) {
		printf("fail\n");
		printf("entity was not unique\n");
		return 0;
	}
	printf("pass\n");
	printf("  all new entity tests passed\n");

	return 1;
}

static char destroy_entity_test(void)
{
	entity_t e1, e2;

	printf("  testing destroying entities\n");
	printf("    creating and destroying entity.............. ");
	e1 = new_entity();
	destroy_entity(e1);
	printf("pass\n");

	printf("    checking UUID of entity was reclaimed....... ");
	e2 = new_entity();
	if(e1 != e2) {
		printf("fail\n");
		return 0;
	}

	printf("pass\n");
	printf("  all destroy entity tests passed\n");

	return 1;
}


int main(void)
{
	printf("starting entity unit tests\n");
	printf("  initializing entity system.................... ");
	entity_initialize();
	printf("done\n");
	if(!new_entity_test()) return 1;
	if(!destroy_entity_test()) return 1;
	printf("entity unit tests complete\n");

	return 0;
}
