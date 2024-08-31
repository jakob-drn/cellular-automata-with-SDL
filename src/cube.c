#include "cube.h"

#include <math.h>

static void cube_calc(struct cube* c,int x[8],int y[8],double t)
{
	for(int i=0;i<8;i++)
	{
		
		x[i]=c->ov[i].p.x+(cos(t)*c->ov[i].p.z);
		y[i]=c->ov[i].p.y+(sin(t)*c->ov[i].p.z);
		
	}
}

void cube_draw(struct cube* c,SDL_Renderer* renderer,double t)
{
	static int x[8]={0};
	static int y[8]={0};

	cube_calc(c,x,y,t);
	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderDrawLine(renderer,x[0],y[0],x[1],y[1]);
	SDL_RenderDrawLine(renderer,x[1],y[1],x[2],y[2]);
	SDL_RenderDrawLine(renderer,x[2],y[2],x[3],y[3]);
	SDL_RenderDrawLine(renderer,x[3],y[3],x[4],y[4]);
	SDL_RenderDrawLine(renderer,x[4],y[4],x[5],y[5]);
	SDL_RenderDrawLine(renderer,x[5],y[5],x[6],y[6]);
	SDL_RenderDrawLine(renderer,x[6],y[6],x[7],y[7]);
	SDL_RenderDrawLine(renderer,x[7],y[7],x[0],y[0]);
	SDL_RenderDrawLine(renderer,x[1],y[1],x[6],y[6]);
	SDL_RenderDrawLine(renderer,x[2],y[2],x[5],y[5]);
	SDL_RenderDrawLine(renderer,x[0],y[0],x[3],y[3]);
	SDL_RenderDrawLine(renderer,x[7],y[7],x[4],y[4]);
}

void cube_init(struct cube* c)
{
	int x=c->x,y=c->y,z=c->z,l=c->l;
	for(int i=0;i<8;i++)
		c->ov[i].s=1;
	c->ov[0].p.x=x;
	c->ov[0].p.y=y;
	c->ov[0].p.z=z;
	c->ov[1].p.x=x+l;
	c->ov[1].p.y=y;
	c->ov[1].p.z=z;
	c->ov[2].p.x=x+l;
	c->ov[2].p.y=y+l;
	c->ov[2].p.z=z;
	c->ov[3].p.x=x;
	c->ov[3].p.y=y+l;
	c->ov[3].p.z=z;
	c->ov[4].p.x=x;
	c->ov[4].p.y=y+l;
	c->ov[4].p.z=z+l;
	c->ov[5].p.x=x+l;
	c->ov[5].p.y=y+l;
	c->ov[5].p.z=z+l;
	c->ov[6].p.x=x+l;
	c->ov[6].p.y=y;
	c->ov[6].p.z=z+l;
	c->ov[7].p.x=x;
	c->ov[7].p.y=y;
	c->ov[7].p.z=z+l;
}

