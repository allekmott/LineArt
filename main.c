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
    int win_width = 1152,
        win_height = 720;
    int flag_forceinwin = 1;
    
    // Define some nice colors
    struct color blue = {0, 0, 255, 255};
    
    // seed dat RNG
    srand((unsigned int) time(NULL));
    
    initSDL();
    
    // grab a window and a renderer
    win = getWindow(win_width, win_height);
    g = getRenderer(win);
    
    // clear screen
    clearScreen(g);
    
    // blue lines (for now)
    setColor(g, &blue);
    
    // line number; used to decide direction
    int lineNo = 1;
    
    
    // necesary line node structures for linked list:
    
    // root line node in list
    struct node *root = malloc(sizeof(struct node));
    
    // previously generated line node
    struct node *previous;
    
    // line node undergoing generation
    struct node *current;
    
    
    // first line, start at middle, rand length, go from there
    int x1 = win_width / 2,
    y1 = win_height / 2;
    
    // x2, y2 change in y; only one changes per line
    // first line will always be vertical, so only
    // y will change
    int x2 = x1,
    y2 = y1 + genDifference();
    
    struct line *firstLine = easyLine(x1, y1, x2, y2);
    root->line = firstLine;
    root->next = current;
    previous = root;
    
    clearScreen(g);
    drawLine(g, root->line);
    render(g);
    
    // increment line count so loop starts on horizonal
    lineNo++;
    
    delay(1000);
    
    while (1) {
        if (!handleEvents())
            break;
        
        // allocate memory for new node
        current = malloc(sizeof(struct node));
        
        // add to linked list;
        // new is old's next
        previous->next = current;
        
        if (flag_forceinwin) {
            // keep line bound to window bounds
            while (1) {
                current->line = genNextLine(previous->line, lineNo);
                if (current->line->x2 > win_width ||
                    current->line->y2 > win_height)
                    free(current->line);
                else
                    break;
            }
        } else {
            // line can do whatever tf it wants
            current->line = genNextLine(previous->line, lineNo);
        }
        
        // THIS is very necessary;
        // in rendering:
        // iterate through linked list until next is NULL
        // if you don't set new next to null, it thinks theres another
        // value (will be reset to next element in next iteration of loop)
        current->next = NULL;
        
        clearScreen(g);
        drawAllLines(g, root);
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
    
    freeLineList(root);
    cleanup(g, win);
    
    return 0;
}
