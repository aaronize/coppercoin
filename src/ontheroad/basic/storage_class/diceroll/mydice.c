
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "diceroll.h"

int main(void)
{
    int dice, roll;
    int sides;

    srand((unsigned int)time(0));
    printf("Enter the number of sides per die, 0 to stop.\n");
    while (scanf("%d", &sides) == 1 && sides > 0)
    {
        printf("How many dice?\n");
        scanf("%d", &dice);
        roll = rollNDice(dice, sides);
        printf("You have rolled a %d using %d %d-sided dice.\n", roll, dice, sides);
        printf("--->next roll\nHow many sides? Enter 0 to stop.\n");
    }
    printf("The rollem() function was called %d times.\n", rollCount);
    printf("Good Fortune to you!\n");

    return 0;
}
