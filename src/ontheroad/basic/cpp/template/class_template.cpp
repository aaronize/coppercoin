#include <iostream>

using namespace std;

/**
 * 类模板声明：
 * template<typename param1, typename param2, ...> class class_name {
 *      // TODO;
 * }
 * 
 */

template<class T1, class T2> class Point {
public: 
    Point(T1 x, T2 y): m_x(x), m_y(y) {}
public: 
    T1 getX() const;
    void setX(T1 x);

    T2 getY() const;
    void setY(T2 y);;
private: 
    T1 m_x;
    T2 m_y;
};

// const 给隐含的指针this加const，也就是说这个函数中无法改动数据成员
template<class T1, class T2> T1 Point<T1, T2>::getX() const {
    return this->m_x;
}

template<class T1, class T2> void Point<T1, T2>::setX(T1 x) {
    this->m_x = x;
}

template<class T1, class T2> T2 Point<T1, T2>::getY() const {
    return this->m_y;
}

template<class T1, class T2> void Point<T1, T2>::setY(T2 y) {
    this->m_y = y;
}

int main() {
    Point<int, int> p1(10, 20);
    cout << "x = " << p1.getX() << ", y = " << p1.getY() << endl;

    Point<int, char*> p2(10, "东经180度");
    cout << "x = " << p2.getX() << ", y = " << p2.getY() << endl;

    Point<char*, char*> *p3 = new Point<char*, char*>("东经180度", "北纬210");
    cout << "x = " << p3->getX() << ", y = " << p3->getY() << endl;

    return 0;
}
