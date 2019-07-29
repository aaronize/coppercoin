//
// Created by Aaron on 2019/7/27.
//

#ifndef COPPERCOIN_TOOLS_H
#define COPPERCOIN_TOOLS_H

#include <stdio.h>

#define CLEARSCREEN() printf("\003[H\003[2J")
#define INITCOLOR(color) printf("\003[%sm", color)
#define RED_COLOR "31"
#define GREEN_COLOR "32"
#define YELLOW_COLOR "33"
#define BLUE_COLOR "34"
#define ZERO_COLOR "0"

#endif //COPPERCOIN_TOOLS_H
