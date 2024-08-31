#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include "ticker.h"
#include "io.h"
#include "globals.h"
#include "map.h"

void ruleset(struct map* m);

double get_SDL_GetTicks_seconds()
{
	return SDL_GetTicks()*0.001;
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window *window = SDL_CreateWindow("CUBE",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) 
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) 
	{
		SDL_DestroyWindow(window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Event e;
	ticker0.w.start=1; 
	ticker0.w.duration=0.9; 
	ticker0.w.clock=get_SDL_GetTicks_seconds;

	struct map dornauer_way_of_life=
	{
		.scale=&global_draw_scaling,
		.offset_x=&global_draw_offset_x,
		.offset_y=&global_draw_offset_y,
		.screen_width=SCREEN_WIDTH,
		.screen_height=SCREEN_HEIGHT,
		.ruleset=&ruleset,
		.size=300,
		.scale_offset=1
	};
	map_init(&dornauer_way_of_life);
	map_set_cell_plain(&dornauer_way_of_life,9,9,1);
	map_set_cell_plain(&dornauer_way_of_life,0,0,1);
	map_set_cell_plain(&dornauer_way_of_life,0,9,1);
	map_set_cell_plain(&dornauer_way_of_life,9,0,1);
	map_set_cell_plain(&dornauer_way_of_life,0,10,1);
	map_set_cell_plain(&dornauer_way_of_life,111,111,1);
	map_set_cell_plain(&dornauer_way_of_life,111,112,1);
	map_set_cell_plain(&dornauer_way_of_life,111,113,1);
	map_set_cell_plain(&dornauer_way_of_life,113,111,1);
	map_set_cell_plain(&dornauer_way_of_life,110,111,1);
	map_set_cell_plain(&dornauer_way_of_life,111,112,1);
	map_set_cell_plain(&dornauer_way_of_life,112,113,1);
	map_set_cell_plain(&dornauer_way_of_life,111,111,1);
	map_set_cell_plain(&dornauer_way_of_life,115,112,1);
	map_set_cell_plain(&dornauer_way_of_life,119,113,1);
	map_set_cell_plain(&dornauer_way_of_life,118,111,1);
	map_set_cell_plain(&dornauer_way_of_life,112,113,1);
	map_set_cell_plain(&dornauer_way_of_life,113,115,1);
	map_set_cell_plain(&dornauer_way_of_life,113,112,1);
	map_set_cell_plain(&dornauer_way_of_life,115,113,1);
	map_set_cell_plain(&dornauer_way_of_life,111,114,1);
	map_set_cell_plain(&dornauer_way_of_life,115,113,1);
	map_set_cell_plain(&dornauer_way_of_life,115,114,1);
	map_set_cell_plain(&dornauer_way_of_life,114,116,1);
	map_set_cell_plain(&dornauer_way_of_life,115,115,1);
	map_set_cell_plain(&dornauer_way_of_life,115,113,1);
	map_set_cell_plain(&dornauer_way_of_life,5,2,1);
	map_set_cell_plain(&dornauer_way_of_life,5,1,1);
	map_set_cell_plain(&dornauer_way_of_life,5,0,1);
	map_set_cell_plain(&dornauer_way_of_life,5,6,1);
	map_set_cell_plain(&dornauer_way_of_life,5,7,1);
	map_set_cell_plain(&dornauer_way_of_life,5,8,1);
	map_set_cell_plain(&dornauer_way_of_life,5,9,1);
	map_set_cell_plain(&dornauer_way_of_life,110,132,1);
	map_set_cell_plain(&dornauer_way_of_life,113,131,1);
	map_set_cell_plain(&dornauer_way_of_life,110,134,1);
	map_set_cell_plain(&dornauer_way_of_life,100,132,1);
	map_set_cell_plain(&dornauer_way_of_life,103,131,1);
	map_set_cell_plain(&dornauer_way_of_life,100,134,1);
	map_set_cell_plain(&dornauer_way_of_life,110,130,1);
	map_set_cell_plain(&dornauer_way_of_life,113,129,1);
	map_set_cell_plain(&dornauer_way_of_life,112,130,1);

	while (1) 
	{
		if(ticker0.r.Q)
		{
			printf("\[%lli\]\t%lf sec\n",ticker0.r.ticks,get_SDL_GetTicks_seconds());
			map_evolve(&dornauer_way_of_life);
		}

		while (SDL_PollEvent(&e)) 
		{
			switch (e.type) 
			{
				case SDL_QUIT:
					goto MAIN_END;	
					break;
				case SDL_KEYDOWN:
					io_handle_keydown(&e.key);
					break;
				case SDL_KEYUP:
					io_handle_keyup(&e.key);
					break;
				case SDL_MOUSEMOTION:
					io_handle_mousemotion(&e.motion);
					break;
				case SDL_MOUSEBUTTONDOWN:
					io_handle_mousebuttondown(&e.button);
					break;
				case SDL_MOUSEBUTTONUP:
					io_handle_mousebuttonup(&e.button);
					break;
				case SDL_MOUSEWHEEL:
					io_handle_mousewheel(&e.wheel);
					break;

				default: 
					break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		map_draw(&dornauer_way_of_life,renderer);
		SDL_RenderPresent(renderer);

		ticker(&ticker0);
	}

MAIN_END:
	map_free(&dornauer_way_of_life);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void ruleset(struct map* m)
{
	for(int i=0; i<m->size;i++)
		for(int j=0; j<m->size;j++)
		{
			int cells_alive=0;
			int cells_growing=0;
			int cells_dying=0;
			int xmin=i*m->size;
			int xmax=(i*m->size)+m->size;
			int ymin=0;
			int ymax=m->size*m->size;
			int pos=(i*m->size)+j;
			char* cell0=(m->cell_plain0+(i*m->size)+j);
			char* cell1=(m->cell_plain1+(i*m->size)+j);
			for(int o=-1;o<2;o++)
			{
				char xconf=pos+o<xmax&&pos+o>xmin ? 1 : 0;
				if(xconf)
				{
					if(*(cell0+o)==1)
						cells_alive++;
					if(*(cell0+o)==2)
						cells_dying++;
					if(*(cell0+o)==3)
						cells_growing++;
				}
				if(pos-(m->size)+o>ymin && xconf)
				{
					if(*(cell0-(m->size)+o)==1)
						cells_alive++;
					if(*(cell0-(m->size)+o)==2)
						cells_dying++;
					if(*(cell0-(m->size)+o)==3)
						cells_growing++;
				}
				if(pos+(m->size)+o<ymax && xconf)
				{
					if(*(cell0+(m->size)+o)==1)
						cells_alive++;
					if(*(cell0+(m->size)+o)==2)
						cells_dying++;
					if(*(cell0+(m->size)+o)==3)
						cells_growing++;
				}
			}
#if 0
			if(*cell0==1) cells_alive--;

			if(*cell0==2) *cell1=0; 
			else if(*cell0==1)
				if((cells_alive)<2) *cell1=2;
				else if((cells_alive+cells_dying)>4) *cell1=2;
				else;
			else if(cells_alive==2) *cell1=1;
			else *cell1=*cell0;
#endif
#if 0
			if(*cell0==1) cells_alive--;

			if(*cell0==2) *cell1=0; 
			else if(*cell0==3) *cell1=1;
			else if(*cell0==1)
				if((cells_alive)<2) *cell1=2;
				else if((cells_alive+cells_dying+cells_growing)>3) *cell1=2;
				else;
			else if(cells_alive==2) *cell1=3;
			else *cell1=*cell0;
#endif
#if 0 //STAR TREK
			if(*cell0==1) cells_alive--;

			else if(*cell0==1)
				if((cells_alive)==2 || cells_alive==4 || cells_alive==8) *cell1=0;
				else;
			else if(cells_alive==2) *cell1=1;
			else *cell1=*cell0;
#endif
			if(*cell0==1) cells_alive--;

			if(*cell0==2) *cell1=3;	
			else if(*cell0==3) *cell1=0;	
			else if(*cell0==1)
				if(cells_alive<2 || cells_alive>3) *cell1=2;
				else *cell1=1;
			else if(cells_growing==3|| cells_dying==3 || cells_alive==2) *cell1=1;
			else *cell1=*cell0;

		}
}

