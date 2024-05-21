//
// Created by Will Pelech on 3/27/24.
//
class Shape{//abstract class cannot make an instance
public:
    Shape(int x, int y):x(x),y(y){}
private:
    int x,y;
};
class Triangle{

};
// if you are inheriting an abstract mehtod and dont inherit it you are abstract and cant create an instance
//abstract classes need a constructor

//force the developer to write a draww

//overide makes you check your work
//final - cant override last time

//abstracts are really important like very

//pet peeve would not make it possible to have an abstract class


//class EqTri: public Triangle{
//
//};
//monkey wrench:common code such as drawing
//you put the method Shape::draw();

//one last thing:
//
//wrapper something that calls something else in base class
//using Base::foo;
class Base{
public:
    void foo(int n) const {
    }
};


//need to mark the display const

//stuck with the choice of making a function polymorphic
//you call methods


//overloaded functions

//compiler chooses most specific one



class Parent{};
class Child:public Parent{};
class Grandchild:public Child{};

void func(Parent& base { cout<<"func(Parent)\n"; }

