//
// Created by Will Pelech on 2/2/24.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

struct molecule{
    vector<string> names;
    int carbon;
    int hydrogen;
};

void open_stream(ifstream& current_stream);
void filler(ifstream& current_stream,vector<molecule>& molecule_list);
//returns the index of location of the of a molecule
size_t find_formula(int c ,int h,  const vector<molecule>& molecule_list);
void display_vec(const vector<molecule>& mole_list);
void insert(int count_h,int count_c,vector<molecule>& molecule_list, const string& name);
void print_singular(const molecule& mole_list);
void bubble_sort(vector<molecule>& molecule_list);
int main(){
    vector<molecule> molecule_list;
    string stream;
    cout << "enter a file name: ";
    cin >> stream;
    ifstream file(stream);
    open_stream( file );
    filler(file, molecule_list);
    cout << "Unsorted" << endl;
    display_vec(molecule_list);
    bubble_sort(molecule_list);
    cout<<endl<<"Sorted:"<<endl;
    display_vec(molecule_list);
}

void open_stream(ifstream& current_stream){
    string new_name;
    while(!current_stream){
        cout << "The file didn't open try again:";
        cin >> new_name;
        cout << endl;
        current_stream.open(new_name);
    }
}
void filler(ifstream& current_stream,vector<molecule>& molecule_list){
    string name;
    char c;
    int count_c;
    char h;
    int count_h;
    int index;

    //this while loop will call a function to find chemical formula and either
    // add or push to the back depending on the return int
    while(current_stream>>name>>c>>count_c>>h>>count_h){
        insert(count_h,count_c,molecule_list,name);
    }

}
void insert(int count_h,int count_c,vector<molecule>& molecule_list,const string& name){
    size_t index= find_formula(count_c,count_h,molecule_list);

    if (molecule_list.size()==index){
        molecule new_molecule;
        new_molecule.hydrogen=count_h;
        new_molecule.carbon=count_c;
        new_molecule.names.push_back(name);
        molecule_list.push_back(new_molecule);
    }else{
        molecule_list[index].names.push_back(name);
    }
}

size_t find_formula(int c ,int h,const vector<molecule>& molecule_list){
    for(size_t index =0; index<molecule_list.size();index++){
        if(molecule_list[index].carbon==c && molecule_list[index].hydrogen==h){
            return index;
        }
    }
    return molecule_list.size();
}
void display_vec(const vector<molecule>& mole_list){
    for (size_t index=0;index<mole_list.size();index++){
        print_singular(mole_list[index]);
    }

}

void print_singular(const molecule& mole_list){
    cout<<'C'<<mole_list.carbon<<'H'<<mole_list.hydrogen<<" ";
    for (const string& name:mole_list.names){
        cout<<name<<" ";
    }
    cout<<endl;
}
void bubble_sort(vector<molecule>& molecule_list){
    for(size_t indexi =0;indexi < molecule_list.size();indexi++){
        for(size_t indexj=0;indexj < molecule_list.size()-1;indexj++){
            if (molecule_list[indexj].carbon > molecule_list[indexi].carbon){
                swap(molecule_list[indexj],molecule_list[indexi]);
            }else if(molecule_list[indexj].carbon == molecule_list[indexi].carbon) {
                if (molecule_list[indexj].hydrogen >
                    molecule_list[indexi].hydrogen) {
                    swap(molecule_list[indexj], molecule_list[indexi]);
                }
            }
        }
    }
}