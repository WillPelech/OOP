//
// Created by Will Pelech on 4/19/24.
//

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator <<(ostream& os, const List& list){
        const Node* cursor=list.header->next;
        while(cursor!=list.trailer){
            os<< cursor->data<<" ";
            cursor=cursor->next;
        }
        return os;
    }
public:
    struct Node;
    ~List(){
        clear();
        delete header;
        delete trailer;
    }
    List& operator=(const List& other){
        clear();
        const Node* cursor = other.header->next;
        while(cursor!=other.trailer){
            push_back(cursor->data);
            cursor=cursor->next;
        }
        return *this;
    }

    List(const List& other):header(new Node()), trailer(new Node()),sizeOf(0){
        header->next=trailer;
        trailer->prev=header;
        const Node* cursor = other.header->next;
        while(cursor!=other.trailer){
            push_back(cursor->data);
            cursor=cursor->next;
        }
    }




    class iterator{
        friend class List;
    public:
        iterator(Node* where):where(where) { }
        iterator& operator++(){
            where=where->next;
            return *this;
        }
        iterator& operator--(){
            where= where->prev;
            return *this;
        }
        bool operator ==(const iterator& other) const{
            if(other.where==where){
                return true;
            }
            return false;
        }
        bool operator !=(const iterator& other)const{
            return !(other==*this);
        }

        int& operator * () const {
            return where->data;
        }

    private:
        Node* where;
    };

    iterator insert(iterator it, int data){
        Node* new_n = new Node{data,it.where,it.where->prev};
        it.where->prev->next=new_n;
        it.where->prev=new_n;
        it.where=it.where->prev;
        sizeOf++;
        return it;
    }
    iterator erase(iterator it) {
        Node *hold = it.where;
        it.where->prev->next=it.where->next;
        it.where->next->prev=it.where->prev;
        sizeOf--;
        it.where=it.where->next;
        delete hold;
        return it;
    }

    iterator begin(){
        return iterator(header->next);
    };
    iterator end(){
        return iterator(trailer);
    }



    struct Node;
    int& operator [] (int index){
        if(index>sizeOf){cerr<<"Out of Bounds";}

        Node* cursor =header->next;
        for(size_t ind  =0 ;ind<index; ind++){
            cursor  = cursor -> next;
        }
        return cursor->data;
    }
    int operator [] (int index) const{
        if(index>sizeOf){cerr<<"Out of Bounds";}

        const Node* cursor = header->next;
        for(size_t ind  =0 ;ind<index; ind++){
            cursor  = cursor -> next;
        }
        return cursor->data;
    }

    List():
            header(new Node()), trailer(new Node()),sizeOf(0){
        header->next=trailer;
        trailer->prev=header;
    }
    void push_back(int data){
        Node* new_n = new Node{data,trailer,trailer->prev};
        trailer->prev->next=new_n;
        trailer->prev=new_n;
        sizeOf ++;
    }
    void pop_back(){
        if(sizeOf!=0) {
            Node *hold = trailer->prev;
            trailer->prev->prev->next=trailer;
            trailer->prev=trailer->prev->prev;
            delete hold;
            sizeOf--;
        }

    }
    int front() const{
        if(sizeOf!=0){
            return header->next->data;
        }
        return 0;
        cerr<<"invalid list";
        exit(1);
    };
    int& front(){
        if(sizeOf!=0){
            return header->next->data;
        }
        cerr<<"invalid list";
        exit(1);
    }

    int back() const{
        if(sizeOf!=0){
            return trailer->prev->data;
        }
        return 0;
        cerr<<"invalid list";
        exit(1);
    };

    int& back() {
        if(sizeOf!=0){
            return trailer->prev->data;
        }
        cerr<<"invalid list";
        exit(1);
    };





    size_t size() const{return sizeOf;}

    void push_front(int data){
        Node* new_n = new Node{data,header->next, header};
        header->next->prev=new_n;
        header->next=new_n;
        sizeOf++;
    }

    void pop_front(){
        if(sizeOf!=0) {
            Node *hold = header->next;
            header->next->next->prev=header;
            header->next=header->next->next;
            delete hold;
            sizeOf--;
        }
    }

    void clear(){
        while(sizeOf!=0){
            pop_front();
        }
    }
    struct Node{
        int data;
        Node* next;
        Node* prev;
    };





private:

    Node* header;
    Node* trailer;
    size_t sizeOf;
};

// Task 1
void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
         << ", front: " << myList.front()
         << ", back(): " << myList.back()
         << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
void changeFrontAndBackConst(const List& theList) {
//    theList.front() = 17;
//    theList.back() = 42;
}

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << "Leaving doNothing\n";
}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }

    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";

}