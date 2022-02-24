





[TOC]

### C++书籍推荐

---

C++ 书籍：
#### 基础
《C++ Primer》（作者是C++第一个编译器的开发者）
《C++ Prpgramming Language》（作者是C++之父）

#### 专家建议

《Effective C++》

#### STL模板库

《The C++ Standard Library》
《STL源码剖析》

#### 方案

1. 《C++ Primer》
2. 《深度探索C++对象模型》
3. 《Effective C++》
4. （可选）写windows应用程序：《windows核心编程》
5. （可选）写linux应用程序：《UNIX环境高级编程》
6. 《设计模式：可复用面向对象软件的基础》
7. （模板）《C++ Templates: The Complete Guide》



### 单例模式 singleton
---
```
class A P
{
pubilc:
    static A& getInstance();
    setup() {...}
private:
    A();
    A(const A& rhs);
    ...
};

A& A::getInstance() 
{
    static A a;
    return a;
}
```



### 所谓stack(栈) 所谓heap(堆)

---
Stack，是存在于某作用域（scope）的一块内存空间（memory space）。
例如当你调用函数，函数本身即会形成一个stack用来放置它所接收的参数，以及返回的地址。
在函数本体（function body）内声明的任何变量，其所是用的内存块都取自上述stack。

Heap，或谓system heap，是指由操作系统提供的一块全局（global）内存空间，程序可动态分配（dynamic allocated）从其中获得若干区块（blocks）。
可以在程序任何位置以new的方式动态获得，切记获取后要去释放。

1. c1所占用的空间来自stack，c1便是所谓的stack object，其生命在作用域（scope）结束之际结束。这个作用域内的object，又称为auto object，因为它会被自动清空
2. c2便是所谓的static object，其生命在作用域（scope）结束之后仍然存在，直到整个程序结束
3. c3便是所谓的global object（全局对象），其生命在程序结束之后才结束，也可以把它视为一种static object，其作用域是整个程序
4. complex(3)是个临时对象，所占用的空间是以new自heap动态分配得到，并由p指向
5. p所指的便是heap object，其生命在它被delete时结束，如果不加delete，则会出现内存泄露（memory leak），因为当作用域结束，p所指向的heap object仍然存在，但指针p的生命却结束了，作用域之外再也看不到p（也就没机会delete p）


```
class Complex { ... };
...
Complex c3(1, 2);

{
    Complex c1(1, 2);
    static Complex c2(1, 2);
    Complex* p = new Complex(3);
    ...
    delete p;
}
```

#### new：先分配memory，再调用ctor（构造函数）

```C++
Complex* pc = new Complex(1, 2);

// 编译器转化为：

// 1.分配内存，其内部调用malloc(n)，即先分配内存
void mem = operator new(sizeof(Complex));

// 2.转型
pc = static_cast<Complex*>(mem);

// 3.构造函数，相当于 Complex::Complex(this,1,2); 这里的this相当于pc
pc->Complex::Complex(1, 2);
```

#### delete：先调用dtor（析构函数），再释放内存

```
Complex* pc = new String("Hello");
...
delete ps;

// 编译器转化为

// 1.析构函数，析构的是类中的指针类型的私有变量
String::~String(ps);

// 2. 释放内存，其内部调用free(ps)，释放的ps本身占用的内存
operator delete(ps);
```



![image-20220224173747794](../pic/image-20220224173747794.png)







