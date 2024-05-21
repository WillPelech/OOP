
/*
  rec01_start.cpp
  spring 2024
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


//
// Function prototypes for tasks 15-17
//

// Task 15. Function to display a vector of ints
void vect_display(const vector<int>&);


// Task 16. Function to modify the vector, using indices
void dub (vector<int>&);


// Task 17. Function to modify the vector, using a ranged for
void dub_ranged_for(vector<int>&);



//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"

    std::cout << "Hello" << std::endl;


    // Task 2  Printing hello ...  Using "using namespace"
    cout << "Hello" << endl;


    //
    // Types and variables
    int x;
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;

    // Task 3  Displaying uninitialized variable
    cout << "x:" << x << endl;

    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    cout << "sizeof(x):" << sizeof(x) << endl;
    cout << "sizeof(y):" << sizeof(y) << endl;
    cout << "sizeof(z):" << sizeof(pie) << endl;

    // Task 5  Attempt to assign the wrong type of thing to a variable
//    x = "felix";
//  this is a compilation error because there is an error assigning a string to an integer
//    cout<<x;

    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y <= 20 && y >= 10) {
        cout << "y is in between 20 and 10" << endl;
    } else {
        cout << "y is not in the range 20 to 10";
    }


    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    cout << "For loop:";
    for (int i = 10; i <= 20; ++i) {

        cout << i << " ";
    }
    cout << endl;
    // Then with a while loop
    cout << "While loop:";
    int j = 10;
    while (j <= 20) {
        cout << j << " ";
        ++j;
    }
    cout << endl;
    // Finally with a do-while loop
    cout << "Do-While loop:";
    int l = 10;
    do {
        cout << l << " ";
        ++l;
    } while (l < 21);
    cout << endl;

    // Task 8  Looping to successfully open a file, asking user for the name
    bool file_opened = false;
    string filename;
    ifstream curr_file;
    while (!file_opened) {
        cout << "what is the name of the file";
        cin >> filename;
        curr_file.open(filename);
        if (!curr_file) {
            cout << "the file you tried to open does not exist" << endl;
        } else {
            file_opened = true;
            cout << "file successfully opened";
        }
    }

    // Task 9  Looping, reading file word by "word".
    string word;
    while (curr_file >> word) {
        cout << word << endl;
    }
    // Task 10 Open a file of integers, read it in, and display the sum.
    ifstream numfile("integers.txt");
    if (!numfile) {
        cerr << "An error occurred";
        exit(1);
    }
    int total = 0;
    int curr_num;
    while (numfile >> curr_num) {
        cout << curr_num << " ";
        total += curr_num;
    }

    cout << endl << total << endl;

    // Taks 11 Open and read a file of integers and words. Display the sum.
    ifstream mixfile("mixed.txt");
    if (!mixfile) {
        cerr << "An error occurred";
    }
    int total2 = 0;
    int curr_num1;
    while (mixfile >> curr_num1) {
        cout << curr_num1 << " ";
        total2 += curr_num1;
    }

    cout << endl << total2;
    cout << endl;

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> int_vec;
    for (int i = 10; i <= 100; i += 2) {
        int_vec.push_back(i);
    }




    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < int_vec.size() - 1; ++i) {
        cout << int_vec[i] << " ";
    }
    cout << endl;

    //         b) using a "ranged for"
    for (int l: int_vec) {
        cout << l << " ";
    }
    cout << endl;
    //         c) using indices again but backwards
    for (size_t i = int_vec.size(); i > 0; --i) {
        cout << int_vec[i-1] << " ";
    }
    cout << endl;

    // Task 14. Initialize a vector with the primes less than 20.
    vector<int> num2{2, 3, 5, 7, 11, 13, 17, 19};
    cout << "<";
    for (int num: num2) {
        cout << num << ",";
    }
    cout << ">";

    //
    // Function calls
    //
    // Task 15  Function to print a vector
    vect_display(num2);

    // Task 16  Function to double the values in a vector
    dub(num2);
    vect_display(num2);

    // Task 17  Function to double the values in a vector, using a ranged for
    dub_ranged_for(num2);
    vect_display(num2);

}
//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints





void vect_display(const vector<int>& display_vect){
    cout<<"<";
    for (size_t i =0;i<display_vect.size();++i){
        if (i==display_vect.size()-1){
            cout<<display_vect[i];
        }else{
            cout<<display_vect[i]<<",";
        }

    }
    cout<<">"<<endl;
}
// Task 16. Function to modify the vector, using indices





void dub (vector<int>& dub_vect) {
    for (size_t i =0;i<dub_vect.size();++i){
        dub_vect[i]=2*dub_vect[i];
    }
}



// Task 17. Function to modify the vector, using a ranged for

void dub_ranged_for(vector<int>& dub_vect){
    for (int& num:dub_vect){
        num=2*num;
    }
}






