//
//  main.c
//  LineArt
//
//  Created by Allek Mott on 8/31/15.
//  Copyright (c) 2015 Loop404. All rights reserved.
//

#include <SDL2/SDL.h>
#include <time.h>
#include <unistd.h>

#include "sloth.h"
#include "lineart.h"

int main(int argc, const char *argv[]) {
    SDL_Window *win;
    SDL_Renderer *g;
    
    // Define some nice colors
    struct color blue = {0, 0, 255, 255};
    
    // seed dat RNG
    srand((unsigned int) time(NULL));
    
    initSDL();
    
    // grab a window and a renderer
    win = getWindow();
    g = getRenderer(win);
    
    // clear screen
    clearScreen(g);
    
    // blue lines (for now)
    setColor(g, &blue);
    
    int running = 1;
    
    while (running) {
        clearScreen(g);
        int win_width, win_height;
        getWindowSize(win, &win_width, &win_height);
        
        // start at center of window
        int x1 = win_width / 2,
            y1 = win_height / 2;
        
        // x2, y2 change in y; only one changes per line
        // first line will always be vertical, so only
        // y will change
        int x2 = x1,
            y2 = y1 + genDifference();
        
        struct line l = {x1, y1, x2, y2};
        drawLine(g, &l);
        
        render(g);
        sleep(1);
    }
    
    cleanup(g, win);
    
    return 0;
}
