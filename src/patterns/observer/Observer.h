#if !defined(__OBSERBER_H__)
#define __OBSERBER_H__
using namespace std;

class Subject;

class Observer
{
public:
    Observer();
    virtual ~Observer();
    virtual void update(Subject *sub);
};

#endif