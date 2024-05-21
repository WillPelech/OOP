//
// Created by Will Pelech on 3/25/24.
//

#ifndef HW07_NOBLE_H
#define HW07_NOBLE_H
#include <iostream>
#include <vector>
#include <string>


namespace WarriorCraft {
    class Warrior;
    class Noble {
        //output operator
        friend std::ostream &operator<<(std::ostream &os, const Noble &noble);

    public:
        //constructor
        Noble(const std::string &name);

        //kills a warrior
        void kill();

        //this method hires a warrior if possible
        bool hire(Warrior &warrior);

        //the fire method passed by reference doesnt copy the warrior object
        bool fire(Warrior &warrior);

        //gets name
        const std::string &get_name() const { return name; }

        //battles two Nobles
        void battle(Noble &other_noble);


        bool remove_warrior(const Warrior *);

    private:
        //private methods
        //calculates a ratio between weaker and stronger army
        double ratio(double weaker, double stronger);

        //sets strength of an army using the ratio
        void set_strength(double ratio);

        //gets the strength of the warrior
        double get_strength() const;

        //returns the index of where the warrior
        size_t find_warrior(const Warrior *warrior);


        //private fields
        bool alive;
        std::vector<Warrior *> army;
        std::string name;
    };
}
#endif //HW07_NOBLE_H
