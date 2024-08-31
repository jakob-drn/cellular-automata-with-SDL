#pragma once

#include "ticker.h"
#define PI 3.141592654
#define SCREEN_WIDTH 2520
#define SCREEN_HEIGHT 1376

extern double global_draw_scaling;
extern int global_draw_offset_x;
extern int global_draw_offset_y;
extern int global_mouse_pos_x;
extern int global_mouse_pos_y;

extern struct ticker ticker0;

#define xstr(s) str(s)
#define str(s) #s

// fprintf(stderr, "%s:%s:%i:%s\n",__FILE__,__func__,__LINE__,str(ERROR_CALLOC_FAILD));

// E R R O R s 
#define ERROR_CALLOC_FAILD 0x1

// W A R N I N G s
#define WARNING_AVOIDED_OUT_OF_BOUNCE 0xA1
