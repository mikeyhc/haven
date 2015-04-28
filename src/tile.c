/* tile.c
 * implementation of tile interface
 *
 * author: mikeyhc <mikeyhc@atmosia.net>
 */

#include <tile.h>
#include <tileset.h>

void new_tile(struct tile *tile, uint8_t type, item item,
		uint8_t o, uint8_t n, uint8_t co2, uint8_t p)
{
	tile->type = type;
	tile->item = item;
	tile->gasses = 0x00 | o << OXYGEN_OFFSET
		            | n << NITROGEN_OFFSET
			    | co2 << CO2_OFFSET
			    | p << PLASMA_OFFSET;
}

void delete_tile(struct tile *tile)
{
	tile->type = 0;
	tile->item = 0;
	tile->gasses = 0;
}

void set_tile_oxygen(struct tile *tile, uint8_t o)
{
	tile->gasses = (tile->gasses & ~OXYGEN_MASK)
		| (o << OXYGEN_OFFSET);
}

void set_tile_nitrogen(struct tile *tile, uint8_t n) {
	tile->gasses = (tile->gasses & ~NITROGEN_MASK)
		| (n << NITROGEN_OFFSET);
}

void set_tile_co2(struct tile *tile, uint8_t co2)
{
	tile->gasses = (tile->gasses & ~CO2_MASK)
		| (co2 << CO2_OFFSET);
}

void set_tile_plasma(struct tile *tile, uint8_t p)
{
	tile->gasses = (tile->gasses & ~PLASMA_MASK)
		| (p << PLASMA_OFFSET);
}

uint8_t get_tile_oxygen(struct tile *tile)
{
	return tile->gasses & OXYGEN_MASK >> OXYGEN_OFFSET;
}

uint8_t get_tile_nitrogen(struct tile *tile)
{
	return tile->gasses & NITROGEN_MASK >> NITROGEN_OFFSET;
}

uint8_t get_tile_co2(struct tile *tile)
{
	return tile->gasses & CO2_MASK >> CO2_OFFSET;
}

uint8_t get_tile_plasma(struct tile *tile)
{
	return tile->gasses & PLASMA_MASK >> PLASMA_OFFSET;
}

void render_tile(struct tile *tile, struct tileset *tileset, int x, int y)
{
	render_tileset(tileset, x, y, tile->type);
}
