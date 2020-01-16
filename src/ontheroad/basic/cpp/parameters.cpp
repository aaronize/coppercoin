#include <iostream>

using namespace std;

// 值传递
void change1(int n)
{
    cout << "值传递--函数操作地址：" << &n << endl;
    n++;
}

// 引用传递
void change2(int& n)
{
    cout << "引用传递--函数操作地址：" << &n << endl;
    n++;
}

// 指针传递
void change3(int *n)
{
    cout << "指针传递--函数操作地址：" << &n << endl;
    *n = *n + 1;
}

int main()
{
    int n = 10;
    cout << "实参的地址：" << &n << endl;
    change1(n);
    cout << "after change1() n=" << n << endl;  // n的值没有被改变
    change2(n);
    cout << "after change2() n=" << n << endl;
    change3(&n);
    cout << "after change3() n=" << n << endl;

    return 0;
}

/**
 * output：
 * 实参的地址：0x61fe1c
 * 值传递--函数操作地址：0x61fdf0
 * after change1() n=10
 * 引用传递--函数操作地址：0x61fe1c
 * after change2() n=11
 * 指针传递--函数操作地址：0x61fdf0
 * after change3() n=12
 */