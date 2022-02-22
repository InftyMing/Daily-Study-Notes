



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
3. 
4. complex(3)是个临时对象，所占用的空间是以new自heap动态分配得到，并由p指向


```
class Complex { ... };
...
Com

{
    Complex c1(1, 2);
    static Complex c2(1, 2);
    Complex* p = new Complex(3);
}
```