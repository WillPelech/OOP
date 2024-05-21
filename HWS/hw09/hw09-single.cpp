//
// Created by Will Pelech on 4/15/24.
//

#include <iostream>
#include <vector>
using namespace std;

class Polynomial{
    friend ostream& operator << (ostream& os, const Polynomial& poly);
    friend bool operator == (const Polynomial& rhs,const Polynomial& lhs);
public:
Polynomial();

Polynomial(const Polynomial& other);

Polynomial(vector<int> vec);

~Polynomial();

Polynomial& operator+=(const Polynomial& other);

Polynomial& operator=(const Polynomial& rhs);

int evaluate(int val) const;

void leading_zeros();
private:
    void clear();

    // this holds the degree of the polynomial
    struct Degree{
        int coeff;
        Degree* next;
    };

    Degree* head;
    size_t len;
};


Polynomial operator +(const Polynomial& lhs, const Polynomial& rhs);
void doNothing(Polynomial temp) {}
bool operator!=(const Polynomial& rhs,const Polynomial& lhs);

int main() {
    //test constructor
    Polynomial p0;                       // 0
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    // Polynomial temp(p4);
    // cout << "temp: " << temp << endl;

    cout << "displaying polynomials\n"
         << "p0: " << p0 << endl
         << "p1: " << p1 << endl
         << "p2: " << p2 << endl
         << "p3: " << p3 << endl
         << "p4: " << p4 << endl
         << "has_a_zero: " << has_a_zero << endl;

//     Polynomial temp;
//     temp = p2 + p3;
//     cout << "temp: " << temp << endl;

    cout << "p2 + p3: " << (p2 + p3) << endl
         << "p2 + p4: " << (p2 + p4) << endl
         << "p4 + p2: " << (p4 + p2) << endl;

//    cout<< "p2 + p4: " << (p2+p4) << endl;

    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;
    cout << "p5: " << p5 << endl;

    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator

    Polynomial p6;

    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    p6 = p4;
    cout << "p6: " << p6 << endl;

    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;

    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    Polynomial p8({1, 1});
    Polynomial p9({-1, 1});
    Polynomial p10({0, 0, 2});
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()

    cout << "p8: " << p8 << endl
         << "p9: " << p9 << endl
         << "p10: " << p10 << endl;
    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;

    cout << "==================== Custom Test ===============";
    cout << endl;
    cout <<"multiple zeroes in middle polynomial:";
    Polynomial p11({1,0, 0, 2});
    cout<<p11;

}


// constructors
    Polynomial::Polynomial() : head(new Degree{0, nullptr}),
    len(0){}

    Polynomial::Polynomial(vector<int> vec):
    head(new Degree{0, nullptr}),len(0)
    {
        Degree *current = head;
        if(vec.size()==0) {
            head= nullptr;
            return;
        }
        // leading zeros
        size_t start = 0;
        while(vec[start]==0){
            start+=1;
        }

        for (size_t i = start; i < vec.size(); i++) {
            current ->next= new Degree{   vec[i], nullptr};
            current = current->next;
            len++;
        }
    }
//assignment operator
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if(this == &rhs) return *this;
    clear();
    if (rhs.head == nullptr) {
        head = nullptr;
        len = 0;
        return *this;
    }
    head = new Degree{0, nullptr};
    Degree* cursor_lhs = head;
    const Degree* cursor_rhs = rhs.head->next;
    while(cursor_rhs){
        cursor_lhs -> next = new Degree{cursor_rhs->coeff, nullptr};
        cursor_lhs = cursor_lhs -> next;
        cursor_rhs = cursor_rhs -> next;
    }
    len = rhs.len;
    return *this;
}


//copy constructor
Polynomial::Polynomial(const Polynomial & rhs):
head(new Degree{0, nullptr}), len(rhs.len) {
    if(rhs.head == nullptr){
        return;
    }
    Degree* cursor_lhs = head;
    const Degree* cursor_rhs = rhs.head->next;

    while(cursor_rhs){
        cursor_lhs -> next = new Degree{cursor_rhs->coeff, nullptr};
        cursor_lhs = cursor_lhs -> next;
        cursor_rhs = cursor_rhs -> next;
    }

}

//destructor
    Polynomial::~Polynomial(){
        clear();
    };

//output operator
ostream& operator <<(ostream& os, const Polynomial& poly){
    if(poly.len == 0){
        os << "0";
        return os;
    }
    Polynomial::Degree* temp_head = poly.head->next;
    size_t exp = poly.len -1;

    while(temp_head){
        if(temp_head!=poly.head->next and temp_head->coeff!=0){
           os<<"+";
        }

        if (temp_head->coeff == 1 && exp != 0) {
            os << "x";
        } else if (temp_head->coeff == -1 && exp != 0) {
            os << "-x";
        } else if (temp_head->coeff != 0 && exp != 0) {
            if (exp != 0) {
                os << temp_head->coeff << "x";

            }
        }
        if (exp == 0 and temp_head->coeff!=0) {
            os << temp_head->coeff;
        }else if (exp == 1 and temp_head->coeff!=0) {

        }else if (temp_head->coeff!=0){
            os << "^" << exp;
        }
        exp--;
        temp_head = temp_head->next;
        }
        return os;
}


Polynomial& Polynomial::operator+=(const Polynomial& other){
    Degree* lhs = head->next;
    Degree* rhs = other.head->next;
//    cout<<"first:"<<len<<endl;
//    cout<<"second:"<<other.len<<endl;
    int dif = (len - 1) - (other.len-1) ;
//    cout<<"dif:"<<dif<<endl;
    while(dif < 0){
            head->next= new Degree{0,head->next};
            dif++;
            len++;
    }
    lhs = head->next;
    while(dif > 0){
        lhs=lhs->next;
        dif --;
    }

    while(lhs && rhs){

        lhs -> coeff += rhs -> coeff;
        lhs = lhs->next;
        rhs = rhs->next;
    }
    leading_zeros();
    return *this;

}


Polynomial operator +(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial lhs_temp = lhs;
    lhs_temp += rhs;
    return lhs_temp;
}

void Polynomial::clear(){
    if(head== nullptr){
        return;
    }
    Degree* curr = head;
    Degree* next = curr->next;
    while(next){
        delete curr;
        curr=next;
        next=next->next;
    }
    head = nullptr;
    len=0;
}

bool operator==(const Polynomial& rhs,const Polynomial& lhs){
    if(rhs.len != lhs.len){
        return false;
    }
    Polynomial::Degree* rhs_c = rhs.head->next;
    Polynomial::Degree* lhs_c = lhs.head->next;
    for(size_t ind = 0; ind < rhs.len; ind++){
        if(rhs_c->coeff!=lhs_c->coeff){
            return false;
        }
    }
    return true;
}

bool operator!=(const Polynomial& rhs,const Polynomial& lhs){
    return !(rhs==lhs);
}

int Polynomial::evaluate(int val) const{
    if (!head || !head->next) {
        return 0;
    }

    int tracker = head->next->coeff;
    Degree* cursor=head->next;
    while(cursor->next){
        cursor=cursor->next;
        tracker *=  val;
        tracker += cursor->coeff;
    }
    return tracker;
}

void Polynomial::leading_zeros() {
    Degree* temp_for_delete;
    while(head->next->coeff==0){
        temp_for_delete = head -> next;
        head -> next = head -> next -> next;
        delete temp_for_delete;
        len--;
    }
}