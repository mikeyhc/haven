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

#ifndef _ARRAYLIST_H
#define _ARRAYLIST_H

#include <assert.h>	/* assert */
#include <stdlib.h>	/* calloc, free */
#include <string.h>	/* strncpy, memcpy */

#define ARRAYLIST_INITIAL_SIZE	10
#define ERRSTRING_SIZE		128

#define AL_MEM_ERR	"not enough memory to allocate array"
#define AL_RMEM_ERR	"not enough memory to allocate new array for resize"

#define UNUSED __attribute__ ((unused))

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
	static char new_ ## type ## _arraylist(type ## _arraylist_t*)	\
			UNUSED;						\
	static void free_ ## type ## _arraylist(type ## _arraylist_t*)	\
			UNUSED;						\
	static char get_ ## type ## _arraylist(type ## _arraylist_t*,	\
			unsigned, type *) UNUSED;			\
									\
	static char new_ ## type ## _arraylist(type ## _arraylist_t *l)	\
	{								\
		assert(l);						\
		assert(al_error[0] == '\0');				\
									\
		l->data = calloc(ARRAYLIST_INITIAL_SIZE, sizeof(type));	\
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
	}								\
									\
	static char resize_ ## type ## _arraylist(type ## _arraylist_t	\
			*l)						\
	{								\
		type *new_array;					\
		unsigned new_size;					\
									\
		assert(l);						\
		assert(al_error[0] == '\0');				\
									\
		if(l->current < l->size)				\
			return 1;					\
		new_size = l->size * 2;					\
		new_array = calloc(new_size, sizeof(type));		\
		if(!new_array) {					\
			strncpy(al_error, AL_RMEM_ERR, ERRSTRING_SIZE);	\
			return 0;					\
		}							\
		memcpy(new_array, l->data, l->size * sizeof(type));	\
		free(l->data);						\
		l->data = new_array;					\
		l->size = new_size;					\
		return 1;						\
	}								\
									\
	static char insert_ ## type ## _arraylist(type ## _arraylist_t	\
			*l, type e)					\
	{								\
		assert(l);						\
		assert(al_error[0] == '\0');				\
									\
		if(!resize_ ## type ## _arraylist(l))			\
			return 0;					\
		l->data[l->current++] = e;				\
		return 1;						\
	}								\
									\
	static char get_ ## type ## _arraylist(type ## _arraylist_t *l,	\
			unsigned idx, type *e)				\
	{								\
		assert(l);						\
		assert(al_error[0] == '\0');				\
									\
		if(idx > l->current)					\
			return 0;					\
		*e = l->data[idx];					\
		return 1;						\
	}

#endif  /* _ARRAYLIST_H */
