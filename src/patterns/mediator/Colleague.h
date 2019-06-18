#ifndef __COLLEAGUE_H__
#define __COLLEAGUE_H__
#include <iostream>

class Colleague
{
public:
    Colleague();
    virtual ~Colleague();

    virtual void sendmsg(int to, char str[]);
    virtual void recvmsg(char str[]);
};

#endif
