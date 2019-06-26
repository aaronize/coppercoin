#include "Subject.h"

Subject::Subject()
{}

Subject::~Subject()
{}

void Subject::attach(Observer* pObserver)
{
    m_vtObs.push_back(pObserver);
}

void Subject::detach(Observer* pObserver)
{
    for (vector<Observer*>::iterator it = m_vtObs.begin(); it != m_vtObs.end(); it++)
    {
        if (*it == pObserver)
        {
            m_vtObs.erase(it);
            return;
        }
    }
}

void Subject::notify()
{
    for (vector<Observer*>::iterator it = m_vtObs.begin(); it != m_vtObs.end(); it++)
    {
        (*it)->update(this);
        return;
    }
}

void Subject::setState(int s)
{
    state = s;
}
