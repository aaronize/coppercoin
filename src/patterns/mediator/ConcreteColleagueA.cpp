#include "ConcreteColleagueA.h"
#include <iostream>

using namespace std;

ConcreteColleagueA::ConcreteColleagueA()
{

}

ConcreteColleagueA::~ConcreteColleagueA()
{

}

void ConcreteColleagueA::sendmsg(int to, char *str)
{
    cout << "send msg from colleagueA, to:" << to << endl;
    m_pMediator->operation(to, str);
}

void ConcreteColleagueA::recvmsg(char *str)
{
    cout << "ConcreteColleagueA received msg:" << str << endl;
}
