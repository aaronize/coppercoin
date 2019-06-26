#if !defined(__SUBJECT_H__)
#define __SUBJECT_H__

#include "Observer.h"
#include <vector>
using namespace std;

class Subject
{
public:
    Subject();
    virtual ~Subject();
    Observer *m_Observer;

    void attach(Observer *);
    void detach(Observer *);
    void notify();

    virtual int getState();
    virtual void setState(int);

private:
    int state;
    vector<Observer*> m_vtObs;
};

#endif