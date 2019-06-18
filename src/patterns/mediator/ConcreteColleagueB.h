#ifndef __CONCRETE_COLLEAGUE_B_H__
#define __CONCRETE_COLLEAGUE_B_H__

#include "Colleague.h"

class ConcreteColleagueB: public Colleague
{
public:
    ConcreteColleagueB();
    virtual ~ConcreteColleagueB();

    virtual void sendmsg(int to, char *str);
    virtual void recvmsg(char *str);
};

#endif
