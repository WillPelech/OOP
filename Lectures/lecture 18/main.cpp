#include <iostream>
using namespace std;

class Base{
    friend ostream& operator<<(ostream& os, const Base& base){
        return os << "x: " << base.x;
    }
public :
Base(int x) :x(x){}
//two exes one to refer to field on to parameter
protected://mark this method as protected
void setX(int x){
        //will check the scope first
        this->x= x;
    }

private:
//protected://frowned upon
int x;
};
//a derived class cant call another protected function of another derived function including an instance of the base class
//only for on type
//only access protected in Cat
class Derived : public Base{
public:
    Derived(int x) :Base(x) {}
    void derivedSettingX(){
        setX(42);// compilation error
    }
};
int main(){
    Derived d(7);
    cout << d << endl;
}

// when we analyze a function at comp time

//public interface- whether or not purr is in the pub interface of pet

// we could make cat have the displayCat

class Shape{
public:
    Shape(){

    }
};
//doesnt if

void drawAShape(Shape& someShape){
    someShape.draw();
}
//virtual void draw() = 0;-- abstract method.