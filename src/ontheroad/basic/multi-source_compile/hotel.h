/*
hotel.c中的常量定义和函数声明
 */

#ifndef __MULTI_SOURCE_COMPILE_HOTEL_H__
#define __MULTI_SOURCE_COMPILE_HOTEL_H__

#define QUIT        5
#define HOTEL_1     80.00
#define HOTEL_2     125.00
#define HOTEL_3     155.00
#define HOTEL_4     200.00
#define DISCOUNT    0.95
#define STARS       "********************************"

// 给出选项列表
int menu(void);

// 返回预订的天数
int getBookedNights(void);

// 计算价格
void showPrice(double hotelRate, int bookedNights);

#endif
