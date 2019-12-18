#include "SmartPtr.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

namespace Noah
{
    class A
    {
    public: 
        A()
        {
            cout << "Create A\n";
        }
        ~A()
        {
            cout << "Destroy A\n";
        }
        A(const A&)
        {
            cout << "Copy A\n";
        } 
        A(A&&)
        {
            cout << "Move A\n";
        }
    }; 
    A getA_unnamed()
    {
        A a;
        return a;
    }
    void main() noexcept
    { 
        A a = getA_unnamed();

        cout << "Before Exit Main()" << endl;
    }
}

class MyString : public string
{
public:
    MyString(const char* p) noexcept
        : string(p)
    {
        cout << "MyString(const char* p)" << endl;
    }

    ~MyString()
    {
        cout << "~MyString()" << endl;
    }

    MyString& operator=(const char* p) noexcept
    {
        cout << "MyString& operator=(const char* p)" << endl;
    }

    MyString(const MyString& rhs) noexcept
        : string(rhs)
    {
        cout << "MyString(const MyString& rhs)" << endl;
    }

    MyString(MyString&& rhs) noexcept
        : string(std::forward<MyString>(rhs))
    {
        cout << "MyString(MyString&& rhs)" << endl;
    }

    MyString& operator=(const MyString& rhs) noexcept
    {
        string::operator =(rhs);
        cout << "MyString& operator=(const MyString& rhs)" << endl;
        return *this;
    }

    MyString& operator=(MyString&& rhs) noexcept
    {
        string::operator =(std::forward<MyString>(rhs));
        cout << "MyString& operator=(MyString&& rhs)" << endl;
        return *this;
    }
};

int main()
{
    //Noah::main();
    MyString a = "abc";
    MyString b = a;
    return 0;
}