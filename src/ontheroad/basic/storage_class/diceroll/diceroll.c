/* diceroll.c 掷骰子 */

#include <stdio.h>
#include <stdlib.h>
#include "diceroll.h"

int rollCount = 0;

static int rollem(int sides)
{
    int roll;

    roll = rand() % sides + 1;

    ++rollCount;
    return roll;
}

int rollNDice(int dice, int sides)
{
    int d;
    int total = 0;
    if (sides < 2)
    {
        printf("Need at least 2 sides.\n");
        return -2;
    }
    if (sides < 1)
    {
        printf("Need at least 1 die.\n");
        return -1;
    }
    for (d = 0; d < dice; d++)
        total += rollem(sides);
    
    return total;
}
