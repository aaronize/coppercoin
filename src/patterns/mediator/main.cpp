// https://design-patterns.readthedocs.io/zh_CN/latest/behavioral_patterns/mediator.html

#include <iostream>
#include "ConcreteColleagueA.h"
#include "ConcreteColleagueB.h"
#include "ConcreteMediator.h"

using namespace std;

int main(int argc, char *argv[])
{
    // 多态
    Colleague *pa = new ConcreteColleagueA();
    Colleague *pb = new ConcreteColleagueB();
    ConcreteMediator *pm = new ConcreteMediator();

    pm->registered(1, pa);
    pm->registered(2, pb);

    pa->sendmsg(2, "hello, i am a");
    pb->sendmsg(1, "hello, i am b");

    delete pa, pb, pm;
    return 0;
}
