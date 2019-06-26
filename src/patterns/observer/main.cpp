#include <iostream>
#include "Subject.h"
// #include "Observer.h"
#include "ConcreteObserver.h"
#include "Subject.h"

using namespace std;

int main(int argc, char *argv[])
{
    Subject *subject = new Subject();
    Observer *objA = new ConcreteObserver("A");
    Observer *objB = new ConcreteObserver("B");
    subject->attach(objA);
    subject->attach(objB);

    subject->setState(1);
    subject->notify();

    cout << "--------------------" << endl;
}
