//
// Created by Will Pelech on 3/25/24.
//

#ifndef HW07_WARRIOR_H
#define HW07_WARRIOR_H
#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Noble;
    class Warrior {
        //output operator
        friend std::ostream &operator<<(std::ostream &os,
                const Warrior &warrior);

    public:
        //constructor
        Warrior(const std::string &name, double strength);

        //getters and setters
        void set_hiring(Noble *nbp);

        const std::string &get_name() const;

        double get_strength() const;

        void set_strength(double val);

        bool runaway();

        bool isHired() const;

    private:
        double strength;
        std::string name;
        Noble *noble;
    };
}
#endif //HW07_WARRIOR_H


