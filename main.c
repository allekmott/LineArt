//
//  main.c
//  LineArt
//
//  Created by Allek Mott on 8/31/15.
//  Copyright (c) 2015 Loop404. All rights reserved.
//

#include <SDL2/SDL.h>

#include "sloth.h"


int main(int argc, const char *argv[]) {
    SDL_Window *win;
    SDL_Renderer *g;
    
    initSDL();
    
    printf("SDL_Init success!\n");
    
    win = getWindow();
    g = getRenderer(win);
    
    // Define some nice colors
    struct color blue = {0, 0, 255, 255};
    
    // clear screen
    clearScreen(g);
    
    // new rect @ 50, 50 w/ dimms 50x50
    SDL_Rect rect = {50, 50, 50, 50};
    setColor(g, &blue);
    fillRect(g, &rect);
    render(g);
    delay(5000);
    
    cleanup(g, win);
    
    return 0;
}
