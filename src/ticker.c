#include "ticker.h"

/*void ticker_print_tick_and_et()
{ 
	int x,y;
	getmaxyx(stdscr,y,x);
	mvprintw(y-1,x-20,"t %lli",global_ticker.ticks);
	mvprintw(y-2,x-20, "et %f",ELAPSED_TIME_SEC);
}
*/


void ticker(struct ticker* t)
{
	if(t->w.rst)
	{
		t->w.start=0;
		t->r.Q=0;
		t->r.error=0;
		t->r.ticks=0;
		t->intern.init=0;
		t->r.time_of_start=0;
		t->intern.time_tick_start=0;
		t->w.rst=0;
	}
	if(t->w.start && !t->intern.init)
	{
		t->r.time_of_start=t->w.clock();                         
		t->intern.time_tick_start=t->w.clock();
		t->r.Q=0;
		t->r.ticks=0;
		t->intern.init=1;
	}
	if(t->intern.init)
	{
		if((t->w.clock()-t->intern.time_tick_start)
			< t->w.duration)
			t->r.Q=0;
		else 
		{
			t->intern.time_tick_start=t->w.clock();
			t->r.ticks++;
			t->r.Q=1;
		}
	}
}
