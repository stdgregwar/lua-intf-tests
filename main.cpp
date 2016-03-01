#include <iostream>

#include "LuaIntf.h"

using namespace std;
using namespace LuaIntf;

class Foo
{
public:
    Foo(int val = 0) : mVal(val){}
    void display(){cout << mVal << endl;}
    int val(){return mVal;}
    void set_val(int val){mVal = val;}
private:
    int mVal;
};

int main()
{
    LuaContext l;
    LuaBinding(l).beginClass<Foo>("Foo")
            .addConstructor(LUA_ARGS(_opt<int>))
            .addProperty("val",&Foo::val,&Foo::set_val)
            .addFunction("display", &Foo::display)
            .endClass();

    for(int i = 0 ; i < 50 ; i++)
    {
        l.doFile("bench.lua");
    }

    return 0;
}

