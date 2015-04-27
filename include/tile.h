/* tile.h
 * a tile is a basic building block of a chunk, which in turn
 * is a makes up a superchunk, which makes up a map. A tile
 * has both a type, a possible item and a collection of gasses
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#ifndef _HAVEN_TILE_H
#define _HAVEN_TILE_H

#include <stdint.h>

typedef uint32_t gasses;
typedef uint32_t item;

#define OXYGEN_MASK   0xFF
#define NITROGEN_MASK 0xFF00
#define CO2_MASK      0xFF0000
#define PLASMA_MASK   0xFF000000

#define OXYGEN_OFFSET   0
#define NITROGEN_OFFSET 8
#define CO2_OFFSET      16
#define PLASMA_OFFSET   24

struct tile {
	uint8_t type;
	item item;
	gasses gasses;
};

void new_tile(struct tile *tile, uint8_t type, item item,
		uint8_t o, uint8_t n, uint8_t co2, uint8_t p);
void delete_tile(struct tile *tile);

void set_tile_oxygen(struct tile *tile, uint8_t o);
void set_tile_nitrogen(struct tile *tile, uint8_t n);
void set_tile_co2(struct tile *tile, uint8_t co2);
void set_tile_plasma(struct tile *tile, uint8_t p);

uint8_t get_tile_oxygen(struct tile *tile);
uint8_t get_tile_nitrogen(struct tile *tile);
uint8_t get_tile_co2(struct tile *tile);
uint8_t get_tile_plasma(struct tile *tile);

#endif
