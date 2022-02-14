// guard 防卫式声明，作用：防止由于同一个头文件被包含多次，而导致了重复定义
#ifndef __COMPLEX__
#define __COMPLEX__

#include <cmath>
#include <iostream>

// forward declarations 前置声明
class ostream;
class complex;

complex& __doapl (complex* ths, const complex& r);

// class declarations 类声明
class complex
{
public:
    /*
        constructor (ctor 构造函数) 函数名称一定与类名称相同
        构造函数可以有很多个，这种做法即 overloading(重载)
    */
    complex (double r = 0, double i = 0)    // default argument (默认实参)
        : re(r), im(i)  // initialization list (初值列 初始列) 相比于在函数体内赋值，效率更高
    {}
    complex& operator += (const complex&);
    /*
        函数若在 class body 内定义完成，便成为 inline 候选人，inline 函数非常快
        一般比较简单的函数，编译器有能力会将其变成 inline 函数，取决于编译器本身
    */
    double real() const { return re; }  // 这里 const 的意思是不改变数据中的内容
    double imag() const { return im; }

private:
    double re, im;
    
    /* 
        - 参数传递：pass by value vs. pass by reference(to const)
        pass by value：值传递，把数据整包传过去，但是数据可能很大，所以尽可能使用传引用的方式
        pass by reference：传引用，传递速度很快，最好所有参数传递都传引用，如果传过去不希望对方修改，则加上const
        - 返回值传递：return by value vs. return by reference(to const)
        返回值的传递也最好传引用

        - 相同 class 的各个 objects 互为 friends(友元)
    */
    friend complex& __doapl (complex*, const complex&);

    // 不带指针的类多半不用析构函数
};

// class definition 类定义
inline double imag (const complex& x) 
{
    return x.imag();
}

inline double real (const complex& x) 
{
    return x.real();
}

// 第一个参数将会被改动，第二个参数加了const将不会被改动
inline complex& __doapl (complex* ths, const complex& r)
{
    // 自由取得 friend 的 private 成员
    ths->re += r.re;
    ths->im += r.im;
    // return by reference，好处是传递者无需知道接收者是以reference形式接收，返回的是一个object
    return *ths;
}

/*
    所有的成员函数一定带着一个隐藏的参数this，下面代码等价于:

    inline complex& complex::operator += (this, const complex& r) {
        return __doapl(this, r);
    }

    但是在实际定义时，不能显示写出。this位置未必都在最左侧，具体要看编译器
    this是一个指针，以下面调用为例，this表示c2，r即是c1
    谁调用这个函数，this就指向谁

    complex c1(2, 1);
    complex c2(5);
    c2 += c1

*/
inline complex& complex::operator += (const complex& r)
{
    return __doapl(this, r);
}

// operator overloading 操作符重载、非成员函数
inline complex operator + (const complex& x, const complex& y)
{
    // 绝不可return by reference，因为返回的必定是个local object，换言之，临时对象不能return by reference
    return complex(real(x) + real(y), imag(x) + imag(y));
}

inline complex operator + (const complex& x, double y)
{
    return complex(real(x) + y, imag(x));
}

inline complex operator + (double x, const complex& y)
{
    return complex(x + real(y), imag(y));
}

inline complex operator + (const complex& x)
{
    return x;
}

inline complex operator - (const complex& x)
{
    return complex(-real(x), -imag(x));
}

inline bool operator == (const complex& x, const complex& y)
{
    return real(x) == real(y) && imag(x) == imag(y);
}

inline bool operator == (const complex& x, double y)
{
    return real(x) == y && imag(x) == 0;
}

inline bool operator == (double x, const complex& y)
{
    return x == real(y) && imag(y) == 0;
}
// 共轭复数
inline complex conj (const complex& x)
{
    return complex(real(x), -imag(x));
}

/*
    1. 传入的参数os不加const，因为os相当于count，向cout中写入任何信息时都在改变cout的状态
    调用示例：
    complex c1(2, 1);
    cout << conj(c1);
    
    2. 这里函数返回值不能是void，而是返回引用，因为可能存在这种连续输出的情况，cout<<c1的结果类型为ostream，
    且需要能继续接收conj(c1)的信息
    cout << c1 << conj(c1);
*/
ostream& operator << (ostream& os, const complex& x) {
    return os << '(' << real(x) << ',' << imag(x) << ')';
}

#endif