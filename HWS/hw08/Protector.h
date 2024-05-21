//
// Created by Will Pelech on 4/12/24.
//

#ifndef HW08_PROTECTOR_H
#define HW08_PROTECTOR_H
#include <iostream>
#include <string>

namespace WarriorCraft {

    class Lord;

    class Protector{
    public:
        //constructor
        Protector(const std::string& name, double num);
        //getters and setters
        const std::string& get_name() const;

        double get_strength() const;

        bool get_hired() const;

        virtual void set_strength(double new_s);

        void set_hiring(Lord* ldptr);

        const std::string& lord_name() const;//this function gets lords name
        //runaway method
        bool runaway();

        virtual void display() const=0;//I think that every subclass should
//implement a display function
    private:
        //private data members
        std::string name;
        Lord* lptr;
        double strength;
    };


    class Warrior:public Protector{
    public:
        Warrior(const std::string& name, double num);
    protected:
        void display() const override;
    };

    class Archer: public Warrior{
    public:
        Archer(const std::string& name, double num);
    protected:
        void display() const override;
    };

    class Swordsman: public Warrior{
    public:
        Swordsman(const std::string& name, double strength);
        void display() const override;
    };

    class Wizard: public Protector{
    public:
        Wizard(const std::string& name, double strength);
        void display() const override;
    };


}
#endif //HW08_PROTECTOR_H
