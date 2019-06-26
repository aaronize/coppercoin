#if !defined(__CONCRETE_OBSERVER_H__)
#define __CONCRETE_OBSERVER_H__

#include "Observer.h"
#include <string>
using namespace std;

class ConcreteObserver : public Observer 
{
public:
    ConcreteObserver(string);
    virtual ~ConcreteObserver();
    virtual void update(Subject *sub);

private:
    string m_obsName;
    int m_observerState;
};

#endif