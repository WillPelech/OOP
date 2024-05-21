//
// Created by Will Pelech on 3/25/24.
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Noble;
// warrior class
class Warrior{
    //output operator
    friend ostream& operator << (ostream& os , const Warrior& warrior);

public:
    //constructor
    Warrior(const string& name, double strength);

    //getters and setters
    void set_hiring(Noble* nbp);

    const string& get_name() const;

    double get_strength() const;

    void set_strength(double val);
    //Sets noble to none and removes warrior from noble army
    bool runaway();
    //returns if the warrior is hire
    bool isHired() const;

private:
    double strength;
    string name;
    Noble* noble;
};

class Noble{
    //output operator
    friend ostream& operator << (ostream& os, const Noble& noble);
public:
    //constructor
    Noble(const string& name);
    //kills a warrior
    void kill();

    //this method hires a warrior if possible
    bool hire(Warrior& warrior);

    //the fire method passed by reference doesnt copy the warrior object
    bool fire(Warrior& warrior);

    //gets name
    const string& get_name() const{return name;}

    //battles two Nobles
    void battle(Noble& other_noble);
    //removes a warrior from the army
    bool remove_warrior(const Warrior*);
private:
    //private methods
    //calculates a ratio between weaker and stronger army
    double ratio(double weaker, double stronger);

    //sets strength of an army using the ratio
    void set_strength(double ratio);

    //gets the strength
    double get_strength() const;
    //will find the index of a warrior within army
    size_t find_warrior(const Warrior* warrior);


    //private fields
    bool alive;
    vector<Warrior*> army;
    string name;
};


int main(){

        Noble art("King Arthur");
        Noble lance("Lancelot du Lac");
        Noble jim("Jim");
        Noble linus("Linus Torvalds");
        Noble billie("Bill Gates");

        Warrior cheetah("Tarzan", 4);
        Warrior sky("Leia", 6);
        Warrior wizard("Merlin", 9);
        Warrior jaffa("Teal'c", 9);
        Warrior theGovernator("Conan", 12);
        Warrior nimoy("Spock", 15);
        Warrior lawless("Xena", 20);
        Warrior mrGreen("Hulk", 8);
        Warrior dylan("Hercules", 3);

        jim.hire(nimoy);
        lance.hire(theGovernator);
        art.hire(jaffa);
        art.hire(cheetah);
        art.hire(wizard);
        art.hire(sky);
        lance.hire(dylan);
        linus.hire(lawless);
        billie.hire(mrGreen);
        art.hire(nimoy);

        cout << "================ Initial Status ===============" << endl;
        cout << art << endl
             << lance << endl
             << jim << endl
             << linus << endl
             << billie << endl;

        cout << "===============================================\n\n";

        art.fire(cheetah);
        wizard.runaway();
        cout << endl << art << endl;

        art.battle(lance);
        jim.battle(lance);
        linus.battle(billie);
        billie.battle(lance);

        cout << "\n================ Final Status ===============" << endl;
        cout << art << endl
             << lance << endl
             << jim << endl
             << linus << endl
             << billie << endl;

        // Tarzan and Merlin should be unemployed
        cout << "Tarzan's Hire Status: " << boolalpha
             << cheetah.isHired() << endl;
        cout << "Merlin's Hire Status: " << boolalpha
             << wizard.isHired() << endl;
        cout << "===============================================\n\n";
    }


//output operator for warrior
ostream& operator << (ostream& os , const Warrior& warrior){
    os << "\t\t" << warrior.name << ": " << warrior.strength;
    return os;
}

//output operator for noble
ostream& operator << (ostream& os, const Noble& noble){
    os << noble.name << " has an army of " << noble.army.size();
    for(Warrior* warrior: noble.army){
        os << endl << *warrior;
    }
    return os;
}
//Warrior

//constructor for the warrior class
Warrior::Warrior(const string& name, double strength) : strength(strength),
name(name),noble(nullptr){}

//sets the hiring status from a nullptr to a noble ptr
void Warrior::set_hiring(Noble* nbp) {
    noble=nbp;
}

//gets the name of a warrior
const string& Warrior::get_name() const {return name;}

//sets the strength of a warrior
void Warrior::set_strength(double val) {
    strength = val;
}
//gets the strength of a warrior
double Warrior::get_strength() const {return strength;}

