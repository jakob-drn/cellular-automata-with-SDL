#pragma once

#include <SDL2/SDL.h>

void io_handle_keydown(const SDL_KeyboardEvent* key);
void io_handle_keyup(const SDL_KeyboardEvent* key);

void io_handle_mousemotion(const SDL_MouseMotionEvent* motion);
void io_handle_mousebuttondown(const SDL_MouseButtonEvent* button);
void io_handle_mousebuttonup(const SDL_MouseButtonEvent* button);
void io_handle_mousewheel(const SDL_MouseWheelEvent* wheel);
