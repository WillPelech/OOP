//Created by Will Pelech
//This code battles warriors and Nobles
// the nobles and warriors are created on the heap
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// warrior class
class Warrior{
    //output operator
    friend ostream& operator << (ostream& os , const Warrior& warrior);
public:
    //constructor
    Warrior(const string& name, double strength) : strength(strength),
    name(name), hired(false){}
    //getters and setters
    bool get_hiring() const {return hired;}
    void set_hiring(bool hiring) {hired=hiring;}
    const string& get_name() const {return name;}
    double get_strength() const {return strength;}
    void set_strength(double val) {
        strength = val;
    }

private:
    double strength;
    string name;
    bool hired;
};

class Noble{
    //output operator
    friend ostream& operator << (ostream& os, const Noble& noble);
public:
    //constructor
    Noble(const string& name):name(name),alive(true),army(){}
    //kills a warrior
    void kill(){
        alive=false;
        for(Warrior* warrior : army){
            warrior -> set_strength(0);
        }
    }

    //this method hires a warrior if possible
    bool hire(Warrior& warrior){
        if(!alive){ return false;}
        if(warrior.get_hiring()){
            return false;
        }else{
            army.push_back(&warrior);
            warrior.set_hiring(true);
            return true;
        }
    };

    //the fire method passed by reference doesnt copy the warrior object
    bool fire(Warrior& warrior){

        if(!alive){
            cout << "The Noble is dead and can't hire";
            return false;
        }

        bool warrior_fired = false;
        for(size_t index = 0; index < army.size();index++){
            //if the warrior is in the warrior
            if(army[index] == &warrior) {
                cout << army[index] -> get_name() <<
                ", you don't work for me anymore! -- " <<
                name << "." << endl;
                army[index] -> set_hiring(false);
                warrior_fired = true;
            }if(warrior_fired){
                army[index-1] = army[index];
            }

        }
        if(warrior_fired){
            army.pop_back();
        }
        return warrior_fired;
    };

