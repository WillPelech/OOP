//Will Pelech this my recitation 4 code
//

// Task 1
// Who are you? What is this program called?

// I have stopped using cerr in your started code because CLion makes
// a mess with it.

#include <iostream>   // needed for task 2
#include <vector>     // needed for task 27
using namespace std;  // needed for task 2

// Task 16 Complex definition
struct Complex{
    double real;
    double img;
};

// Task 17 PlainOldClass definition
class PlainOldClass {
public:
    //constructor
    PlainOldClass() : x(-72) {}
    //getters and setters
    int getX() const { return x; }
    void setX( int val )  { x = val; }
private:
    int x;
};

// Task 18 PlainOldClass2 definition
class PlainOldClassV2 {
public:
    PlainOldClassV2() : x(-72) {}
    int getX() const { return x; }
    //this sets the x to x which is kind of hard to tell what's going on
    void setX( int x )  {this->x = x; } // HMMMM???
private:
    int x;
};

// Task 28 Colour definition
class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b)
            : name(name), r(r), g(g), b(b) {}
    void display() const {
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
    }
private:
    string name;
    unsigned r, g, b;
};

// Task 29 SpeakerSystem definition
class SpeakerSystem {
public:
    void vibrateSpeakerCones(unsigned signal) const {

        cout << "Playing: " << signal << "Hz sound..." << endl;
        cout << "Buzz, buzzy, buzzer, bzap!!!\n";
    }
};


// Task 29 Amplifier definition
// the problem is the pointer is not constant
// you could make attached speakers const
// the second is you could make spkrs non constant but this could
//allow us to change the speakers
class Amplifier {
public:
    void attachSpeakers(const SpeakerSystem& spkrs)
    {
        if(attachedSpeakers) {
            cout << "already have speakers attached!\n";
        } else {
            attachedSpeakers = &spkrs;
        }
    }

    void detachSpeakers() { // should there be an "error" message if not attached?
        attachedSpeakers = nullptr;
    }

    void playMusic( ) const {
        if (attachedSpeakers) {
            attachedSpeakers -> vibrateSpeakerCones(440);
        } else {
            cout << "No speakers attached\n";
        }
    }
private:
    const SpeakerSystem* attachedSpeakers = nullptr;
};

// Task 30 Person Definition
class Person {
public:
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        if (this->roomie == nullptr&& newRoomate.roomie== nullptr or this!= &newRoomate) {
            roomie = &newRoomate;        // now I have a new roomie
            newRoomate.roomie = this;    // and now they do too
        }else{
            cerr<<"Someone already has a roomie";
        }
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie = nullptr;
    string name;
};



