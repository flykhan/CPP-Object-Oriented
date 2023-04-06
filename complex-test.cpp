#include "complex.h"
#include <iostream>

using namespace std;

// 重载<<表示输出，输出复数的实部和虚部
ostream &
operator<<(ostream &os, const complex &x) // 第一个参数os，虽然它是引用类型，但也经常被声明为const引用类型。这是因为，os作为输出流对象，其状态（如输出位置）可能会在运算符重载过程中被修改，所以通常来说不应该将其声明为const。如果将os声明为const引用类型，则意味着不允许修改输出流的状态，这可能导致编译错误或者输出结果不正确。
{
    return os << '(' << real(x) << ',' << imag(x) << ')';
}

int main()
{
    complex c1(2, 1);
    complex c2(4, 0);

    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;

    cout << "c1 + c2 = " << c1 + c2 << endl;
    cout << "c1 - c2 = " << c1 - c2 << endl;
    cout << "c1 * c2 = " << c1 * c2 << endl;
    cout << "c1 / 2 = " << c1 / 2 << endl;

    cout << "conj(c1) = " << conj(c1) << endl;        // 返回复数的共轭复数
    cout << "norm(c1) = " << norm(c1) << endl;        // 返回复数的模的平方
    cout << "polar(10,4) = " << polar(10, 4) << endl; // 极坐标(10,4)对应的复数

    cout << "(c1 += c2) = " << (c1 += c2) << endl;

    cout << "(c1 == c2) = " << (c1 == c2) << endl; // 结果为0，表示 false，因为c1和c2不相等
    cout << "(c1 != c2) = " << (c1 != c2) << endl; // 结果为1，表示 true，因为c1和c2不相等
    cout << "+c2 = " << +c2 << endl;
    cout << "-c2 = " << -c2 << endl;

    cout << "(c2 - 2) = " << (c2 - 2) << endl;
    cout << "(5 + c2) = " << (5 + c2) << endl;

    return 0; // 返回0，表示程序运行成功; 返回值通常用来表示错误代码,如返回1表示程序运行失败
}
