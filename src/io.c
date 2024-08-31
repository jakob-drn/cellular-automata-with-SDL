#include "io.h"
#include <stdio.h>

#include "globals.h"
#include <math.h>

#define IO_GLOBAL_DRAW_OFFSET_KOEF 747
#define IO_GLOBAL_DRAW_OFFSET_MIN 5

void io_handle_keydown(const SDL_KeyboardEvent* key)
{
	switch(key->keysym.sym)
	{
		case SDLK_KP_PLUS:
			ticker0.w.duration*=1.1;
			printf("%f\n",ticker0.w.duration);
			break;
		case SDLK_KP_MINUS:
			ticker0.w.duration*=0.9;
			printf("%f\n",ticker0.w.duration);
			break;
		case SDLK_UP:
			global_draw_offset_y+=IO_GLOBAL_DRAW_OFFSET_MIN
			+log(IO_GLOBAL_DRAW_OFFSET_KOEF/global_draw_scaling);
			break;
		case SDLK_DOWN:
			global_draw_offset_y-=IO_GLOBAL_DRAW_OFFSET_MIN
			+log(IO_GLOBAL_DRAW_OFFSET_KOEF/global_draw_scaling);
			break;
		case SDLK_RIGHT:
			global_draw_offset_x-=IO_GLOBAL_DRAW_OFFSET_MIN
			+log(IO_GLOBAL_DRAW_OFFSET_KOEF/global_draw_scaling);
			break;
		case SDLK_LEFT:
			global_draw_offset_x+=IO_GLOBAL_DRAW_OFFSET_MIN
			+log(IO_GLOBAL_DRAW_OFFSET_KOEF/(global_draw_scaling));
			break;
		case SDLK_z:
			global_draw_offset_y=0;
			global_draw_offset_x=0;
			global_draw_scaling=1;
			break;

		default:
			printf("kd:\t%s\n",SDL_GetKeyName(key->keysym.sym));
			break;

	}
}

void io_handle_keyup(const SDL_KeyboardEvent* key)
{
	switch(key->keysym.sym)
	{
		case  SDLK_RIGHT:
			printf("right released\n");
			break;
		default:
			printf("ku:\t%s\n",SDL_GetKeyName(key->keysym.sym));
			break;

	}
}

void io_handle_mousemotion(const SDL_MouseMotionEvent* motion)
{
//	printf("mm\tx%i\ty%i\n",motion->x,motion->y);
	global_mouse_pos_x=motion->x;
	global_mouse_pos_y=motion->y;
}

void io_handle_mousebuttondown(const SDL_MouseButtonEvent* button)
{
	switch(button->button)
	{
		case SDL_BUTTON_LEFT:
			printf("ld\tcl%i\t%i\t%i\n",button->clicks,button->x,button->y);
			break;
		case SDL_BUTTON_RIGHT:
			printf("rd\tcl%i\t%i\t%i\n",button->clicks,button->x,button->y);
			break;
		case SDL_BUTTON_MIDDLE:
			printf("md\tcl%i\t%i\t%i\n",button->clicks,button->x,button->y);
			break;
	}
}
void io_handle_mousebuttonup(const SDL_MouseButtonEvent* button)
{
	switch(button->button)
	{
		case SDL_BUTTON_LEFT:
			printf("lu\tcl%i\t%i\t%i\n",button->clicks,button->x,button->y);
			break;
		case SDL_BUTTON_RIGHT:
			printf("ru\tcl%i\t%i\t%i\n",button->clicks,button->x,button->y);
			break;
		case SDL_BUTTON_MIDDLE:
			printf("mu\tcl%i\t%i\t%i\n",button->clicks,button->x,button->y);
			break;
	}
}

void io_handle_mousewheel(const SDL_MouseWheelEvent* wheel)
{
	if(wheel->y>0) global_draw_scaling*=1.1;
	else global_draw_scaling*=0.9;
	//global_draw_offset_x*=global_draw_scaling;
	//global_draw_offset_y*=global_draw_scaling;
	printf("mw\tx%i\ty%i\t%i\t%lf\n",wheel->x,wheel->y,wheel->direction,global_draw_scaling);
}
