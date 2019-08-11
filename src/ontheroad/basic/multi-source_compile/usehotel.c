/*
旅馆房间收费程序

gcc -o mge_hotel hotel.c usehotel.c
 */

#include <stdio.h>
#include "hotel.h"

int main(void)
{
    int bookedNights;
    double hotelRate;
    int code;

    while ((code = menu()) != QUIT)
    {
        switch (code)
        {
            case 1: hotelRate = HOTEL_1;
                break;
            case 2: hotelRate = HOTEL_2;
                break;
            case 3: hotelRate = HOTEL_3;
                break;
            case 4: hotelRate = HOTEL_4;
                break;
            default: hotelRate = 0.0;
                printf("Oops! \n");
                break;
        }

        bookedNights = getBookedNights();
        showPrice(hotelRate, bookedNights);
    }
    printf("Thank you and goodbye. \n");

    return 0;
}
