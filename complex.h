#ifndef __MYCOMPLEX__
#define __MYCOMPLEX__

// 前向声明: 告诉编译器 complex(复数) 类的存在，但是不知道它的具体内容，因此不能使用它的成员，只能使用指针或引用。
class complex;                                    // 前向声明，告诉编译器 complex(复数) 类的存在
complex &__doapl(complex *ths, const complex &r); // 声明 __doapl 函数：doapl : 它代表的含义是“做赋值加法（do assignment plus）”，表示对某个变量进行自增操作。
complex &__doami(complex *ths, const complex &r); // 声明 __doami 函数：doami : 它代表的含义是“做赋值减法（do assignment minus）”，表示对某个变量进行自减操作。
complex &__doaml(complex *ths, const complex &r); // 声明 __doaml 函数：doaml : 它代表的含义是“做赋值乘法（do assignment multiply）”，表示对某个变量进行自乘操作。

// 类的定义
class complex
{
public:
    // 构造函数
    complex(double r = 0, double i = 0) // constructor 构造函数，double r = 0, double i = 0 表示默认实参
        : re(r), im(i)                  // 初值列，初始化
    {
    }

    // 重载运算符
    complex &operator+=(const complex &); // operator+=: 重载运算符+=，返回值为 complex 类型的引用，参数为 const 类型的 complex 类型的引用，表示对复数进行加法操作，但是不改变原来的复数的值，而是返回一个新的复数的值。
    complex &operator-=(const complex &); // operator-=: 重载运算符-=，返回值为 complex 类型的引用，参数为 const 类型的 complex 类型的引用，表示对复数进行减法操作，但是不改变原来的复数的值，而是返回一个新的复数的值。
    complex &operator*=(const complex &); // operator*=: 重载运算符*=，返回值为 complex 类型的引用，参数为 const 类型的 complex 类型的引用，表示对复数进行乘法操作，但是不改变原来的复数的值，而是返回一个新的复数的值。
    complex &operator/=(const complex &); // operator/=: 重载运算符/=，返回值为 complex 类型的引用，参数为 const 类型的 complex 类型的引用，表示对复数进行除法操作，但是不改变原来的复数的值，而是返回一个新的复数的值。

    // 其他函数
    double real() const { return re; } // const 表示不允许修改对象的值，只是读取 re 的值
    double imag() const { return im; }

private:
    // private: 表示私有成员，只能在类内部访问，不能在类外部访问
    double re, im;

    // 友元函数: 友元函数可以访问类的私有成员
    friend complex &__doapl(complex *, const complex &);
    friend complex &__doami(complex *, const complex &);
    friend complex &__doaml(complex *, const complex &);
};

// 内联函数的定义
inline complex &
__doapl(complex *ths, const complex &r) // ths: this 指针，指向当前对象的指针，r: 传入的参数，const 类型的 complex 类型的引用，表示对复数进行加法操作，但是不改变原来的复数的值，而是返回一个新的复数的值
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex &
complex::operator+=(const complex &r)
{
    return __doapl(this, r);
}

inline complex &
__doami(complex *ths, const complex &r)
{
    ths->re -= r.re; // 这里必须用到友元函数(在 class 中定义 friend complex& __domai ...)，因为私有成员不能在类外部访问
    ths->im -= r.im;
    return *ths;
}

inline complex &
complex::operator-=(const complex &r)
{
    return __doami(this, r);
}

inline complex &
__doaml(complex *ths, const complex &r) // 复数乘等运算
{
    double f = ths->re * r.re - ths->im * r.im;
    ths->im = ths->re * r.im + ths->im * r.re;
    ths->re = f;
    return *ths;
}

inline complex &
complex::operator*=(const complex &r)
{
    return __doaml(this, r);
}

inline double
imag(const complex &x)
{
    return x.imag();
}

inline double
real(const complex &x)
{
    return x.real(); // 返回复数的实部
}

// 重载运算符的定义，需要定义三种情况：两个复数相加，一个复数和一个实数相加，一个实数和一个复数相加
inline complex
operator+(const complex &x, const complex &y)
{
    return complex(real(x) + real(y), imag(x) + imag(y)); // 返回两个复数的和
}

