/* t/unit/arraylist.c
 * a simple set of unit tests for the arraylist class
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <arraylist.h>
#include <stdio.h>

initialize_arraylist_type(int);

static char arraylist_create(void)
{
	int_arraylist_t l;

	printf("  testing arraylist creation\n");
	printf("    creating standard arraylist of type int..... ");
	if(!new_int_arraylist(&l)) {
		printf("fail\n");
		printf("arraylist error: %s\n", arraylist_error());
		return 0;
	}
	free_int_arraylist(&l);
	printf("pass\n");

	printf("  all arraylist creation tests passed\n");
	return 1;
}

static char arraylist_insert(void)
{
	int_arraylist_t l;
	int t;

	printf("  testing arraylist insertion\n");
	if(!new_int_arraylist(&l)) {
		printf("could not create arraylist for test\n");
		printf("arraylist error: %s\n", arraylist_error());
		return 0;
	}

	printf("    inserting element 1......................... ");
	if(!insert_int_arraylist(&l, 1)) {
		printf("fail\n");
		printf("arraylist error: %s\n", arraylist_error());
		return 0;
	}
	printf("pass\n");
	
	printf("    checking element 1 inserted................. ");
	if(!get_int_arraylist(&l, 0, &t)) {
		printf("fail\n");
		printf("element not in correct position\n");
		return 0;
	}
	if(t != 1) {
		printf("fail\n");
		printf("incorrect element in position\n");
		return 0;
	}
	printf("pass\n");

	free_int_arraylist(&l);
	printf("  all arraylist insertion tests passed\n");
	return 1;
}

int main(void)
{
	printf("starting arraylist unit tests\n");
	if(!arraylist_create()) return 1;
	if(!arraylist_insert()) return 1;
	printf("arraylist unit tests complete\n");

	return 0;
}
