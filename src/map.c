#include "map.h"
#include <math.h>

const double MAP_DEFAULT_SCALE=1;
const int MAP_DEFAULT_OFFSET_X=0;
const int MAP_DEFAULT_OFFSET_Y=0;
const int MAP_DEFAULT_CELL_PIXEL_PADDING=2;

static void map_draw_start_cross(struct map* m, SDL_Renderer* renderer);
static void map_draw_crosshair(struct map* m, SDL_Renderer* renderer);
static void map_draw_mark_outline(struct map* m, SDL_Renderer* renderer);
static void map_draw_border(struct map* m, SDL_Renderer* renderer);

void map_set_cell_pixel(struct map* m)
{	
	m->cell_pixel=(int)(sqrt((double)((m->screen_width*m->screen_height))/((double)(((m->size+1)*(m->size+1)))))*(*m->scale*m->scale_offset));	
	//printf("cellp: %i\n",m->cell_pixel);
}

void map_init(struct map* m)
{
	if(m->size<1) m->size=MAP_DEFAULT_MAP_CELLS_SIZE;
	m->cell_plain0=(char*)calloc(m->size*m->size,sizeof(char));
	m->cell_plain1=(char*)calloc(m->size*m->size,sizeof(char));
	if(!m->cell_plain0||!m->cell_plain1) 
	{
		fprintf(stderr, "%s:%s:%i:%s\n",__FILE__,__func__,__LINE__,str(ERROR_CALLOC_FAILD));
		exit(ERROR_CALLOC_FAILD);
	}

	if(m->scale==0) m->scale=&MAP_DEFAULT_SCALE;
	if(m->offset_x==0) m->offset_x=&MAP_DEFAULT_OFFSET_X;
	if(m->offset_y==0) m->offset_y=&MAP_DEFAULT_OFFSET_Y;
	if(m->cell_pixel_padding==0) m->cell_pixel_padding=&MAP_DEFAULT_CELL_PIXEL_PADDING;

	if(m->screen_width==0) m->screen_width=MAP_DEFAULT_SCREEN_WIDTH;
	if(m->screen_height==0) m->screen_height=MAP_DEFAULT_SCREEN_HEIGHT;

	map_set_cell_pixel(m);
}

void map_free(struct map* m)
{
	free(m->cell_plain0);
	free(m->cell_plain1);
}

void map_draw(struct map* m, SDL_Renderer* renderer)
{
	SDL_Rect rect={0};
	map_set_cell_pixel(m);
	map_draw_start_cross(m,renderer);
	
	for(int y=0; y<m->size;y++)
	{
	
		for(int x=0; x<m->size;x++)		
		{
			int state=*(m->cell_plain0+(y*m->size)+(x));
			if(state==0) continue;

			rect.x=(m->cell_pixel*x)+(*m->offset_x); 
			rect.y=(m->cell_pixel*y)+(*m->offset_y);
			rect.w=m->cell_pixel-(*m->cell_pixel_padding);
			rect.h=m->cell_pixel-(*m->cell_pixel_padding);
			//printf("%i %i %i\n",rect.x,rect.y,rect.h);
			switch(state)
			{
				case 1:
					SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
					break;
				case 2:
					SDL_SetRenderDrawColor(renderer,0x00,0xFF,0xFF,0xFF);
					break;
				case 3:
					SDL_SetRenderDrawColor(renderer,0xFF,0x00,0xFF,0xFF);
					break;

				default:
					int tst=state*0.9;
					SDL_SetRenderDrawColor(renderer,0x00,0xFF*tst,0xFF*tst,0xFF*tst);
					break;
			}
			SDL_RenderFillRect(renderer,&rect);
		}
	}
	map_draw_crosshair(m,renderer);
	map_draw_border(m,renderer);
}

int map_set_cell_plain(struct map* m, int x, int y, int state)
{
	if(x>=m->size||y>=m->size)
	{

		fprintf(stderr, "%s:%s:%i:%s(%i)(%i)\n",__FILE__,__func__,__LINE__,str(WARNING_AVOIDED_OUT_OF_BOUNCE),x,y);
		return WARNING_AVOIDED_OUT_OF_BOUNCE;
	}
	int i = (y*m->size)+x;
	m->cell_plain0[i]=state;
	return 0;
}

void map_evolve(struct map* m)
{
	m->ruleset(m);
	for(int i=0;i<m->size*m->size;i++)
	{
		*(m->cell_plain0+i)=*(m->cell_plain1+i);
		*(m->cell_plain1+i)=0;
	}
}

static void map_draw_start_cross(struct map* m, SDL_Renderer* renderer)
{
	int p=*m->cell_pixel_padding/2;
	int x=*m->offset_x+(m->cell_pixel*(m->size/2));
	int y=*m->offset_y+(m->cell_pixel*(m->size/2));
	int a=12;
	double s=*m->scale;
	x-=p;
	y-=p;
	SDL_SetRenderDrawColor(renderer,0xFF,0,0,0xAF);
	SDL_RenderDrawLine(renderer,x,y,(s*a)+x,y);
	SDL_RenderDrawLine(renderer,x,y,x,y+(s*a));
	SDL_RenderDrawLine(renderer,x,y,x,y-(s*a));
	SDL_RenderDrawLine(renderer,x,y,x-(s*a),y);
}

static void map_draw_crosshair(struct map* m, SDL_Renderer* renderer)
{
	int x=m->screen_width/2;
	int y=m->screen_height/2;
	int a=10;
	int s=1;

	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0,0xFF);
	SDL_RenderDrawLine(renderer,x,y,(s*a)+x,y);
	SDL_RenderDrawLine(renderer,x,y,x,y+(s*a));
	SDL_RenderDrawLine(renderer,x,y,x,y-(s*a));
	SDL_RenderDrawLine(renderer,x,y,x-(s*a),y);
}

static void map_draw_border(struct map* m, SDL_Renderer* renderer)
{
	int x=0+(*m->offset_x);
	int y=0+(*m->offset_y);
	int v=(m->cell_pixel*m->size)+(*m->offset_y);
	int w=(m->cell_pixel*m->size)+(*m->offset_x);
	SDL_SetRenderDrawColor(renderer,0xFF,0xF0,0,0xFF);
	SDL_RenderDrawLine(renderer,x,y,w,y);
	SDL_RenderDrawLine(renderer,x,y,x,v);
	SDL_RenderDrawLine(renderer,x,v,w,v);
	SDL_RenderDrawLine(renderer,w,y,w,v);
}
