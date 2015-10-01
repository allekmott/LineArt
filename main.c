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

int handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                return 0;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        return 0;
                }
                break;
        }
    }
    return 1;
}

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
    
    int lineNo = 1; // line number; used to decide direction
    struct line previous,
                current;
    
    // first line, start at middle, rand length, go from there
    int win_width, win_height;
    getWindowSize(win, &win_width, &win_height);
    
    int x1 = win_width / 2,
    y1 = win_height / 2;
    
    // x2, y2 change in y; only one changes per line
    // first line will always be vertical, so only
    // y will change
    int x2 = x1,
    y2 = y1 + genDifference();
    
    easyLine(&current, x1, y1, x2, y2);
    
    clearScreen(g);
    drawLine(g, &current);
    render(g);
    
    // increment line count so loop starts on horizonal
    lineNo++;
    
    // when we enter the loop, we want the first line
    // to be the previous, because we start the loop
    // at the second
    previous = current;
    delay(1000);
    
    while (1) {
        if (!handleEvents())
            break;
        
        genNextLine(&previous, &current, lineNo);
        
        clearScreen(g);
        drawLine(g, &current);
        render(g);
        
        previous = current;
        lineNo++;
        
        // break up sleeping into smaller segments
        // to allow user to exit faster
        int i;
        for (i = 0; i < 10; i++) {
            if (!handleEvents())
                break;
            delay(100);
        }
        if (i < 10)
            break;
    }
    
    cleanup(g, win);
    
    return 0;
}
