#ifndef __MYSTRING__
#define __MYSTRING__

#include <iostream>

/*
    class with pointer members必须有copy ctor和copy op=
    注意，只要类成员中有指针，一定要自己去定义实现拷贝构造函数和拷贝赋值函数
*/

class String
{
public:
    // 构造函数ctor
    String(const char *cstr = 0);
    
    // 拷贝构造函数，拷贝的是类对象
    String(const String &str);
    
    // 拷贝赋值函数，操作符重载
    String& operator = (const String& str);
    
    // 析构函数dtor
    ~String();

    char* get_c_str() const {return m_data;}

private:
    // 动态分配内存
    char *m_data;
};

inline String::String(const char* cstr = 0) 
{
    if (cstr) {
        // +1 是指为结束符'\0'预留空间
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    }
    else {
        // 未指定初值
        m_data = new char[1];
        *m_data = '\0';
    }
}

// copy ctor 拷贝构造函数 深拷贝
inline String::String(const String& str)
{
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

// copy assignment operator 拷贝赋值函数
inline String& String::operator = (const String& str)
{
    // 检测自我赋值(self assignment)
    if (this == &str) {
        return *this;
    }
    
    delete[] m_data;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}

inline String::~String()
{
    delete[] m_data;
}

ostream& operator << (ostream& os, const String& str) 
{
    os << str.get_c_str();
    return os;
}

#endif