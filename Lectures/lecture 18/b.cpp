
#include <iostream>
using namespace std;


class Base{

public:
    Base(){
        cerr<<"Base";
    }
    Base(const Base& rhs){
        cerr<<"Base p";
    }
    ~Base(){
        cerr<<"~base";
    }
};

class Derived:public Base{
    Derived():Base(){ cerr<<"derived()";}

    ~Derived(){
        cerr<<"~Derived()";
    }
};