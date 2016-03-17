#include <iostream>
#include <functional>

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
    void setCallback(LuaRef c){mCallback = c;}
    LuaRef callback(){return mCallback;}
    ~Foo(){cout << "Foo dtor " << mVal << endl;}
private:
    unsigned long long mVal;
    LuaRef mCallback;
};

void smartLuaPrint(LuaRef r, bool end = true)
{
    switch(r.type())
    {
        case LuaTypeID::TABLE:
        {
            cout << "{";
            bool nfirst = false;
            for(auto it = r.begin(); it != r.end(); ++it)
            {
                if(nfirst) cout << ", ";
                smartLuaPrint(it.value(),false);
                nfirst = true;
            }
            cout << "}";
            break;
        }
        default:
            cout << r.toValue<string>();
        break;
    }
    if(end) cout << endl;
}

int main()
{
    using namespace std::placeholders;
    LuaContext l;
    LuaBinding(l).beginClass<Foo>("Foo")
            .addConstructor(LUA_SP(SharedFoo),LUA_ARGS(_opt<int>))
            .addProperty("val",&Foo::val,&Foo::set_val)
            .addProperty("fun", &Foo::callback,&Foo::setCallback)
            .addFunction("display", &Foo::display)
            .addFunction("plus",&Foo::plus)
            .endClass()
            .addFunction("print",std::function<void(LuaRef)>(std::bind(smartLuaPrint,_1,true)));

    l.doFile("printvscout.lua");
    l.doString("j = \"string bloubi\" \n i = {4,2,{6,7},j} \n print(i)");

    return 0;
}