int main() {
    cout << "Task 1\n";

    // Task 2
    cout << "Task 2\n";
    // Add code here
    int x;
    x = 10;
    cout << "x=" << x << endl;

    // Task 3
    cout << "Task 3\n";
    // Using the debugger, set a breakpoint in main and run to
    // it. Observe the value of x.
    // [No new code]

    // Task 4
    cout << "Task 4\n";
    // Using the debugger, step forward observing the value of x
    // [No new code]

    // Task 5
    cout << "Task 5\n";
    // Watch window. Xcode equivalent? Gdb equivalent?
    // Activity: see x's value
    // [No new code]

    // Task 6
    cout << "Task 6\n";
    // Watch window to see the address of x
    // [No new code]
    //address was 0x16f31768c
    // Task 7
    cout << "Task 7\n";
    // Watch window to see the value stored at the address of x
    // [No new code]

    // Task 8
    cout << "Task 8\n";
    // Add code. here
    int* p;
    p = &x;
    cout << "p = " << p << endl;

    // Task 9
    cout << "Task 9\n";
    // Using the value you observe in &x, write a line of code to
    // directly assign that value to p. E.g. p = 0x0012fed4;
    // What happens? Should have a compiler error.
    //p=0x16eeaf69c;

    // Task 10
    cout << "Task 10\n";
    // Run earlier print statement for "p = ". Observe the watch
    // window.
    // Then add code here:
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;
    // Task 11
    cout << "Task 11\n";
    // Add code here
    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;


    // Task 12
    cout << "Task 12\n";
    // Add code
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;

    // Task 13
    cout << "Task 13\n";
    // Add code here
    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;

    // Task 14
    cout << "Task 14\n";
    // Add code here
    double d(33.44);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p  = *pD;
    *q  = *p;
    //pD  = p;
    //p   = pD;

    // Task 15
    cout << "Task 15!!!\n"; // Yes, this is a VERY IMPORTANT task!
    // Const and pointers.
    // Add code here
    int joe = 24;
    const int sal = 19;
    int*  pI;
    //works because you are assigning a pointer to an address
    pI = &joe;
    //works because it sets the value at the address pI points to to 234
    *pI = 234;
    //this will ont work because pI is a pointer of type int and cannot point
    //to something of type const int
//  pI = &sal;
    //works because it sets the value at the address pI points to to 7623
    *pI = 7623;
    const int* pcI;
    //not same type will not compile
    pcI = &joe;

   // const in front means that this is an immutable pointer
   // and cannot be changed
//     *pcI = 234;
   //this works because pcI and sal are const in
   pcI = &sal;
   //issue pcI is const and cannot be changed
// *pcI = 7623;
//needs to be initialized to an address because it cannot change memory locations
//int* const cpI;
int* const cpI(&joe);

//cannot change memory locations
//int* const cpI(&sal);
//cannot change memory location
//  cpI = &joe;
//can do because it si in the same memory location
 *cpI = 234;
 //cannot change memory locations
//  cpI = &sal;
 *cpI = 7623;

//needs to be initialized to a location because it cannot be moved
//const int* const cpcI;
const int* const cpcI(&joe);
//this cannot change addresses
//const int* const cpcI(&sal);
//cannot change address
//  cpcI = &joe;
//cannot modify the value at its address
// *cpcI = 234;
//cannot change addresses
//  cpcI = &sal;
//cannot modify value at address
// *cpcI = 7623;

    // Task 16
    cout << "Task 16\n";
    // Pointers to user-defined types.  Add the type for struct Complex above.
    // Add code here
    Complex c ={11.23,45.67};
    //contains a ptr to the address of c
    Complex* pC(&c);

    cout<<"real:"<<(*pC).real<<"\nimaginary: "<<(*pC).img<<endl;
    // Task 17
    cout << "Task 17\n";
    // Add code here
    // What is this code doing?

    PlainOldClass poc;
    //pointer pointing to &poc
    PlainOldClass* ppoc( &poc );
    //access public method using the special dereferencing operator
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;

    // Task 18
    cout << "Task 18\n";
    // Test the changes to PlainOldClass
    PlainOldClassV2 poc2;
    PlainOldClassV2* ppoc2(&poc2);
    cout << ppoc2->getX() << endl;
    ppoc2->setX( 2837 );
    cout << ppoc2->getX() << endl;

    // Task 19
    cout << "Task 19\n";
    // creating and modifying an item on the heap. Use the debugger to
    // observe.
    // Add code here
    //this points to a location in the heap
    int* pDyn = new int(3);
    *pDyn = 17;
    cout << "The " << *pDyn
    << " is stored at addres" << pDyn << " which is in the heap\n";
    // Task 20
    cout << "Task 20\n";
    // What happens to pDyn in the following? With most compilers it
    // is unchanged.  Visual Studio actually changes it. (I should
    // check if that is just in debug mode.)
    // Add code here
    cout << pDyn << endl;
    delete pDyn;
    //the pointer still points to the same place in the heap
    cout << pDyn << endl;

    cout << "The 17 might still be stored at address"  << pDyn <<
    "even though we delected pDyn\n";
    cout << "But can we dereference pDyn? we can try. This might crash..." <<
    *pDyn <<". Still here?\n";

    // Task 21
    cout << "Task 21\n";
    // Add code here
    pDyn= nullptr;
    double* pDouble = nullptr;
    // Task 22
    cout << "Task 22\n";
    // Add code here
//    cout << "Can we dereference nullptr?  " << *pDyn << endl;
//    cout << "Can we dereference nullptr?  " << *pDouble << endl;

    // Task 23
    cout << "Task 23\n";
    // Question. Can <code>this</code> be nullptr?
    // it cannot in order for this keyword to be called it will reference the
    //original object that this was called on

    // Task 24
    cout << "Task 24\n";
    // Add code here
    //pointer to a double in the heap
    double* pTest = new double(12);

    delete pTest;
    pTest = nullptr;
    delete pTest;
    // Task 25
    cout << "Task 25\n";
    // Add code here
    short* pShrt = new short(5);
    delete pShrt;
    //raises an error saying that we deleted an already freed up space
//    delete pShrt;

    // Task 26
    cout << "Task 26\n";
    // Add code here
    long jumper = 12238743;
//    delete jumper;
    long* ptrTolong = &jumper;
//    delete ptrTolong; we are trying to delete a pointer not on the heap
// which causes an issue
    Complex cmplx;
//    we are deleting an initiliazed class where none of the
//  members are on the heap
//    delete cmplx;

    // Task 27
    cout << "Task 27\n";
    // Add code here
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    //sets the values of the Complex class
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        tmpPCmplx = new Complex; // create a new Complex object on the heap
        tmpPCmplx->real = ndx;   // set real and img to be the
        tmpPCmplx->img  = ndx;   // value of the current ndx
        complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
// display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        //dereferences and accesses the real and img
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
// release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx];
    }
// clear the vector
    complV.clear();

    // Task 28 Use the Colour class
    cout << "Task 28\n";
    // Add Colour class above main
    // Add code here
    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

// fill vector with Colours from the file
// this could be from an actual file but here we are using the keyboard instead of a file
// (so we don't have to create an actual file)
// Do you remember the keystroke combination to indicate "end of file" at the keyboard?
// somehow the while's test has to fail - from keyboard input
//    while (cin >> inputName >> inputR >> inputG >> inputB) {
//        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
//    }
//
//// display all the Colours in the vector:
//    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
//        colours[ndx]->display();
//        cout << endl;
//    }
//    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
//        delete colours[ndx];
//
//    }


    // Task 29 Use SpeakerSystem and Amplifier classes
    cout << "Task 29\n";
    // Add SpeakerSystem and Amplifier classes above main


    // Task 30 Use the Person class
    cout << "Task 30\n";
    // Add Person class above main
    // Add code here


    Person joeBob("Joe Bob"), billyJane("Billy Jane");

    joeBob.movesInWith(billyJane);

// did this work out?
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;

}
