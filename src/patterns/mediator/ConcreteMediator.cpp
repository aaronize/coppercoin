#include "ConcreteMediator.h"
#include <map>
#include <iostream>

using namespace std;

ConcreteMediator::ConcreteMediator()
{

}

ConcreteMediator::~ConcreteMediator()
{

}

void ConcreteMediator::operation(int to, char *str)
{
    map<int, Colleague*>::const_iterator iter = m_mpColleague.find(to);
    if (iter == m_mpColleague.end())
    {
        cout << "not found this colleague!" << endl;
        return;
    }

    Colleague *pc = iter->second;
    pc->recvmsg(str);

    return;
}

void ConcreteMediator::registered(int to, Colleague *aColleague)
{
    map<int, Colleague*>::const_iterator iter = m_mpColleague.find(to);
    if (iter == m_mpColleague.end())
    {
        m_mpColleague.insert(make_pair(to, aColleague));
        aColleague->setMediator(this);
    }
}
