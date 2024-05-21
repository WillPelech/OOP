//
// Created by Will Pelech on 4/24/24.
//Hw 09 implementing a polynomial class

#ifndef HW09_POLYNOMIAL_H
#define HW09_POLYNOMIAL_H
#include <iostream>

class Polynomial{
    // this is the output operator
    friend std::ostream& operator <<(std::ostream& os, const Polynomial& poly);
    //equality operator
    friend bool operator==(const Polynomial& rhs,const Polynomial& lhs);

public:
    //default constructor
    Polynomial();
    //copy constructor
    Polynomial(const Polynomial& other);
    //constructor which takes vector as parameter
    Polynomial(std::vector<int> vec);
    //destructor for polynomial
    ~Polynomial();
    //addition assignment operator
    Polynomial& operator+=(const Polynomial& other);
    //assignment operator
    Polynomial& operator=(const Polynomial& rhs);
    //evaluates a Polynomial using horners method
    int evaluate(int val) const;
    //auxillary function to get rid of leading zeros
    void leading_zeros();
private:
    //clears the whole list and takes care of heap
    void clear();

    // this holds the degree of the polynomial
    struct Degree{
        int coeff;
        Degree* next;
    };
    //private fields
    Degree* head;
    size_t len;
};
//non member function which make calls to member functions
Polynomial operator + (const Polynomial& lhs, const Polynomial& rhs);
//inequality operator
bool operator!=(const Polynomial& rhs,const Polynomial& lhs);

#endif //HW09_POLYNOMIAL_H
