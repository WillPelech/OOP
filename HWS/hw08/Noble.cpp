//
// Created by Will Pelech on 4/12/24.
//
#include "Noble.h"
#include "Protector.h"

using namespace std;
namespace WarriorCraft {
//noble methods

//constructors for Noble and derived classes
    Noble::Noble(const string &name) : name(name), alive(true) {}

    Lord::Lord(const string &name) : Noble(name) {}

    PersonWithStrengthToFight::PersonWithStrengthToFight
            (const std::string &name, double strength)
            : Noble(name), strength(strength) {

    }

//getters and setters
// get_strength methods
    bool Noble::get_alive() const {
        return alive;
    }

    bool Noble::set_alive(bool al) {
        alive = al;
    }

    const string &Noble::get_name() const {
        return name;
    }

    double Lord::get_strength() const {
        double total_strength = 0;
        for (const Protector *protector: army) {
            total_strength += protector->get_strength();
        }
        return total_strength;
    }

    void Lord::set_strength(double multiplier) {
        //warrior off the ratio
        for (Protector *protector: army) {//goes through and changes evry
            //warrior off the ratio
            double new_strength = (protector->get_strength() * (multiplier));
            protector->set_strength(new_strength);
        }
    }

    double PersonWithStrengthToFight::get_strength() const {
        return strength;
    }

    void PersonWithStrengthToFight::set_strength(double multiplier) {
        strength = strength * multiplier;
    }

    bool Lord::hires(Protector &protector) {
        if (!get_alive()) {
            cout << get_name() <<
                 " failed to hire " << protector.get_name() << endl;
            return false;
        }//checks the warrior is alive
        if (protector.get_hired()) {//makes sure the warrior isn't dead
            cout << get_name() <<
                 " failed to hire " << protector.get_name() << endl;
            return false;
        } else {

            army.push_back(&protector);//adds warrior to army
            protector.set_hiring(this);//sets noble ptr
            return true;
        }
    }


    //removes protector and keeps order
    bool Lord::remove_protector(const Protector *protector) {
        size_t war_ind = find_protector(protector);//finds index of protector
        if (war_ind != army.size()) {//makes sure it was found
            //shifts every protector forward and pop the last
            for (size_t index = war_ind + 1; index < army.size(); index++) {
                army[index - 1] = army[index];
            }
            army.pop_back();
            return true;
        }
        return false;
    }

    //finds the protector index in the army
    size_t Lord::find_protector(const Protector *protector) {
        for (size_t index = 0; index < army.size(); index++) {
            if (army[index] == protector) {
                return index;
            }
        }
        return army.size();
    }



    bool Lord::fires(Protector &protector) {
        if (!get_alive()) {//checks warrior is alive
            cout << "The Noble is dead and can't hire" << endl;
            return false;
        }
        //finds the index of the warrior
        size_t index = find_protector(&protector);
        if (index != army.size()) {//makes sure the warrior exists
            cout << army[index]->get_name() <<
                 ", you don't work for me anymore ! -- " <<
                 get_name() << "." << endl;
        }
        //removes it from the army
        bool war_rem = remove_protector(&protector);
        if (war_rem) {
            protector.set_hiring(nullptr);//sets to null ptr
        }
        return war_rem;
    }



//kill methods
    void Lord::kill() {
        set_alive(false);//sets alive field to false
        for (Protector *protector: army) {
            protector->set_strength(0);// goes through and
            // sets strength to 0
        }
    }

    void PersonWithStrengthToFight::kill() {
        set_alive(false);//set alive false
        strength = 0;//strength 0
    }


    void Noble::battle(Noble &other_noble) {

        cout << get_name() << " battles " << other_noble.get_name() << endl;

        //strengths of nobles
        double noble1_strength = get_strength();
        double noble2_strength = other_noble.get_strength();
        //sees who is alive
        battle_cry();
        other_noble.battle_cry();
        //makes sure both are alive outputs if not
        if (!get_alive() && !other_noble.get_alive()) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
            return;
        } else if (!get_alive()) {
            cout << "He's dead, " << other_noble.get_name() << endl;
            return;
        } else if (!other_noble.get_alive()) {
            cout << "He's dead, " << get_name() << endl;
            //compares strengths
            return;
        }
        if (noble1_strength == noble2_strength) {
            kill();
            other_noble.kill();
            cout << "Mutual Annihilation " << get_name() << " and " <<
                 other_noble.get_name() << " die at each other's hands "
                 << endl;
            //kills weaker Noble
        } else if (noble1_strength > noble2_strength) {

            cout << get_name() << " defeats "
            << other_noble.get_name() << endl;
            double multiplier =
            ratio(noble2_strength, noble1_strength);
            other_noble.kill();
            set_strength(multiplier);

        } else if (noble1_strength < noble2_strength) {
            cout << other_noble.get_name()
            << " defeats " << get_name() << endl;
            double multiplier =
            ratio(noble1_strength, noble2_strength);
            kill();
            other_noble.set_strength(multiplier);
        }
    }



    double Noble::ratio(double weaker, double stronger) {
        if (stronger == 0) {
            return 1.0;
        }
        return 1 - (weaker / stronger);
    }


    ostream &operator<<(ostream &os, const Noble &noble) {
        noble.display(os);
        return os;
    }

//overridden display methods for output operator
    ostream &Lord::display(ostream &os) const {
        os << get_name() << " has an army of size:" << army.size();

        for (const Protector *protector: army) {
            os << endl << "\t" << protector->get_name() << " has strength "
               << protector->get_strength();
        }
        return os;
    }

    ostream &PersonWithStrengthToFight::display(ostream &os) const {
        os << get_name() << " has strength:" << strength;
        return os;
    }

//batlle cry methods when a warrior enters the battle
    void Lord::battle_cry() const {//displays all warriors
        if (get_alive()) {
            for (const Protector *protector: army) {
                protector->display();
            }
        }
    }

    void PersonWithStrengthToFight::battle_cry() const {
        //checks if alive and so makes ugh sound
        if (get_alive()) {
            cout << "Ugh!" << endl;
        }
    }
}
