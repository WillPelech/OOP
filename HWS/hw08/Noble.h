//
// Created by Will Pelech on 4/12/24.
//

#ifndef HW08_NOBLE_H
#define HW08_NOBLE_H
#include <iostream>
#include <vector>
#include <string>


namespace WarriorCraft {

    class Protector;

    class Noble{
        friend std::ostream& operator <<
        (std::ostream& os, const Noble& noble);
    public:
        //constructor
        Noble(const std::string& name);
        //public getters
        const std::string& get_name() const;
        virtual double get_strength() const = 0;
        bool get_alive() const;
        //public battle function
        void battle(Noble& other_noble);

    protected:

        //method called in the output operator needs to be overriden
        //by every subclass
        virtual std::ostream& display(std::ostream& os) const=0;
        //protected setters
        bool set_alive(bool al);
        virtual void set_strength(double multiplier)=0;
        //auxillary ratio method
        double ratio(double weaker, double stronger);
        //protected battle_cry method every Lord uses when defending
        void virtual battle_cry() const=0;

    private:
        //kill method
        virtual void kill()=0;

        std::string name;
        bool alive;
    };


    class Lord : public Noble{
    public:
        //constructor for Lord
        Lord(const std::string& name);
        //hire and fire methods
        bool hires(Protector& protector);
        bool fires(Protector& protector);
        //overridden get strength method
        double get_strength() const override;
        //displays the warrior defending battle cry
        void virtual battle_cry() const;
        //removes a protector from the warriors army
        bool remove_protector(const Protector *protector);
    protected:
        //method called by output operator
        std::ostream& display(std::ostream& os)  const override;
        //protected setter
        void set_strength(double multiplier) override;

    private:
        //sets alive to false and sets the army strength to zero
        void kill() override;
        //finds the index of a protector in the Lord's army
        size_t find_protector(const Protector *protector);
        //private field
        std::vector<Protector*> army;
    };



    class PersonWithStrengthToFight: public Noble{
    public:
        //constructor for PersonWithStrength to fight
        PersonWithStrengthToFight(const std::string& name, double strength);
        //public getter
        double get_strength() const override;
        //battle cry method
        void virtual battle_cry() const;
    protected:
        // called in the output operator
        std::ostream& display(std::ostream& os) const override;
        //sets strength of a ratio
        void set_strength(double multiplier) override;
    private:
        //sets strength to zero and alive to false
        void kill() override;
        double strength;
    };
}
#endif //HW08_NOBLE_H
