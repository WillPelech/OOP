//
// Created by Will Pelech on 4/24/24.
//Hw 09 implementing a polynomial class
//
#include "Polynomial.h"

using namespace std;

//default constructor
Polynomial::Polynomial() :
        head(new Degree{0, nullptr}), len(0){}
//constructor which takes vector in
Polynomial::Polynomial(vector<int> vec):
        head(new Degree{0, nullptr}),len(0)
{
    Degree *current = head;
    //edge case of empty vector
    if(vec.size()==0) {
        head= nullptr;
        return;
    }
    // eliminates leading zeros
    size_t start = 0;
    while(vec[start]==0){
        start+=1;
    }
    //adds terms while incrementing the length
    for (size_t i = start; i < vec.size(); i++) {
        current ->next= new Degree{   vec[i], nullptr};
        current = current->next;
        len++;
    }
}
//assignment operator
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if(this == &rhs) return *this;//checks for self assignment
    clear();//gets rid of everything
    if (rhs.head == nullptr) {//incasee rhs is empty
        head = nullptr;
        len = 0;
        return *this;
    }
    head = new Degree{0, nullptr};//makes a new head
    Degree* cursor_lhs = head;//starts at head
    const Degree* cursor_rhs = rhs.head->next;
    //loops through
    while(cursor_rhs){
        //iterates making the next term for each poly
        cursor_lhs -> next = new Degree{cursor_rhs->coeff, nullptr};
        cursor_lhs = cursor_lhs -> next;//makes sure lhs and rhs match
        cursor_rhs = cursor_rhs -> next;
    }
    len = rhs.len;//makes sure both have the same length
    return *this;
}


//copy constructor
Polynomial::Polynomial(const Polynomial & rhs):
        head(new Degree{0, nullptr}), len(rhs.len) {
    //makes sure rhs polynomial exists
    if(rhs.head == nullptr){
        return;
    }
    Degree* cursor_lhs = head;//makes a cursor that starts at head
    const Degree* cursor_rhs = rhs.head->next;//rhs read cursor
    //loops thorugh and copies over
    while(cursor_rhs){
        cursor_lhs -> next = new Degree{cursor_rhs->coeff, nullptr};
        cursor_lhs = cursor_lhs -> next;
        cursor_rhs = cursor_rhs -> next;
    }

}

//destructor
Polynomial::~Polynomial(){
    clear();//calls clear method which manages heap
};

//output operator
ostream& operator <<(ostream& os, const Polynomial& poly){
    if(poly.len == 0){//checks length 0
        os << "0";
        return os;
    }
    //ptrs to go through poly
    Polynomial::Degree* temp_head = poly.head->next;
    size_t exp = poly.len -1;

    while(temp_head){
        //condition when not head and coef is not zero
        if(temp_head!=poly.head->next and temp_head->coeff!=0){
            os<<"+";
        }
        //decides what to do by looking at coedd and exp
        if (temp_head->coeff == 1 && exp != 0) {
            os << "x";
        } else if (temp_head->coeff == -1 && exp != 0) {
            os << "-x";
        } else if (temp_head->coeff != 0 && exp != 0) {
            if (exp != 0) {
                os << temp_head->coeff << "x";
            }
        }
        //handles exponentiation mainly looking when not to exponent
        if (exp == 0 and temp_head->coeff!=0) {
            os << temp_head->coeff;
        }else if (exp == 1 and temp_head->coeff!=0) {
        }else if (temp_head->coeff!=0){
            os << "^" << exp;
        }
        exp--;//decrements exponents as we go
        temp_head = temp_head->next;
    }
    return os;
}

//+ assignment
Polynomial& Polynomial::operator+=(const Polynomial& other){
    //starts at first for both
    Degree* lhs = head->next;
    Degree* rhs = other.head->next;
    //finds the difference in lengths of both
    int dif = (len - 1) - (other.len-1) ;
    //if the dif is negative then we make new nodes holding zero
    //so they have a place to be added
    while(dif < 0){
        head->next= new Degree{0,head->next};
        dif++;
        len++;
    }
    //resets lhs cursor
    lhs = head->next;
    //if the dif is positive we move for they are in the same
    //location
    while(dif > 0){
        lhs=lhs->next;
        dif --;
    }
    //checks both arent null and adds them
    while(lhs && rhs){
        lhs -> coeff += rhs -> coeff;
        lhs = lhs->next;
        rhs = rhs->next;
    }
    leading_zeros();//gets rid of possible leading zeroes
    return *this;

}

//addition
Polynomial operator +(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial lhs_temp = lhs;//makes copy
    lhs_temp += rhs;//makes a call to +=
    return lhs_temp;//returns the temp
}
//clears and manages the heap for polynomial
void Polynomial::clear(){
    if(head == nullptr){//checks head is not a null ptr
        return;
    }
    Degree* curr = head;
    Degree* next = curr->next;
    while(next){//makes sure that the next exists
        delete curr;//gets rid of the curr and increments
        curr=next;
        next=next->next;
    }
    head = nullptr;//gets rid of possible dangling pointer
    len=0;//sets the len to 0
}
//equal operator
bool operator==(const Polynomial& rhs,const Polynomial& lhs){
    if(rhs.len != lhs.len){//checks dif length first
        return false;
    }

    Polynomial::Degree* rhs_c = rhs.head->next;
    Polynomial::Degree* lhs_c = lhs.head->next;
    //goes digit by digit and checks
    for(size_t ind = 0; ind < rhs.len; ind++){
        if(rhs_c->coeff!=lhs_c->coeff){
            return false;
        }
    }
    return true;
}
//inequality operator
bool operator!=(const Polynomial& rhs,const Polynomial& lhs){
    return !(rhs==lhs);//calls not ==
}
//evaluates polynomial using horners method
int Polynomial::evaluate(int val) const{
    if (!head || !head->next) {//checks that they both exists
        return 0;
    }
    //base value that we add to
    int tracker = head->next->coeff;
    Degree* cursor=head->next;
    while(cursor->next){//while next value isnt null
        cursor=cursor->next;
        tracker *=  val;
        tracker += cursor->coeff;
    }
    return tracker;
}
//gets rid of leading zeroes
void Polynomial::leading_zeros() {
    Degree* temp_for_delete;
    //loops through and temp holds a note that we delete
    while(head->next->coeff==0){
        temp_for_delete = head -> next;
        head -> next = head -> next -> next;
        delete temp_for_delete;
        len--;
    }
}