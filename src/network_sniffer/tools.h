//
// Created by Aaron on 2019/7/27.
//

#ifndef __COPPERCOIN_TOOLS_H__
#define __COPPERCOIN_TOOLS_H__

#include <stdio.h>

#define CLEARSCREEN() printf("\003[H\003[2J")
#define INITCOLOR(color) printf("\003[%sm", color)
#define RED_COLOR "31"
#define GREEN_COLOR "32"
#define YELLOW_COLOR "33"
#define BLUE_COLOR "34"
#define ZERO_COLOR "0"

#endif //__COPPERCOIN_TOOLS_H__
