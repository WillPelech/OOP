//
// Created by Will Pelech on 1/31/24.
//
//The purpose of the code is to be able to decrypt encoded files using the
//Caesarian Cypher

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//function loops for every character in the line and mutates it using the
//Caesarian cypher and calling a helper function which is a letter decoder
void string_mutator(string& line, int rotation);

//receives a char and returns the corresponding Caesar Cypher char
char letter_decoder(char letter, int rotation);


int main() {

    int rotation;
    string line_to_copy;
    vector<string> lines;

    //tests if file was opened exits code if not opened
    ifstream file("encrypted.txt");
    if(!file){
        cerr << "failed to open file";
        exit(1);
    }

    //saves the first line of the file into rotation::type int
    file >> rotation;
//    cout << rotation << endl;

    //puts all the lines of a file into a vector
    while(getline(file,line_to_copy)){
        lines.push_back(line_to_copy);
    }

    file.close();

    //makes a call to the string mutator
    for(size_t index = 0; index<=lines.size() ; ++index){
        string_mutator(lines[index-1],rotation);
    }

    // this goes through every mutated line in the vector and displays it
    for (size_t line = lines.size(); line > 0 ; --line){
        cout << lines[line-1]<<endl;
    }


}

void string_mutator(string& line, int rotation){
    //this loop goes character by character and reassigns the current character
    //with the one provided by the
    for (size_t index = 0; index < line.size(); ++ index){
        char curr_letter = letter_decoder(line[index],rotation);
        line[index] = curr_letter;
    }
}

char letter_decoder(char letter, int rotation){
    char new_letter;
    //these statements determine how we will mutate the characters off of the
    //guidelines provided
    if (letter < 'A' || letter > 'Z') {
        new_letter=letter;
    } else if(letter - rotation > 'Z') {
        new_letter=letter- rotation -26;
    } else if(letter - rotation < 'A') {
        new_letter=letter - rotation + 26;
    } else {
        new_letter=letter - rotation;
    }

    return new_letter;
}

