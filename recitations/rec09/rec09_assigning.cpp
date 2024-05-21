//
// Created by Will Pelech on 3/30/24.
//
#include <iostream>;
#include <vector>;
using namespace std;

class Base{
};

class Derived:public Base{
};
int main(){
    Base base;
    Derived der;
    Base* bases;
    Derived* deriveds;

//    bases=deriveds;//works
//    deriveds=bases;//doesnt
    //bases = &der;//works
    //deriveds = &base;//doesnt

}