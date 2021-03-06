//
//  sloth.h
//  LineArt
//
//  Created by Allek Mott on 10/1/15.
//  Copyright © 2015 Loop404. All rights reserved.
//

#ifndef sloth_h
#define sloth_h

#include <SDL2/SDL.h>
#include "lineart.h"

struct color {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

// Define some nice colors
static struct color GHETTO_BLUE = {0, 0, 255, 255},
    GHETTO_RED = {255, 0, 0, 255},
    GHETTO_GREEN = {0, 255, 0, 255},
    GHETTO_BLACK = {0, 0, 0, 255},
    GHETTO_WHITE = {255, 255, 255, 0};

// clean up (free win, g)
void cleanup(SDL_Renderer *r, SDL_Window *w);

// beautiful function to cleaunup and return error
void gtfo(SDL_Renderer *r, SDL_Window *w);

// initialize sdl
void initSDL();

// grab a window from sdl
SDL_Window *getWindow(int width, int height);

// get size of window, store in int args
void getWindowSize(SDL_Window *w, int *width, int *height);

// grab a window's renderer from sdl
SDL_Renderer *getRenderer(SDL_Window *w);

// set the renderer's color
void setColor(SDL_Renderer *r, struct color *c);

// set clear color (stored in sloth, used to clear
// render with
// clearColor defaults to white (rgb(255, 255, 255));
void setClearColor(struct color *c);

// clear the screen (fill with clearColor)
void clearScreen(SDL_Renderer* r);

// draw line to renderer
void drawLine(SDL_Renderer *r, struct line *l);

// draw all lines in list to renderer
void drawAllLines(SDL_Renderer *r, struct node *root);

// draw renderer to screen
void render(SDL_Renderer *r);

// SDL pause
void delay(Uint32 delayTimeMs);

#endif /* sloth_h */
