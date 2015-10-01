//
//  lineart.c
//  LineArt
//
//  Created by Allek Mott on 10/1/15.
//  Copyright © 2015 Loop404. All rights reserved.
//


#include <stdlib.h>
#include "lineart.h"

int genDifference() {
    // generate random number between 0 and 2 * MAX
    int diff = rand() % (MAX_LINE_LENGTH * 2 + 1);
    
    // subtract MAX -> -MAX <= diff <= MAX
    diff -= MAX_LINE_LENGTH;
    
    if (diff == 0)
        diff = genDifference();
    
    return diff;
}

void easyLine(struct line *l, int x1, int y1, int x2, int y2) {
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
}

void getMidpoint(struct line *l, struct point *p) {
    p->x = (l->x1 + l->x2) / 2;
    p->y = (l->y1 + l->y2) / 2;
}

void genNextLine(struct line *previous, struct line *current, int lineNo) {
    int vertical = (lineNo % 2 == 1);
    
    int diff = genDifference();
    
    struct point midpoint;
    
    getMidpoint(previous, &midpoint);
    int x1, x2, y1, y2;
    
    x1 = midpoint.x;
    y1 = midpoint.y;
    
    if (vertical) {
        // when moving vertically, x won't change
        x2 = x1;
        y2 = y1 + diff;
    } else {
        // when moving horizontally, y won't change
        y2 = y1;
        x2 = x1 + diff;
    }
    easyLine(current, x1, y1, x2, y2);
}