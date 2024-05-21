//
// Created by Will Pelech on 3/25/24.
//
#include <iostream>
#include <string>
#include "Warrior.h"
#include "Noble.h"

using namespace std;

namespace WarriorCraft{
    //warrior constructor
    Warrior::Warrior(const string &name, double strength) :
    strength(strength),name(name),noble(nullptr) {}

    //sets the hiring to a noble pointer
    void Warrior::set_hiring(Noble *nbp) {
        noble = nbp;
    }
    // gets the name
    const string& Warrior::get_name() const { return name; }
    //sets the strength of a warrior
    void Warrior::set_strength(double val) {
        strength = val;
    }
    //get strengths of a warrior
    double Warrior::get_strength() const { return strength; }
    //warriors runs away from noble
    bool Warrior::runaway() {
        if (noble != nullptr) {//makes sure the warrior has a noble
            cout << name << " flees in terror, abandoning his lord, "
                 << noble->get_name() << endl;
        }

        if (noble->remove_warrior(this)) {//removes the warrior
            noble = nullptr;
            return true;
        }
        return false;
    }
    //returns warriors hire status
    bool Warrior::isHired() const {
        return noble;
    }
    //warrior output operator
    ostream& operator << (ostream& os , const Warrior& warrior){
        os << "\t\t" << warrior.name << ": " << warrior.strength;
        return os;
    }

}