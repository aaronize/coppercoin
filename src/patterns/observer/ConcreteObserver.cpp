#include "ConcreteObserver.h"
#include <iostream>
#include <vector>
#include "Subject.h"

using namespace std;

ConcreteObserver::ConcreteObserver(string name)
{
    m_obsName = name;
}

ConcreteObserver::~ConcreteObserver()
{}

void ConcreteObserver::update(Subject* sub)
{
    m_observerState = sub->getState();
    cout << "update observer [" << m_obsName << "] state: [" << m_observerState << "]" << endl;
}
