// guard 防卫式声明
#ifndef __COMPLEX__
#define __COMPLEX__

#include <cmath>

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

inline complex& __doapl (complex* ths, const complex& r)    // 第一个参数将会被改动，第二个参数将不会被改动
{
    // 自由取得 friend 的 private 成员
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex& complex::operator += (const complex& r)
{
    return __doapl(this, r);
}

#endif