//runaway method
bool Warrior::runaway(){

    if(noble != nullptr) {//checks that the Warrior can runaway
        cout <<name << " flees in terror, abandoning his lord, "
        <<noble->get_name()<< endl;
    }else{
        return false;//if nullptr return false
    }

    if(noble->remove_warrior(this)){//removes the warrior
        //and sets the nobleptr to noble
        noble = nullptr;
        return true;

    }
    return false;
}

bool Warrior::isHired() const{//returns warriors hiring status
    return noble;
}

//Public noble methods
//noble constructor
Noble::Noble(const string& name):name(name),alive(true),army(){}

//noble kill method
void Noble::kill(){
    alive=false;//sets alive field to false
    for(Warrior* warrior : army){
        warrior -> set_strength(0);// goes through and sets strength 0
    }
}
// hiring Noble method
bool Noble::hire(Warrior& warrior) {
    if (!alive) { return false; }//cant hire if noble is dead
    if (warrior.isHired()) {//checks the warrior isnt hired
            cout << name <<
            " failed to hire " << warrior.get_name() << endl;
            return false;
        } else {
            army.push_back(&warrior);
            warrior.set_hiring(this);
            return true;
        }
    }


bool Noble::fire(Warrior& warrior){
    if(!alive){
        cout << "The Noble is dead and can't hire"<<endl;
        return false;
    }

    size_t index = find_warrior(&warrior);
    if(index != army.size()){
        cout << army[index] -> get_name() <<
            ", you don't work for me anymore! -- " <<
            name << "." << endl;
    }

    bool war_rem = remove_warrior(&warrior);
    if(war_rem){
        warrior.set_hiring(nullptr);
    }
    return war_rem;
}

void Noble::battle(Noble& other_noble){

    cout << name << " battles " << other_noble.name << endl;

    //strengths of nobles
    double noble1_strength = get_strength();
    double noble2_strength = other_noble.get_strength();

    //makes sure both are alive outputs if not
    if(!alive && !other_noble.alive) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }else if(!alive){
        cout<<"He's dead, "<<other_noble.name<<endl;}
    else if(!other_noble.alive){
        cout<<"He's dead, "<<name<<endl;
        //compares strengths
    }else if (noble1_strength==noble2_strength){
        kill();
        other_noble.kill();
        cout << "Mutual Annihilation " << name <<" and " <<
             other_noble.get_name() << " die at each other's hands " << endl;
        //kills weaker Noble
    }else if(noble1_strength>noble2_strength){

        cout<<name<<" defeats "<<other_noble.name<<endl;
        double multiplier = ratio(noble2_strength,noble1_strength);
        other_noble.kill();
        set_strength(multiplier);

    }else if(noble1_strength<noble2_strength){
        cout<<other_noble.name<<" defeats "<<name<<endl;
        double multiplier = ratio(noble1_strength,noble2_strength);
        kill();
        other_noble.set_strength(multiplier);

    }

}
//finds a warrior index
size_t Noble::find_warrior(const Warrior* warrior){
    for(size_t index = 0; index < army.size(); index++){
        if(army[index]==warrior){//check if the ptrs pt to the same
            //place
            return index;
        }
    }
    return army.size();//return size if not found
}

//private Noble methods
//auxillary metho
double Noble::ratio(double weaker, double stronger){
    if(stronger == 0){
        return 1.0;
    }
    return 1 - (weaker / stronger);
}
//set strength method
void Noble::set_strength(double ratio){
    for (Warrior* warrior : army) {//goes through and changes evry
        //warrior off the ratio
        double new_strength = (warrior->get_strength() * (ratio));
        warrior->set_strength(new_strength);
    }
}
//get strength
double Noble::get_strength() const{
    double total_strength = 0;
    for(const Warrior* warrior:army){//goes through and gathers strengths
        total_strength += warrior->get_strength();
    }
    return total_strength;
}
//remove warrior (maintains order)
bool Noble::remove_warrior(const Warrior* warrior){
    size_t war_ind = find_warrior(warrior);//finds index of warrior
    if(war_ind != army.size()){//checks warrior exists
        //loops through moves every ptr forward and pops from back
        for(size_t index = war_ind+1; index<army.size(); index++){
            army[index-1]=army[index];
        }
        army.pop_back();
        return true;
    }
    return false;
}