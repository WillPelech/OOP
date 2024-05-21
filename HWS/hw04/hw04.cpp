
/*
  hw04_start.cpp
  Association: Noble - Warrior
  Will Pelech this will battle warriors and Nobles
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.

//This is the warrior class
class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
    Warrior(const string& name,double strength):name(name),
    strength(strength), hired(false){}
    //getters and setters
    double get_strength() const{ return strength;}
    void set_strength(double new_strength){strength=new_strength;}
    const string& get_name() const{return name;};
    bool get_hiring() const{return hired;}
    //hire and fire methods which change hiring status
    void fire(){hired=false;}
    void hire(){hired = true;}

private:
    double strength;
    string name;
    bool hired;
};
//this is the noble class
class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble);

public:

    Noble(const string& name):name(name),army(),alive(true){}
    //this method will attempt to hire a warrior and returns a boolean
    //if the task was completed or not
    bool hire(Warrior& warrior){
        if(warrior.get_hiring()||!alive) {
            cout<<name<<" failed to hire "<<warrior.get_name()<<endl;
            return false;
        }
        army.push_back(&warrior);
        warrior.hire();
        return true;
    }
    //this methods attempts to fire a warrior return type:bool
    bool fire(Warrior& warrior) {
        if (alive && warrior.get_hiring()) {
            size_t index;
            //checks to see if there is a match warrior by comparing adresses
            for (index = 0; index < army.size(); index++) {
                if (army[index] == &warrior) {
                    warrior.fire();
                    cout << warrior.get_name() << ", you don't work for me "
                         << "any more! -- " << name << "."<<endl;
                    //this loop will remove the warrior from vector and
                    //maintains order by shifting every warrior forward
                    for (size_t i = index + 1; i < army.size(); i++) {
                        army[i - 1] = army[i];
                    }
                    //gets rid of repeated last warrior
                    army.pop_back();
                    return true;
                }
            }
            //condition to check if the warrior was not found
            if (index == army.size()) {
                cout << name << " failed to fire " << warrior.get_name() << endl;
                return false;
            }
        }

        return false;
    }
    //this will battle two warriors and makes a
    //call to the modify strength method
    void battle(Noble& other_noble){
        cout << name << " battles " << other_noble.name<<endl;
        //conditions to check the status of both nobles before fighting
        if(!alive && !other_noble.alive){
            cout<<"Oh, NO! They are both dead! Yuck!"<<endl;

        }else if(!alive){
            cout<<"He's dead, " << other_noble.name;
        }else if (!other_noble.alive){
            cout << "He's dead, " << name <<endl;
            //only occurs if both are alive
        }else{
            if(get_strength() == other_noble.get_strength()){
                kill();
                other_noble.kill();

                cout <<"Mutual Annihilation: "<<name<< " and "
                     <<other_noble.name <<" die at each other's hands" <<endl;

            }else if(get_strength() > other_noble.get_strength()){
                //modifies the strength of the stronger warrior
                modify_strength
                (get_strength(),other_noble.get_strength());
                cout << name << " defeats " << other_noble.name << endl;
                other_noble.kill();

            }else{
                //modifies the strength of the stronger warrior
                other_noble.modify_strength
                (other_noble.get_strength(),get_strength());
                cout << other_noble.name << " defeats " << name <<endl;
                kill();
            }
        }
    };

private:

    double get_strength() const{
        //returns the total if alive returns 0 if dead
        if (alive) {
            double total_strength = 0;
            //ranged for through the army and adds the strengths up
            for (const Warrior* warrior: army) {
                total_strength += warrior -> get_strength();
            }
            return total_strength;
        }
        return 0.0;
    }
    //goes through the army and sets the strengths to 0 of the warriors
    void kill(){
        alive=false;
        for(size_t i = 0; i < army.size(); i++) {
            army[i]->set_strength(0);
        }

    }
    //this will modify the strength of an army by calculating the ratio
    // if the warrior is dead it will do nothing
    void modify_strength(double strong_army, double weak_army){
        if(!alive){return;}
        double ratio = 1- weak_army/strong_army;
        //modifies every warrior in army using ranged for loop of warrior
        //ptrs
        for (Warrior* warrior:army){
            warrior -> set_strength(warrior->get_strength() * ratio);
        }
    };

    vector<Warrior*> army;
    string name;
    bool alive;
};





int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);

    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

}
//output operator for Warrior
ostream& operator<<(ostream& os, const Warrior& warrior){
    os << "  " <<  warrior.name << ": " <<warrior.strength;
    return os;
}
//output operator for Noble makes call to warrior output operator
ostream& operator<<(ostream& os, const Noble& noble){
    os<<noble.name<< " has am army of " << noble.army.size();
    for(size_t index=0; index < noble.army.size();index++){
        os<<endl<<*noble.army[index];
    }

    return os;
}