#include <iostream>

#include "LuaIntf.h"

using namespace std;
using namespace LuaIntf;

class Foo
{
public:
    double x;
    Foo(int val = 0) : mVal(val){}
    void display(){cout << mVal << endl;}
    const unsigned long long& val(){return mVal;}
    void set_val(const  unsigned long long& val){mVal = val;}
private:
    unsigned long long mVal;
};

int main()
{
    LuaContext l;
    LuaBinding(l).beginClass<Foo>("Foo")
            .addConstructor(LUA_ARGS(_opt<int>))
            .addProperty("val",&Foo::val,&Foo::set_val)
            .addFunction("display", &Foo::display)
            .endClass();

    l.doString("f = Foo() \n f.val = 1\n print(type(f))");
    /*for(int i = 0 ; i < 100 ; i++)
    {
        //l.doFile("bench.lua");
        l.doString("f.val = 2*f.val \n f:display()");
    }*/


    //l.doFile("printvscout.lua");

    return 0;
}

