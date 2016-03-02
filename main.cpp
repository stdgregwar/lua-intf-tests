#include <iostream>

#include "LuaIntf.h"


using namespace std;
using namespace LuaIntf;

namespace LuaIntf
{
    LUA_USING_SHARED_PTR_TYPE(std::shared_ptr)
}

class Foo;

typedef shared_ptr<Foo> SharedFoo;

class Foo
{
public:
    double x;
    Foo(int val = 0) : mVal(val){}
    void display(){cout << mVal << endl;}
    const unsigned long long& val(){return mVal;}
    void set_val(const  unsigned long long& val){mVal = val;}
    SharedFoo plus(){return SharedFoo(new Foo(mVal+1));}
    ~Foo(){cout << "Foo dtor " << mVal << endl;}
private:
    unsigned long long mVal;
};

int main()
{
    LuaContext l;
    LuaBinding(l).beginClass<Foo>("Foo")
            .addConstructor(LUA_SP(SharedFoo),LUA_ARGS(_opt<int>))
            .addProperty("val",&Foo::val,&Foo::set_val)
            .addFunction("display", &Foo::display)
            .addFunction("plus",&Foo::plus)
            .endClass();

    l.doString("val = Foo(69) \n val:display()");
    l.doString("val2 = val:plus()");

    SharedFoo sptr;
    {
        cout << "In" << endl;
        SharedFoo fptr = l.getGlobal<SharedFoo>("val2");
        l.doString("val:display()");
        fptr->set_val(42);
        //sptr = fptr;
    }

    cout << "Out" << endl;

    l.doString("val2 = val1 \n val1 = nil");
    l.gc();
    l.doString("val2 = nil");
    l.gc();

    cout << "After GC" << endl;
    /*for(int i = 0 ; i < 100 ; i++)
    {
        //l.doFile("bench.lua");
        l.doString("f.val = 2*f.val \n f:display()");
    }*/


    //l.doFile("printvscout.lua");

    return 0;
}

