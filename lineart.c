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
    
    return diff;
}