#include <arraylist.h>
#include <entity.h>

initialize_arraylist_type(entity_t)

static entity_t_arraylist_t recycle_list;
static entity_t current_entity;

void entity_initialize(void)
{
	/* TODO: read the entity database */
	current_entity = 1;
	new_entity_t_arraylist(&recycle_list);
}

entity_t new_entity(void)
{
	entity_t e;

	if(!is_empty_entity_t_arraylist(&recycle_list) &&
			pop_entity_t_arraylist(&recycle_list, &e))
		return e;
	return current_entity++;
}

void destroy_entity(entity_t e)
{
	/* TODO: remove empty components related to entity */
	/* TODO: non-silent failure */
	push_entity_t_arraylist(&recycle_list, e);
}
