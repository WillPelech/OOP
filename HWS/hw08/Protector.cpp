//
// Created by Will Pelech on 4/12/24.
//
//constructors
#include "Protector.h"
#include "Noble.h"
using namespace std;
namespace WarriorCraft {
    //constructors
    Protector::Protector(const string& name, double num):
            name(name),strength(num),lptr(nullptr){}
    Warrior::Warrior(const string& name, double num):Protector(name, num){}
    Archer::Archer(const string& name, double num): Warrior(name,num){}
    Swordsman::Swordsman(const string& name, double strength):
    Warrior(name,strength){}
    Wizard::Wizard(const string& name, double strength):
    Protector(name,strength){}

//protector getter and setter methods
//gets name
    const string& Protector::get_name() const{
        return name;
    }
//sets hiring
    void Protector::set_hiring(Lord *ldptr) {
        lptr = ldptr;
    }
//sets strength of a protector
    void Protector::set_strength(double new_s) {
        strength=new_s;
    }
//gets strength of a protector
    double Protector::get_strength() const {
        return strength;
    }

//gets the hiring status of a protector
    bool Protector::get_hired() const{
        return lptr;
    }
//gets the name of the warrior that the protector has
//this method can only be called when the warrior has a lord
    const string& Protector::lord_name() const{
        return lptr->get_name();
    }

//runaway method
    bool Protector::runaway(){
        if (lptr != nullptr) {//makes sure the warrior has a noble
            cout << name << " flees in terror, abandoning his lord, "
                 << lptr->get_name() << endl;
        }

        if (lptr->remove_protector(this)) {//removes the warrior
            lptr = nullptr;
            return true;
        }
        return false;
    }

//display methods

//shared text that all warriors say
    void Warrior::display() const {
        cout<<get_name() << " says: Take that in the "
                            "name of my lord, "<< lord_name()<<endl;
    }
//arcber battle display
    void Archer::display() const {
        cout << "TWANG! ";
        Warrior::display();

    }
//wizard battle display
    void  Wizard::display() const {
        cout<< "POOF"<<endl;

    }
//swordsmen battle display
    void Swordsman::display() const {
        cout<< "CLANG! ";
        Warrior::display();
    }
}