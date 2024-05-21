//
// Created by Will Pelech, 3/10/2024
//Purpose: We were tasked with making bigUnsigned which is used
//to store unsigned integers

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class BigUnsigned{
    //output operator
    friend ostream& operator<<(ostream& os, const BigUnsigned& big);
    //equals operator
    friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
    //less that operator
    friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);
public:
    //constructor with a zero default value (if no parameter is passed in)
    //also no initilization list is required because we can use
    //vectors default constructor
    BigUnsigned(int val = 0){
        //initializes the vector to 0
        if (val == 0){
            digits = vector<int>{0};
            return;
        }
        while(val > 0){
            digits.push_back(val % 10);//pushes leading digit
            val /= 10;//goes to the next digit
        }
        }
    //constructor for string of digits passed in
    BigUnsigned(const string& str_dig){

        size_t first_dig = 0;//holds index of first nonzero digit
        //checks where the first digit is by ignoring leading zeros
        while(str_dig[first_dig] == '0'){
            first_dig++;
        }
        //loops through the non-leading zero digits
        for (size_t index = str_dig.size(); index > first_dig; index--) {
            //this calls a helper method dig_decipher
            //which converts a char to an int and stores it in digit
            int digit = dig_decipher(str_dig[index-1]);
            //checks that the digit is valid(helper method returns -1
            //for invalid digits)
            if (digit != -1) {
                    digits.push_back(digit);
                }

            }
            //this will check if the provided str is invalid and
            // assign the unsigned to zero if invalid
            if(empty(digits)){//alternative digits.size()==0
                digits.push_back(0);
            }
        }


    //+= operator
    BigUnsigned& operator+=(const BigUnsigned& rhs){

        size_t min_len;//will store the size of the smallest array

        //determines which unsigned is bigger and sets min_len to that
        if(digits.size() < rhs.digits.size()){
            min_len = digits.size();
        }else{
            min_len = rhs.digits.size();
        }
        //traverses the shorter index and adds entries
        for(size_t index = 0; index < min_len; index++){
            digits[index] = digits[index] + rhs.digits[index];
        }

        //the case when the rhs is bigger
        //it will add the remaining larger digits
        while(min_len < rhs.digits.size()){
            digits.push_back(rhs.digits[min_len]);
            min_len++;
        }
        //calls the private method normalize which normalizes the vector
        normalize();
        return *this;
    }
    //post increment operator
    BigUnsigned& operator ++ (){
        digits[0]++;//increments the lowest digit
        normalize();//makes sure the digits are correct
        return *this;
    }

    //pre-increment
    BigUnsigned operator++(int dummy){
        BigUnsigned temp(*this);//makes a coup of the original
        digits[0] += 1;//adds on to the unsigned vector
        normalize();//makes sure the digits are correct
        return temp;
    }
    //operator bool
    explicit operator bool() const {
        return digits.size() != 1 || digits[0] != 0;
    }

private:
    //private methods
    //converts char to int and returns -1 if the char is not a digit
    int dig_decipher(char num) {
        int x = -1;
        //makes a const vector with all chars having a index
        //corresponding to their value
        const vector<char> chars={'0','1','2','3','4','5','6','7','8','9'};
        //traverses the array to see if the char is in the array
        for(size_t index = 0 ; index < 10 ; index++){
            if(num == chars[index]){//index and char match
                x = index;
            }
        }
        return x;
    }
    //private method to make sure that every int is under 10
    void normalize(){

        int remainder = 0;
        //will go through every entry of digits
        for(size_t index = 0; index < digits.size(); index++) {

            if (remainder == 1){//if there is a remainder increment current
                digits[index] += remainder;
                remainder -= 1;
            }
            if(digits[index] >= 10){//checks if there is a remainder
                digits[index] -= 10;
                remainder++;
            }
        }
        //if there is a remainder at the end that needs to be added
        if (remainder > 0){
            digits.push_back(1);
        }
    }

    //private fields
    vector<int> digits;

};
//ptype for addition operator
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs);
//ptypes for all the comparison operators
bool operator !=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator <(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator <=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator >=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator >(const BigUnsigned& lhs, const BigUnsigned& rhs);



int main() {

    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;

    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;

    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;

    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;


    BigUnsigned big("987654321");

    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
}

//output operator
ostream& operator<<(ostream& os, const BigUnsigned& big){
    for(size_t index = big.digits.size();index > 0;index--){
        os << big.digits[index-1];
    }
    return os;
}

//addition operator
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs){
    BigUnsigned temp(lhs);
    temp += rhs;//calls += operator
    return temp;
}
//bool operator (friend)
bool operator ==(const BigUnsigned& lhs, const BigUnsigned& rhs){
    bool ret = true;
    //if the two are different sizes
    if(lhs.digits.size() != rhs.digits.size()) {
        ret = false;
    }else{
        //loops through both unsigned numbers
        for (size_t index = 0; index < lhs.digits.size();index++){
            //checks digit by digit to see they are different
            if(lhs.digits[index] != rhs.digits[index]){
                ret = false;
            }
        }
    }
    return ret;
}
//less than operator friend
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs){
    //if lhs is smaller
   if(lhs.digits.size() < rhs.digits.size()){
       return true;
   //if lhs is bigger then
   }else if (lhs.digits.size() > rhs.digits.size()){
       return false;

   }else{
       //compares the largest digits first until one is smaller
       for(size_t index = lhs.digits.size();index > 0;index--){
           if(lhs.digits[index-1] <  rhs.digits[index-1]){
               return true;
           }else if (lhs.digits[index-1] > rhs.digits[index-1]) {
               return false;
           }
       }
       //the digits are equal so will return false
       return false;
   }
}
//less than or equals operator
bool operator <=(const BigUnsigned& lhs, const BigUnsigned& rhs){
    return (lhs == rhs || lhs < rhs);
}
//greater than or equals operator
bool operator >=(const BigUnsigned& lhs, const BigUnsigned& rhs){
    return !(lhs < rhs);
}
//not equals operator
bool operator !=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
    return !(lhs == rhs);
}
//greater than operator
bool operator >(const BigUnsigned& lhs, const BigUnsigned& rhs){
    return!(lhs <= rhs);
}

