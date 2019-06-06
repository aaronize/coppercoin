#include <iostream>

using namespace std;

// 成员函数、构造函数、析构函数
class Line
{
    public:
        void setLength(double len);
        double getLength(void);
        Line();
        ~Line();

    private:
        double length;
};

// 使用范围解析运算符 ::，成员函数需要在类中预先声明
Line::Line(void)
{
    cout << "object is being created" << endl;
}

Line::~Line(void)
{
    cout << "object is being deleted" << endl;
}

void Line::setLength(double len)
{
    // 可直接访问类内部成员
    cout << "get length: " << getLength() << endl;
    length = len;
}

double Line::getLength(void)
{
    return length;
}

int main()
{
    Line line;

    // 设置长度
    line.setLength(12.0);
    cout << "Length of line: " << line.getLength() << endl;

    return 0;
}
