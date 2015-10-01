//
//  main.c
//  LineArt
//
//  Created by Allek Mott on 8/31/15.
//  Copyright (c) 2015 Loop404. All rights reserved.
//

#include <SDL2/SDL.h>

SDL_Window *win;
SDL_Renderer *g;
SDL_Surface *bmp;
SDL_Texture *tex;

void cleanup() {
    if (tex != NULL)
        SDL_DestroyTexture(tex);
    if (g != NULL)
        SDL_DestroyRenderer(g);
    if (win != NULL)
        SDL_DestroyWindow(win);
}

int gtfo() {
    cleanup();
    fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
    return 1;
}

int main(int argc, const char *argv[]) {
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return gtfo();
    
    printf("SDL_Init success!\n");
    
    win = SDL_CreateWindow("LineArt",
                           SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED,
                           500,
                           500,
                           SDL_WINDOW_SHOWN);
    if (win == NULL)
        return gtfo();
    
    g = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (win == NULL)
        return gtfo();
    
    bmp = SDL_LoadBMP("/Users/allek/Developer/LineArt/LineArt/hello.bmp");
    if (bmp == NULL)
        return gtfo();
    
    tex = SDL_CreateTextureFromSurface(g, bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL)
        return gtfo();
    
    int i;
    for (i = 0; i < 3; ++i) {
        SDL_RenderClear(g);
        
        SDL_RenderCopy(g, tex, NULL, NULL);
        
        SDL_RenderPresent(g);
        
        SDL_Delay(1000);
    }
    
    cleanup();
    
    return 0;
}
