/* arraylist.h
 * an arraylist is a dynamically resizing list that is implemented as an array.
 * it is implemented using macros to allow for all operations to be type
 * checked at compile time so the function initialize_arraylist_type(TYPE)
 * must be called at the top level before any of the functions.
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#ifndef _ARRAYLIST_H
#define _ARRAYLIST_H

#include <assert.h>	/* assert */
#include <dynamic.h>	/* UNUSED */
#include <stdlib.h>	/* calloc, free */
#include <string.h>	/* strncpy, memcpy, strlen */

#define ARRAYLIST_INITIAL_SIZE	10

#define AL_MEM_ERR	"not enough memory to allocate array"
#define AL_RMEM_ERR	"not enough memory to allocate new array for resize"

char error_memory_error[] = "not enough memory to allocate error string";

#define initialize_arraylist_type(type)					\
	struct type ## _arraylist {					\
		unsigned size;						\
		unsigned current;					\
		char *error;						\
		type *data;						\
	};								\
									\
	typedef struct type ## _arraylist type ## _arraylist_t;		\
									\
	static const char *get_error_ ## type ## _arraylist(		\
			type ## _arraylist_t*) UNUSED;			\
	static char has_error_ ## type ## _arraylist(			\
			type ## _arraylist_t*) UNUSED;			\
	static void set_error_ ## type ## _arraylist(			\
			type ## _arraylist_t*, const char*) UNUSED;	\
	static void clear_error_ ## type ## _arraylist(			\
			type ## _arraylist_t*) UNUSED;			\
									\
	static char new_ ## type ## _arraylist(type ## _arraylist_t*)	\
			UNUSED;						\
	static void free_ ## type ## _arraylist(type ## _arraylist_t*)	\
			UNUSED;						\
	static char insert_ ## type ## _arraylist(type ## _arraylist_t*,\
			type) UNUSED;					\
	static char get_ ## type ## _arraylist(type ## _arraylist_t*,	\
			unsigned, type *) UNUSED;			\
	static unsigned size_ ## type ## _arraylist(			\
			type ## _arraylist_t*) UNUSED;			\
	static char is_empty_ ## type ## _arraylist(			\
			type ## _arraylist_t*) UNUSED;			\
	static char push_ ## type ## _arraylist(type ## _arraylist_t*,	\
			type) UNUSED;					\
	static char pop_ ## type ## _arraylist(type ## _arraylist_t*,	\
			type*) UNUSED;					\
									\
	static const char *get_error_ ## type ## _arraylist(		\
			type ## _arraylist_t *l)			\
	{								\
		assert(l);						\
									\
		return l->error;					\
	}								\
									\
	static char has_error_ ## type ## _arraylist(			\
			type ## _arraylist_t *l)			\
	{								\
		assert(l);						\
									\
		return l->error != NULL;				\
	}								\
									\
	static void set_error_ ## type ## _arraylist(			\
			type ## _arraylist_t *l, const char *err)	\
	{								\
		unsigned len;						\
									\
		assert(l);						\
		assert(err);						\
		assert(!l->error);					\
									\
		len = strlen(err);					\
		l->error = malloc(len + 1);				\
		if(!l->error)						\
			l->error = error_memory_error;			\
		else							\
			strncpy(l->error, err, len);			\
	}								\
									\
	static void clear_error_ ## type ## _arraylist(			\
			type ## _arraylist_t *l)			\
	{								\
		assert(l);						\
		assert(l->error);					\
									\
		free(l->error);						\
		l->error = NULL;					\
	}								\
									\
	static char new_ ## type ## _arraylist(type ## _arraylist_t *l)	\
	{								\
		assert(l);						\
									\
		l->data = calloc(ARRAYLIST_INITIAL_SIZE, sizeof(type));	\
		if(!l->data) {						\
			set_error_ ## type ## _arraylist(l, AL_MEM_ERR);\
			return 0;					\
		}							\
		l->size = ARRAYLIST_INITIAL_SIZE;			\
		l->current = 0;						\
		l->error = NULL;					\
		return 1;						\
	}								\
									\
	static void free_ ## type ## _arraylist(type ## _arraylist_t	\
			*l)						\
	{								\
		assert(l);						\
		assert(!has_error_ ## type ## _arraylist(l));		\
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
		assert(!has_error_ ## type ## _arraylist(l));		\
									\
		if(l->current < l->size)				\
			return 1;					\
		new_size = l->size * 2;					\
		new_array = calloc(new_size, sizeof(type));		\
		if(!new_array) {					\
			set_error_ ## type ## _arraylist(l,		\
					AL_RMEM_ERR);			\
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
		assert(!has_error_ ## type ## _arraylist(l));		\
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
		assert(!has_error_ ## type ## _arraylist(l));		\
									\
		if(idx > l->current)					\
			return 0;					\
		*e = l->data[idx];					\
		return 1;						\
	}								\
									\
	static unsigned size_ ## type ## _arraylist(type ## _arraylist_t\
			*l)						\
	{								\
		assert(l);						\
		assert(!has_error_ ## type ## _arraylist(l));		\
									\
		return l->current;					\
	}								\
									\
	static char is_empty_ ## type ## _arraylist(type ## _arraylist_t\
			*l)						\
	{								\
		assert(l);						\
		assert(!has_error_ ## type ## _arraylist(l));		\
									\
		return l->current == 0;					\
	}								\
									\
	static char push_ ## type ## _arraylist(type ## _arraylist_t *l,\
			type e)						\
	{								\
		return insert_ ## type ## _arraylist(l, e);		\
	}								\
									\
	static char pop_ ## type ## _arraylist(type ## _arraylist_t *l, \
			type *e)					\
	{								\
		assert(l);						\
		assert(!has_error_ ## type ## _arraylist(l));		\
									\
		if(l->current == 0)					\
			return 0;					\
		*e = l->data[--l->current];				\
		return 1;						\
	}

#endif  /* _ARRAYLIST_H */
