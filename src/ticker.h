#pragma once

struct ticker_r 
{
	long long ticks;
	char Q;
	double time_of_start;
	char error;
};

struct ticker_w 
{
	double (*clock)();
	char start;
	char rst;
	double duration;
};

struct ticker_intern
{
	char init;
	double time_tick_start;
};

struct ticker 
{
	struct ticker_r r;
	struct ticker_w w;
	struct ticker_intern intern;
};



void ticker(struct ticker *t);

