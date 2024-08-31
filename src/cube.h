#pragma once

#include <SDL2/SDL.h>

struct cube_p
{
	int x,y,z;	
};

struct cube_ov
{
	struct cube_p p;
	float s;
};

struct cube
{
	int x,y,z,l;
	struct cube_ov ov[8];
};


/*
 *		  7-------6
 *		 /'      /|
 *		0-------1 |
 *		| 4.....|-5
 *		|´      |/
 *		3-------2
 *
 * */


void cube_draw(struct cube* c,SDL_Renderer* renderer,double t);
void cube_init(struct cube* c);

