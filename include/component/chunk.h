/* component/chunk.h
 * a chunk component contains a fixed number of enities in a 3D matrix.
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#ifndef _COMPONENT_CHUNK_H
#define _COMPONENT_CHUNK_H

#include <assert.h>	/* assert */
#include <dynamic.h>	/* UNUSED */
#include <entity.h>	/* entity_t, new_entity */
#include <string.h>	/* memset */

#define initialize_chunk_size(size)					\
	struct chunk_component_ ## size {				\
		entity_t data[size * size * size];			\
		entity_t id;						\
		const char *error;					\
	};								\
									\
	typedef struct chunk_component_ ## size chunk ## size ## _t;	\
									\
	const char *get_chunk ## size ## _error(chunk ##  size ## _t*)	\
			UNUSED;						\
	void set_chunk ## size ## _error(chunk ## size ## _t*,		\
			const char*) UNUSED;				\
	void clear_chunk ##  size ## _error(chunk ## size ## _t*)	\
			UNUSED;						\
									\
	void initialize_chunk ## size (chunk ## size ## _t *) UNUSED;	\
									\
	const char *get_chunk ## size ## _error(chunk ## size ## _t *c)	\
	{								\
		assert(c);						\
		assert(c->error);					\
									\
		return c->error;					\
	}								\
									\
	void set_chunk ## size ## _error(chunk ## size ## _t *c,	\
			const char *err)				\
	{								\
		assert(c);						\
		assert(err);						\
		assert(!c->error);					\
									\
		c->error = err;						\
	}								\
									\
	void clear_chunk ## size ## _error(chunk ## size ## _t *c)	\
	{								\
		assert(c);						\
		assert(c->error);					\
									\
		c->error = NULL;					\
	}								\
									\
	void initialize_chunk ## size (chunk ## size ## _t *c)		\
	{								\
		assert(c);						\
									\
		memset(c->data, 0, size * size * size);			\
		c->id = new_entity();					\
		c->error = NULL;					\
	}								\

#endif	/* _COMPONENT_CHUNK_H */