inline complex
operator+(const complex &x, double y)
{
    return complex(real(x) + y, imag(x)); // 返回复数和实数的和
}

inline complex
operator+(double x, const complex &y)
{
    return complex(x + real(y), imag(y)); // 返回实数和复数的和
}

// 类似的，还有减法、乘法、除法的重载运算符的定义
inline complex
operator-(const complex &x, const complex &y)
{
    return complex(real(x) - real(y), imag(x) - imag(y)); // 返回两个复数的差
}

inline complex
operator-(const complex &x, double y)
{
    return complex(real(x) - y, imag(x)); // 返回复数和实数的差
}

inline complex
operator-(double x, const complex &y)
{
    return complex(x - real(y), -imag(y)); // 返回实数和复数的差
}

inline complex
operator*(const complex &x, const complex &y)
{
    return complex(real(x) * real(y) - imag(x) * imag(y),
                   real(x) * imag(y) + imag(x) * real(y)); // 返回两个复数的积
}

inline complex
operator*(const complex &x, double y)
{
    return complex(real(x) * y, imag(x) * y); // 返回复数和实数的积
}

inline complex
operator*(double x, const complex &y)
{
    return complex(x * real(y), x * imag(y)); // 返回实数和复数的积
}

complex
operator/(const complex &x, double y)
{
    return complex(real(x) / y, imag(x) / y); // 返回复数和实数的商
}

// 重载+表示正值，返回复数的正值；重载-表示负值，返回复数的负值
inline complex
operator+(const complex &x)
{
    return x; // 返回复数的正值
}

inline complex
operator-(const complex &x)
{
    return complex(-real(x), -imag(x)); // 返回复数的负值
}

// 重载==表示相等，返回两个复数是否相等；重载!=表示不等，返回两个复数是否不等
inline bool
operator==(const complex &x, const complex &y)
{
    return real(x) == real(y) && imag(x) == imag(y); // 返回两个复数是否相等
}

inline bool
operator==(const complex &x, double y)
{
    return real(x) == y && imag(x) == 0; // 返回复数和实数是否相等
}

inline bool
operator==(double x, const complex &y)
{
    return x == real(y) && imag(y) == 0; // 返回实数和复数是否相等
}

inline bool
operator!=(const complex &x, const complex &y)
{
    return real(x) != real(y) || imag(x) != imag(y); // 返回两个复数是否不等
}

inline bool
operator!=(const complex &x, double y)
{
    return real(x) != y || imag(x) != 0; // 返回复数和实数是否不等
}

inline bool
operator!=(double x, const complex &y)
{
    return x != real(y) || imag(y) != 0; // 返回实数和复数是否不等
}

// 其他操作
#include <cmath> // 提供sqrt()函数, 用于计算复数的模; 提供cos()函数, 用于计算复数的实部; 提供sin()函数, 用于计算复数的虚部
inline complex
polar(double r, double t)
{
    return complex(r * cos(t), r * sin(t)); // 返回极坐标(r,t)对应的复数
}

inline complex
conj(const complex &x)
{
    return complex(real(x), -imag(x)); // 返回复数的共轭复数
}

inline double
norm(const complex &x)
{
    return real(x) * real(x) + imag(x) * imag(x); // 返回复数的模的平方
}

#endif

// 其他知识点备注：
// pass by reference 引用传递: 函数内部可以修改实参的值; pass by value 值传递(整包传递): 函数内部不能修改实参的值, 但是可以修改实参的副本的值
//  尽量使用 pass by reference 引用传递，因为 pass by value 值传递会产生副本，而且副本的大小是不确定的，所以会影响程序的性能
// friend 声明友元函数: 友元函数可以访问类的私有成员
// complex() : re(0), im(0) {} // 构造函数的重载: copy constructor 拷贝构造函数: 用一个对象初始化另一个对象
// 传递者无需知道接收者是以 reference 形式接收还是以 value 形式接收，只需要知道接收者是以 value 形式接收，那么传递者就会以 value 形式传递，如果接收者是以 reference 形式接收，那么传递者就会以 reference 形式传递。
