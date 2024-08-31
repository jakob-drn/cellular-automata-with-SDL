#pragma once

#include <SDL2/SDL.h>
#include "globals.h"

#define MAP_DEFAULT_MAP_CELLS_SIZE 64
#define MAP_DEFAULT_SCREEN_WIDTH 720
#define MAP_DEFAULT_SCREEN_HEIGHT 576

extern const double MAP_DEFAULT_SCALE;
extern const int MAP_DEFAULT_OFFSET_X;
extern const int MAP_DEFAULT_OFFSET_Y;
extern const int MAP_DEFAULT_CELL_PIXEL_PADDING;


struct map
{
	int size;
	char* cell_plain0;
	char* cell_plain1;
	int cell_pixel;
	const int* cell_pixel_padding;
	double* scale;
	double scale_offset;
	const int* offset_x;
	const int* offset_y;
	int screen_width, screen_height;
	void (*ruleset)(struct map*);
};

void map_init(struct map* m);
void map_free(struct map* m);
void map_draw(struct map* m, SDL_Renderer* renderer);
void map_evolve(struct map* m);
int map_set_cell_plain(struct map* m, int x, int y, int state);
void map_set_cell_pixel(struct map* m);
