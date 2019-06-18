#ifndef __CONCRETE_COLLEAGUE_A_H__
#define __CONCRETE_COLLEAGUE_A_H__

#include "Colleague.h"

class ConcreteColleagueA: public Colleague
{
public:
    ConcreteColleagueA();
    virtual ~ConcreteColleagueA();

    virtual void sendmsg(int to, char str[]);
    virtual void recvmsg(char str[]);
};

#endif
