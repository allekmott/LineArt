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

    if (abs(diff) < 5)
        diff = genDifference();

    return diff;
}

struct line *easyLine(int x1, int y1, int x2, int y2, struct color *color) {
    struct line *l = malloc(sizeof(struct line));
    l->x1 = x1;
    l->y1 = y1;
    l->x2 = x2;
    l->y2 = y2;
    l->color = color;
    return l;
}

void getMidpoint(struct line *l, struct point *p) {
    // midpoint formula!
    p->x = (l->x1 + l->x2) / 2;
    p->y = (l->y1 + l->y2) / 2;
}

struct line *genNextLine(struct line *previous, int lineNo,
        struct color *color) {
    // vertcal on odds, horizontal on evens (1st always vert)
    int vertical = (lineNo % 2 == 1);

    int diff = genDifference();

    struct point midpoint;

    if (previous == NULL) {
        // first line
        midpoint.x = 0;
        midpoint.y = 0;
    } else {
        // not first line
        getMidpoint(previous, &midpoint);
    }

    int x1, x2, y1, y2;

    x1 = midpoint.x;
    y1 = midpoint.y;

    if (vertical) {
        // when moving vertically, x won't change
        x2 = x1;
        y2 = y1 + diff;

        // if line breaks negative window boundaries, reverse direction
        if (y2 < 0)
            y2 = y1 - diff;
    } else {
        // when moving horizontally, y won't change
        y2 = y1;
        x2 = x1 + diff;

        // if line breaks negative window boundaries, reverse direction
        if (x2 < 0)
            x2 = x1 - diff;
    }
    return easyLine(x1, y1, x2, y2, color);
}

void translateLine(struct line *l, int x, int y) {
    l->x1 += x;
    l->x2 += x;
    l->y1 += y;
    l->y2 += y;
}

void freeLineList(struct node *root) {
    struct node *node = root;
    while (node != NULL) {
        struct node *temp = node;
        node = node->next;
        free(temp);
    }
    root = NULL;
}
