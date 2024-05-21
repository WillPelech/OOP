//Created By Will Pelech
//
//The purpose of this file is to read a file and create warriors
// and print out the status of the warriors as well as the results of
//the battles

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Warrior {
    string name;
    int strength;
};

//this function takes in two string arguments from the test file
//and uses a helper function find to Battle two warriors and output the result
void Battle(const string& warrior1,const string& warrior2,vector<Warrior>&
        warriors);
//this displays the status of all warriors
void Status(const vector<Warrior>& warriors);
//a function that creates a new warrior object and adds it to the
//warrior vector
void Add_warrior(const string& name,int strength, vector<Warrior>& warriors);
// this will return the index of a warrior in the warrior vector
//if the index is not found it will return the size of the warrior vector
size_t find(const string& warrior_name, const vector<Warrior>& warriors);



int main(){
    vector<Warrior> warriors;
    Warrior new_warrior;
    string first_word ;
    string first_name;
    int power;
    string second_name;
    ifstream file("warriors.txt");
    if(!file){
        cerr<<"file warriors.txt failed to open";
        exit(1);
    }
    //this loop checks the first word in each line then decides what to do
    while(file>>first_word){
        if (first_word == "Status"){
            Status(warriors);
        }else if(first_word=="Warrior") {
            file >> first_name >> power;
            Add_warrior(first_name,power,warriors);
        }else if (first_word == "Battle") {
            file >> first_name >> second_name;
            Battle(first_name,second_name,warriors);
        }
        }
    file.close();
}

size_t find(const string& warrior, const vector<Warrior>& warriors){
    for(size_t index = 0;index<warriors.size();index++) {
        if (warriors[index].name == warrior) {
            return index;
        }
    }
    return warriors.size();

}


void Add_warrior(const string& name, int strength, vector<Warrior>& warriors) {
    Warrior new_warrior;
    if (find(name, warriors) < warriors.size()) {
        cerr << "Warrior already exists";
    } else {
        new_warrior.name = name;
        new_warrior.strength = strength;
        warriors.push_back(new_warrior);
    }
}

void Status(const vector<Warrior>& warriors){
    cout<<"There are: "<<warriors.size()<<" warrriors"<<endl;
    for(size_t index=0; index<warriors.size();index++){
        cout<<"Warrior: "<<warriors[index].name<<", strength: "
        <<warriors[index].strength<<endl;
    }
}
//makes calls to the find function
void Battle(const string& warrior1,const string& warrior2,vector<Warrior>&
    warriors){
    int index1=find(warrior1,warriors);
    int index2= find(warrior2,warriors);
    int strength2=warriors[index2].strength;
    cout<<warrior1<<" battles "<<warrior2<<endl;
    //This block determines if there are any dead warriors before
    if(warriors[index1].strength==0 && warriors[index1].strength==0){
        cout<<"Oh, NO! They're both dead! Yuck!"<<endl;
        return;
    }else if(warriors[index1].strength==0){
        cout << "He's dead, " << warriors[index1].name << endl;
        return;
    }else if(warriors[index2].strength==0){
        cout << "He's dead, " << warriors[index2].name <<endl;
        return;
    }
    //this will battle the two warriors
    warriors[index2].strength-=warriors[index1].strength;
    warriors[index1].strength-=strength2;
    //this part will readjust any warriors health who falls below 0
    if (warriors[index1].strength<0){
        warriors[index1].strength=0;
    }
    if (warriors[index2].strength<0){
        warriors[index2].strength=0;
    }
    //This block of code prints what happened after the warriors battled
    if(warriors[index1].strength==0 && warriors[index1].strength==0){
        cout<<"Mutual Annihilation: "<<warriors[index1].name
        <<" "<<warriors[index2].name<<endl;
    }else if(warriors[index1].strength==0){
        cout<<warriors[index2].name<<" defeats "<<warriors[index1].name<<endl;
    }else if(warriors[index2].strength==0){
        cout<<warriors[index1].name<<" defeats "<<warriors[index2].name<<endl;
    }
}

