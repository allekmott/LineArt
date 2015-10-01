//
//  lineart.h
//  LineArt
//
//  Created by Allek Mott on 10/1/15.
//  Copyright © 2015 Loop404. All rights reserved.
//

#ifndef lineart_h
#define lineart_h

#include <stdio.h>

#define MAX_LINE_LENGTH 200

// data structure for line
// (x1, y1) = inital point
// (x2, y2) = final point
struct line {
    int x1;
    int y1;
    int x2;
    int y2;
};

// data structure for point (x, y)
struct point {
    int x;
    int y;
};

// Generate displacement value for new line
int genDifference();

// Easy line resetting/initialization
void easyLine(struct line *l, int x1, int y1, int x2, int y2);


// Calculates midpoint of line l,
// stores in point p
void getMidpoint(struct line *l, struct point *p);

#endif /* lineart_h */