    //gets name
    const string& get_name() const{return name;}
    //battles two Nobles
    void battle(Noble& other_noble){

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
private:
    //private methods
    //calculates a ratio between weaker and stronger army
    double ratio(double weaker, double stronger){
        if(stronger == 0){
            return 1.0;
        }
        return 1 - (weaker / stronger);
    }
    //sets strength of an army using the ratio
    void set_strength(double ratio){
        for (Warrior* warrior : army) {
            double new_strength = (warrior->get_strength() * (ratio));
            warrior->set_strength(new_strength);
        }
    }
    //gets the strength
    double get_strength() const{
        double total_strength = 0;
        for(const Warrior* warrior:army){
            total_strength += warrior->get_strength();
        }
        return total_strength;
    }
    //private fields
    bool alive;
    vector<Warrior*> army;
    string name;
};

//function prototypes
void clear(vector<Warrior*>& warriors, vector<Noble*>& nobles);
Noble* noble_finder(const string& name, const vector<Noble*>& nobles);
Warrior* warrior_finder (const string& name, const vector<Warrior*>& warriors);
void status( const vector<Noble*>& nobles, const vector<Warrior*>& warriors);

int main(){
    vector<Warrior*> warriors;
    vector<Noble*> nobles;

    //file checking
    ifstream file("nobleWarriors.txt");
    if (!file){
        cerr << "The file failed to open";
        exit(1);
    }

    //variables to help read the file
    string first_word;
    string second_word;
    double input_strength;
    Noble* noble_ptr;
    Warrior* warrior_ptr;
    bool checker;

    //while loop which will read through the file line by line
    while(file >> first_word){
        //creates a new Noble on the heap if possible
        //calls checker function
        if(first_word == "Noble"){
            file >> second_word;
//            checker = noble_checker(second_word,nobles);

            if(!noble_finder(second_word,nobles)) {
                noble_ptr = new Noble(second_word);
                nobles.push_back(noble_ptr);
            }
            //creates a new warrior on the heap if possible
        }else if(first_word == "Warrior"){
            file >> second_word >> input_strength;
            if (!warrior_finder(second_word,warriors)) {
                warrior_ptr = new Warrior(second_word, input_strength);
                warriors.push_back(warrior_ptr);
            }else{
                cout << second_word << " already exists" << endl;

            }

            //hires a warrior if possible uses finder methods
        }else if(first_word == "Hire"){
                file >> first_word >> second_word;
                //checks to see that both warriors exist
                if (noble_finder(first_word, nobles)
                && warrior_finder(second_word, warriors)) {
                    Noble* noble_ptr = noble_finder(first_word, nobles);
                    Warrior* warrior_ptr = warrior_finder(second_word, warriors);
                    if (!noble_ptr->hire(*warrior_ptr)) {
                        cout << noble_ptr->get_name() <<
                        " failed to hire " << warrior_ptr->get_name() << endl;
                    }
                    //case when the warrior could not be found
                }else if(!warrior_finder(second_word, warriors)){
                    cout << "Attempting to hire using unknown warrior: "
                    << second_word << endl;
                    //case when the noble does not exist
                }else if(!noble_finder(first_word,nobles)){
                    cout << "Attempting to hire without a noble:"
                    << first_word << endl;
                }
                //This is the fire method

        }else if (first_word == "Fire"){
            file >> first_word >> second_word;
            //makes sure both exist
            if(warrior_finder(second_word,warriors) &&
            noble_finder(first_word,nobles)){
                Warrior* temp_warrior = warrior_finder(second_word,warriors);
                Noble* temp_noble = noble_finder(first_word,nobles);
                temp_noble -> fire(*temp_warrior);
            }else{
                //sees if one doesnt exist which one does or if both
                if(noble_finder(first_word,nobles)){
                    cout << first_word << " not found";
                }
                if(warrior_finder(second_word,warriors)){
                    cout << second_word << " not found";
                }

            }

            //battles two warriorr
        }else if(first_word == "Battle"){
            file >> first_word >> second_word;
            Noble* first_noble, *second_noble;
            //gets two noble pointers
            first_noble= noble_finder(first_word,nobles);
            second_noble = noble_finder(second_word,nobles);
            //just check if the nobles exist and are not nullptr
            //and will battle if that s the case
            if (first_noble && second_noble){
                first_noble->battle(*second_noble);
            }else if(!first_noble&&!second_noble){
                cout << "Both Nobles not found" << endl;
            }else if(!first_noble){
                cout << first_noble->get_name() << "not found" << endl;
            }else if(!second_noble){
                cout<< second_noble->get_name() << "not found" << endl;
            }
            // we need to make a battle function that will
        }else if(first_word == "Status"){
            //calls the status function
            status(nobles,warriors);
        }else if(first_word == "Clear"){
            clear(warriors,nobles);
        }
    }
    //closes file
    file.close();
}

//calls the output operator of nobles and warriors
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors){
    cout << "Status" << endl << "======"
    << endl << "Nobles:" << endl;
    //checks if the vector is not empty
    if (nobles.size() != 0) {
        for (const Noble *noble: nobles) {
            cout << *noble << endl;
        }
    }else{
        cout << "NONE" << endl;
    }

    cout << endl << "Unemployed Warriors:" << endl;
    bool check = true;
    if(warriors.size() != 0) {
        for (const Warrior *warrior: warriors) {
            if (warrior->get_hiring() == false) {
                check = false;
                cout << *warrior << endl;
            }
        }
    }
    if(check){
        cout << "NONE" << endl;
    }
}



//finds and returns a warrior pointer in a vector of warrior pointers
Warrior* warrior_finder(const string& name, const vector<Warrior*>& warriors) {
    Warrior* warrior_ptr = nullptr;
    for (Warrior* warrior: warriors){
        if(warrior -> get_name() == name){
            warrior_ptr = warrior;
        }
    }
    return warrior_ptr;
}

//finds and returns a noble pointer in a vector of noble pointers
Noble* noble_finder(const string& name, const vector<Noble*>& nobles) {
    Noble* noble_ptr= nullptr;
    for(Noble* noble:nobles){
        if (noble -> get_name() == name){
            noble_ptr = noble;
        }
    }
    return noble_ptr;
}


//deletes every pointer in both vectors and clears the pointers
void clear(vector<Warrior*>& warriors, vector<Noble*>& nobles){
    for(Warrior* warrior: warriors){
        delete warrior;
    }
    warriors.clear();
    for (Noble* noble: nobles){
        delete noble;
    }
    nobles.clear();
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
