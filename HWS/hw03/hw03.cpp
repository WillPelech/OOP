//Created by Will Pelech
//
//The purpose of this file is to read a file and create warriors
// and print out the status of the warriors as well as the results of
//the battles this will be done using a Warrior objects and their nested
//classes Weapon

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//This is the warrior class which contains the nested class Weapon and also
//has private fields name and warrior_weapon which are of type string and Weapon
class Warrior{
//this nested class has private fields int weapon_strength and string
// weapon_name which as well as setters and getters for the strength field
    class Weapon{
        friend ostream& operator << (ostream& os, const Weapon&);
    public:
        Weapon(const string& weapon_name, int weapon_strength)
                : weapon_name(weapon_name), weapon_strength(weapon_strength) {};
        //getters and setters
        int get_strength() const {return weapon_strength;}

        void set_strength(int strength){
            if (strength < 0){
                weapon_strength = 0;
            }else {
                weapon_strength = strength;
            }
        }

    private:
        int weapon_strength;
        string weapon_name;
    };

friend ostream& operator << (ostream& os, const Warrior& warrior);
friend ostream& operator << (ostream& os, const Weapon& weapon);

public:
    //default constructor for the warrior class
    Warrior(const string& warrior_name, const string& weapon_name,
            int weapon_strength) : name(warrior_name),
            warrior_weapon(weapon_name, weapon_strength){}
    //getters and setters to access fields within Warrior and Weapon
    const string& get_name() const {return name;}
    int get_strength() const{return warrior_weapon.get_strength();}
    //modifies the strength of the warrior weapons
    void modify(int strength) {warrior_weapon.set_strength(strength);}
private:
    string name;
    //private nested class Weapon
    Weapon warrior_weapon;
};
//function prototypes
//this function opens a file and returns an ifstream
ifstream open_file();
//this function will be used to display all the warrior objects
void status(const vector<Warrior>& warriors);
//this function battles two warriors by using the find function
//and then using
void battle(const string& first_name, const string& second_name,
            vector<Warrior>& warriors);
//this function returns a size_t which stores the index of a warrior
//in the warriors vector and returns the size of warriors if
//the warrior is not found
size_t find(const string& warrior, const vector<Warrior>& warriors);

int main(){
    string first_word;
    string second_word;
    string third_word;
    int strength;
    vector<Warrior> warriors;

    ifstream file=open_file();
    //this loop will decide what to do based off of the first word in each line
    while (file >> first_word) {
        //creates and adds a new warrior
        if (first_word == "Warrior") {
            file >> second_word >> third_word >> strength;
            Warrior temporary_warrior(second_word, third_word, strength);
            warriors.push_back(temporary_warrior);
        //battles two warriors which also checks for nonexistent warriors
        }else if(first_word == "Battle"){
            file >> second_word >> third_word;
            battle(second_word,third_word,warriors);
        }else{
            //calls the status function
            status(warriors);
        }

    }

    file.close();
}
//this is the output operator for the warrior this method accesses
//the private fields of Warrior called name and warrior_weapon
ostream& operator << (ostream& os, const Warrior& warrior){
    os << "Warrior: " << warrior.name << ", weapon:" << warrior.warrior_weapon;
    return os;
}
//this is the output operator for the nested class weapon which is in
//the warrior class
ostream& operator << (ostream& os, const Warrior::Weapon& weapon){
    os << " " << weapon.weapon_name << ", " << weapon.weapon_strength;
    return os;
}

//this function returns an ifstream or raises in an error if warriors.txt
//fails to open
ifstream open_file(){
    ifstream file("warriors.txt");
    if (!file){
        cerr << "File failed to open";
        exit(1);
    }
    return file;
}

size_t find(const string& warrior, const vector<Warrior>& warriors){
    for(size_t index = 0;index < warriors.size();index++) {
        if (warriors[index].get_name() == warrior) {
            return index;
        }
    }
    return warriors.size();
}
//this function battles two warriors by using getter and setter functions
//to
void battle(const string& first_name, const string& second_name,
            vector<Warrior>& warriors){
    // these hold indexes of both warriors in the warriors vector
    size_t index1= find(first_name,warriors);
    size_t index2= find(second_name,warriors);
    //checks to print an error of a nonexistent warrior
    if(index1==warriors.size()||index2==warriors.size()){
        cerr << "You tried to battle at least one nonexistent warrior" << endl;
        return;
    }
    cout << warriors[index1].get_name() << " battles " <<
    warriors[index2].get_name() << endl;
    int strength_1=warriors[index1].get_strength();
    int strength_2=warriors[index2].get_strength();
    //makes comparisons to see if any of the initial warriors are dead
    if(strength_1 == 0 && strength_2 == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    }else if (strength_1==0){
        cout << "He's dead, " << warriors[index2].get_name() << endl;
        return;
    }else if (strength_2==0){
        cout << "He's dead, " << warriors[index1].get_name() << endl;
        return;
    }
    //this part changes the warriors strengths when they battle
    warriors[index1].modify(strength_1-strength_2);
    warriors[index2].modify(strength_2-strength_1);
    //these conditionals check what the final outcome of the battle is
    if(warriors[index1].get_strength() == 0 &&
        warriors[index2].get_strength() == 0){
        cout << "Mutual Annihilation: " << warriors[index1].get_name() <<" and "
        << warriors[index2].get_name()<<" die at each other's hands" << endl;
    }else if (warriors[index1].get_strength()==0){
        cout << warriors[index2].get_name() <<" defeats"<<
        warriors[index1].get_name()<< endl;
    }else if (warriors[index2].get_strength()==0){
        cout << warriors[index1].get_name() <<" defeats "<<
             warriors[index2].get_name() << endl;
    }
}
//status method prints out warriors using its output operator and displays every
//warrior and there weapon and strength
void status(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " Warriors" << endl;
    for(const Warrior& warrior: warriors) {
        cout << warrior << endl;
    }
}