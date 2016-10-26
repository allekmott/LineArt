//
//  sloth.c
//  LineArt
//
//  Created by Allek Mott on 10/1/15.
//  Copyright © 2015 Loop404. All rights reserved.
//

#include "sloth.h"
#include <SDL2/SDL.h>

struct color clearColor = {255, 255, 255, 255};

void cleanup(SDL_Renderer *r, SDL_Window *w) {
    if (r != NULL)
        SDL_DestroyRenderer(r);
    if (w != NULL)
        SDL_DestroyWindow(w);
    SDL_Quit();
}

void gtfo(SDL_Renderer *r, SDL_Window *w) {
    cleanup(r, w);
    fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
    exit(1);
}

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return gtfo(NULL, NULL);
}

SDL_Window *getWindow(int width, int height) {
    SDL_Window *w = SDL_CreateWindow("LineArt",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     width,
                                     height,
                                     SDL_WINDOW_SHOWN);
    if (w == NULL) {
        gtfo(NULL, w);
    }
    return w;
}

void getWindowSize(SDL_Window *w, int *width, int *height) {
    SDL_GetWindowSize(w, width, height);
}

SDL_Renderer *getRenderer(SDL_Window *w) {
    SDL_Renderer *r = SDL_CreateRenderer(w, 0,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (r == NULL)
        gtfo(r, w);
    return r;
}

void setColor(SDL_Renderer* r, struct color *c) {
    SDL_SetRenderDrawColor(r, c->r, c->g, c->b, c->a);
}

void setClearColor(struct color *c) {
    clearColor = *c;
}

void clearScreen(SDL_Renderer *r) {
    struct color c; // to store pre-clear draw color
    SDL_GetRenderDrawColor(r, &(c.r), &(c.g), &(c.b), &(c.a));

    SDL_SetRenderDrawColor(r, clearColor.r, clearColor.g, clearColor.b,
            clearColor.a);
    SDL_RenderClear(r);
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
}

void drawLine(SDL_Renderer *r, struct line *l) {
    SDL_RenderDrawLine(r, l->x1, l->y1, l->x2, l->y2);
}

void drawAllLines(SDL_Renderer *r, struct node *root) {
    struct node *node = root;
    while (node != NULL) {
        drawLine(r, node->line);
        if ((node = node->next) == NULL) break;
    }
}

void render(SDL_Renderer *r) {
    SDL_RenderPresent(r);
}

void delay(Uint32 delayTimeMs) {
    SDL_Delay(delayTimeMs);
}
