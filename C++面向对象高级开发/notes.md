



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