/* entity.h
 * an entity is simply a UUID, it is used to track individual elements within
 * the game. prior to using new_entity the function entity_initialize should 
 * be called. this will check the number of rows in the entity database and
 * assign that as the first entity id, this assumes that when the components 
 * are loaded a form of defragmentation is performed to linearize the entity
 * ids.
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#ifndef _HAVEN_ENTITY_H
#define _HAVEN_ENTITY_H

typedef unsigned long entity_t;

void entity_initialize(void);
entity_t new_entity(void);
void destroy_entity(entity_t);

#endif /* _HAVEN_ENTITY_H */
