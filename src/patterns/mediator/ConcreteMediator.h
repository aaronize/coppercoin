#ifndef PATTERNS_CONCRETEMEDIATOR_H
#define PATTERNS_CONCRETEMEDIATOR_H

#include "ConcreteColleagueA.h"
#include "ConcreteColleagueB.h"
#include "Mediator.h"
#include <map>

using namespace std;

class ConcreteMediator: public Mediator 
{
public:
    ConcreteMediator();
    virtual ~ConcreteMediator();

    virtual void operation(int to, char *str);
    virtual void registered(int to, Colleague *aColleague);

private:
    map<int, Colleague*> m_mpColleague;
};

#endif
