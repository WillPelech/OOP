//
// Created by Will Pelech on 3/25/24.
//
#include <iostream>
#include "Noble.h"
#include "Warrior.h"

using namespace std;

namespace WarriorCraft {
    //noble constructor
    Noble::Noble(const string &name) : name(name), alive(true), army() {}

    void Noble::kill() {
        alive = false;//sets the Noble to dead
        for (Warrior *warrior: army) {//changes every war str to 0
            warrior->set_strength(0);
        }
    }

    bool Noble::hire(Warrior &warrior) {
        if (!alive) { return false; }//checks the warrior is alive
        if (warrior.isHired()) {//makes sure the warrior isn't dead
            cout << name <<
                 " failed to hire " << warrior.get_name() << endl;
            return false;
        } else {
            army.push_back(&warrior);//adds warrior to army
            warrior.set_hiring(this);//sets noble ptr
            return true;
        }
    }
    //fire method
    bool Noble::fire(Warrior &warrior) {
        if (!alive) {//checks warrior is alive
            cout << "The Noble is dead and can't hire" << endl;
            return false;
        }
        //finds the index of the warrior
        size_t index = find_warrior(&warrior);
        if (index != army.size()) {//makes sure the warrior exists
            cout << army[index]->get_name() <<
                 ", you don't work for me anymore! -- " <<
                 name << "." << endl;
        }
        //removes it from the army
        bool war_rem = remove_warrior(&warrior);
        if (war_rem) {
            warrior.set_hiring(nullptr);//sets to null ptr
        }
        return war_rem;
    }

    void Noble::battle(Noble &other_noble) {

        cout << name << " battles " << other_noble.name << endl;

        //strengths of nobles
        double noble1_strength = get_strength();
        double noble2_strength = other_noble.get_strength();

        //makes sure both are alive outputs if not
        if (!alive && !other_noble.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!alive) {
            cout << "He's dead, " << other_noble.name << endl;
        } else if (!other_noble.alive) {
            cout << "He's dead, " << name << endl;
            //compares strengths
        } else if (noble1_strength == noble2_strength) {
            kill();
            other_noble.kill();
            cout << "Mutual Annihilation " << name << " and " <<
                 other_noble.get_name() << " die at each other's hands "
                 << endl;
            //kills weaker Noble
        } else if (noble1_strength > noble2_strength) {

            cout << name << " defeats " << other_noble.name << endl;
            double multiplier = ratio(noble2_strength, noble1_strength);
            other_noble.kill();
            set_strength(multiplier);

        } else if (noble1_strength < noble2_strength) {
            cout << other_noble.name << " defeats " << name << endl;
            double multiplier = ratio(noble1_strength, noble2_strength);
            kill();
            other_noble.set_strength(multiplier);

        }

    }
    //find method (returns the index of where a warrior is in an army)
    size_t Noble::find_warrior(const Warrior *warrior) {
        for (size_t index = 0; index < army.size(); index++) {
            if (army[index] == warrior) {
                return index;
            }
        }
        return army.size();
    }

//private Noble methods
    //ratio method
    double Noble::ratio(double weaker, double stronger) {
        if (stronger == 0) {
            return 1.0;
        }
        return 1 - (weaker / stronger);
    }
    //sets strength of Noble
    void Noble::set_strength(double ratio) {//sets strength
        for (Warrior *warrior: army) {
            double new_strength = (warrior->get_strength() * (ratio));
            warrior->set_strength(new_strength);
        }
    }
    //gets the strength
    double Noble::get_strength() const {
        double total_strength = 0;
        for (const Warrior *warrior: army) {
            total_strength += warrior->get_strength();
        }
        return total_strength;
    }
    //removes a warrior from the army
    bool Noble::remove_warrior(const Warrior *warrior) {
        size_t war_ind = find_warrior(warrior);
        if (war_ind != army.size()) {
            for (size_t index = war_ind + 1; index < army.size(); index++) {
                army[index - 1] = army[index];
            }
            army.pop_back();
            return true;
        }
        return false;
    }
    // output operator noble
    ostream& operator << (ostream& os, const Noble& noble){
        os << noble.name << " has an army of " << noble.army.size();
        for(Warrior* warrior: noble.army){
            os << endl << *warrior;
        }
        return os;
    }
}