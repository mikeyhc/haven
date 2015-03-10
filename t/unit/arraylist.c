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
       printf("pass\n");

       printf("  all arraylist creation tests passed\n");
       return 1;
}

int main(void)
{
    printf("starting arraylist unit tests\n");
    if(!arraylist_create()) return 1;
    printf("arraylist unit tests complete\n");

    return 0;
}
