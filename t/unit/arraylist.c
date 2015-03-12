/* t/unit/arraylist.c
 * a simple set of unit tests for the arraylist datatype
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <arraylist.h>
#include <stdio.h>

initialize_arraylist_type(int)

static char arraylist_create(void)
{
	int_arraylist_t l;

	printf("  testing arraylist creation\n");
	printf("    creating standard arraylist of type int..... ");
	if(!new_int_arraylist(&l)) {
		printf("fail\n");
		printf("arraylist error: %s\n", get_error_int_arraylist(&l));
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
	int t, i;

	printf("  testing arraylist insertion\n");
	if(!new_int_arraylist(&l)) {
		printf("could not create arraylist for test\n");
		printf("arraylist error: %s\n", get_error_int_arraylist(&l));
		return 0;
	}

	printf("    inserting element 1......................... ");
	if(!insert_int_arraylist(&l, 1)) {
		printf("fail\n");
		printf("arraylist error: %s\n", get_error_int_arraylist(&l));
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

	printf("    inserting 10 elements to test resize........ ");
	for(i = 0; i < 10; i++) 
		if(!insert_int_arraylist(&l, i)) {
			printf("fail\n");
			printf("failed to insert %d\n", i);
			printf("arraylist_error: %s\n", 
					get_error_int_arraylist(&l));
			return 0;
		}
	printf("pass\n");

	printf("    checking element positions.................. ");
	for(i = 0; i < 10; i++) {
		if(!get_int_arraylist(&l, i + 1, &t)) {
			printf("fail\n");
			printf("element not in correct position\n");
			return 0;
		}
		if(t != i) {
			printf("failed\n");
			printf("element not in correct position\n");
			return 0;
		}
	}
	printf("pass\n");

	printf("    checking size is correct.................... ");
	if(size_int_arraylist(&l) != 11) {
		printf("fail\n");
		return 0;
	}
	printf("pass\n");

	printf("    checking is not empty....................... ");
	if(is_empty_int_arraylist(&l)) {
		printf("fail\n");
		return 0;
	}
	printf("pass\n");

	free_int_arraylist(&l);
	printf("  all arraylist insertion tests passed\n");
	return 1;
}

static char arraylist_push_pop(void)
{
	int_arraylist_t l;
	int i, v;

	printf("  testing arraylist push/pop\n");
	if(!new_int_arraylist(&l)) {
		printf("could not create arraylist for tests\n");
		printf("arraylist error: %s\n", get_error_int_arraylist(&l));
		return 0;
	}

	printf("    pushing items............................... ");
	for(i = 0; i < 10; i++) 
		if(!push_int_arraylist(&l, i)) {
			printf("fail\n");
			printf("could not push onto arraylist\n");
			printf("arraylist error: %s\n", 
					get_error_int_arraylist(&l));
			return 0;
		}
	printf("pass\n");

	printf("    checking items are in correct positions..... ");
	for(i = 0; i < 10; i++) {
		if(!get_int_arraylist(&l, i, &v)) {
			printf("fail!\n");
			printf("object failed to insert\n");
			return 0;
		}
		if(v != i) {
			printf("fail\n");
			printf("found %d, expected %d\n", v, i);
			return 0;
		}
	}
	printf("pass\n");

	printf("    testing items pop correctly................. ");
	for(i = 9; i > 5; i--) {
		if(!pop_int_arraylist(&l, &v)) {
			printf("fail\n");
			printf("could not pop item\n");
			return 0;
		}
		if(i != v) {
			printf("fail\n");
			printf("found %d, expected %d\n", v, i);
			return 0;
		}

	}
	printf("pass\n");

	printf("    checking correct size....................... ");
	if(size_int_arraylist(&l) != 6) {
		printf("fail\n");
		printf("got size %d, expected 6\n", size_int_arraylist(&l));
		return 0;
	}
	printf("pass\n");

	printf("    checking items push correctly after pop..... ");
	for(i = 0; i < 4; i++)
		if(!push_int_arraylist(&l, i)) {
			printf("fail\n");
			printf("failed to push!\n");
			printf("arraylist error: %s\n", 
					get_error_int_arraylist(&l));
			return 0;
		}
	printf("pass\n");

	printf("    checking items in the correct position...... ");
	for(i = 0; i < 6; i++) {
		if(!get_int_arraylist(&l, i, &v)) {
			printf("fail\n");
			printf("object failed to insert\n");
			return 0;
		}
		if(i != v) {
			printf("fail\n");
			printf("found %d, expected %d\n", v, i);
			return 0;
		}
	}

	for(i = 0; i < 4; i++) {
		if(!get_int_arraylist(&l, i + 6, &v)) {
			printf("fail\n");
			printf("object failed to insert\n");
			return 0;
		}
		if(i != v) {
			printf("fail\n");
			printf("found %d, expected %d\n", v, i);
			return 0;
		}
	}
	printf("pass\n");

	free_int_arraylist(&l);
	printf("  all arraylist push/pop tests passed\n");
	return 1;
}

int main(void)
{
	printf("starting arraylist unit tests\n");
	if(!arraylist_create()) return 1;
	if(!arraylist_insert()) return 1;
	if(!arraylist_push_pop()) return 1;
	printf("arraylist unit tests complete\n");

	return 0;
}
