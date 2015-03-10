/* arraylist.h
 * an arraylist is a dynamically resizing list that is implemented as an array.
 * it is implemented using macros to allow for all operations to be type
 * checked at compile time so the function initialize_arraylist_type(TYPE)
 * must be called at the top level before any of the functions.
 *
 * Prior to calling any arraylist functions the function arraylist_initialize()
 * must also be called to set all variables to the correct state, failure to do
 * so can result in unexpected behaviour.
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <assert.h>	/* assert */
#include <stdlib.h>	/* calloc, free */
#include <string.h>	/* strncpy */

#ifndef _ARRAYLIST_H
#define _ARRAYLIST_H

#define ARRAYLIST_INITIAL_SIZE 10
#define ERRSTRING_SIZE         128

#define AL_MEM_ERR "not enough memory to allocate array"

static char al_error[ERRSTRING_SIZE];

void arraylist_clear_error(void)
{
	al_error[0] = '\0';
} 

void arraylist_initialize(void) 
{
	arraylist_clear_error();
}

const char *arraylist_error(void) 
{
	return al_error;
}

#define initialize_arraylist_type(type)					\
	struct type ## _arraylist {					\
		unsigned size;						\
		unsigned current;					\
		type *data;						\
	};								\
									\
	typedef struct type ## _arraylist type ## _arraylist_t;		\
									\
	static char new_ ## type ## _arraylist(type ## _arraylist_t *l)	\
	{								\
		assert(l);						\
		assert(al_error[0] == '\0');				\
									\
		l->data = calloc(ARRAYLIST_INITIAL_SIZE, sizeof(type)); \
		if(!l->data) {						\
			strncpy(al_error, AL_MEM_ERR, ERRSTRING_SIZE);	\
			return 0;					\
		}							\
		l->size = ARRAYLIST_INITIAL_SIZE;			\
		l->current = 0;						\
		return 1;						\
	}								\
									\
	static void free_ ## type ## _arraylist(type ## _arraylist_t	\
			*l)						\
	{								\
		assert(l);						\
		assert(al_error[0] == '\0');				\
									\
		free(l->data);						\
		l->data = NULL;						\
		l->size = 0;						\
		l->current = 0;						\
	}								


#endif  /* _ARRAYLIST_H */
