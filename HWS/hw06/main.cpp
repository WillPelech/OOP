//
// Created by Will Pelech on 3/9/24.
//
/*
  bigUnsigned_begin.cpp
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;



// Put your class and all function definitions here.
class BigUnsigned{
    friend ostream& operator>>(ostream& os, const BigUnsigned& big);
    friend bool operator ==(const BigUnsigned& lhs, const BigUnsigned& rhs);
    friend bool operator <(const BigUnsigned& lhs, const BigUnsigned& rhs);
public:
    BigUnsigned(){digits=vector<int>{0};}
    BigUnsigned(int val=0){
        if (val==0){
            digits=vector<int>{0};
            return;
        }
        while(val>0){
            digits.push_back(val%10);
            val/=10;
        }
    }

    BigUnsigned(const string& str_dig){
        if(dig_decipher(str_dig[0]) !=-1){
            //will check for the first nonzero term
            bool nonzero=false;
            for(size_t index= digits.size()-1; index > 0;index--){
                if(nonzero) {

                    digits.push_back(dig_decipher(str_dig[index]));
                }else{
                    if(dig_decipher(str_dig[index])!=0){
                        nonzero = true;
                        digits.push_back(dig_decipher(str_dig[index]));
                    }

                }
            }
        }else{
            cerr << "This is an invalid digit" << endl;
        }
    }

    int dig_decipher(char num) {
        int x = -1;
        const vector<char> chars={'0','1','2','3','4','5','6','7','8','9'};
        for(size_t index = 0; index < 10;index++){
            if(num == digits[index]){
                x = index;
            }
        }
        return x;
    }
    void normalize(){
        int remainder = 0;
        for(size_t index = 0; index < digits.size(); index++) {
            remainder=digits[index]/10;
            if (index + 1 != digits.size() && remainder != 0) {
                digits.push_back(remainder);
            } else {
                digits[index + 1] += remainder;
                remainder = 0;
            }
        }
    }

    BigUnsigned& operator+=(const BigUnsigned& rhs){
        size_t min_len;
        if(digits.size()<rhs.digits.size()){
            min_len= digits.size();
        }else{
            min_len = rhs.digits.size();
        }
        for(size_t index = 0; index < min_len; index++){
            digits[index]=digits[index]+rhs.digits[index];
        }
        normalize();
        return *this;

    }
    BigUnsigned& operator ++ (){
        *this+=BigUnsigned(1);
        return *this;
    }
    //returns the copy of the original
    BigUnsigned operator ++(int dummy){
        BigUnsigned temp(*this);
        *this+=1;
        normalize();
        return temp;
    }

private:
    vector<int> digits;

};

BigUnsigned operator +(const BigUnsigned& lhs, const BigUnsigned& rhs){
    BigUnsigned temp(lhs);
    temp+=rhs;
    return temp;
}

//ptypes
bool operator !=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator <(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator <=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator >=(const BigUnsigned& lhs, const BigUnsigned& rhs);
bool operator >(const BigUnsigned& lhs, const BigUnsigned& rhs);


/*
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
*/
bool operator ==(const BigUnsigned& lhs, const BigUnsigned& rhs){
    bool ret = true;
    if(lhs.digits.size()!=rhs.digits.size()) {
        ret = false;
    }else{
        for (size_t index = 0; index < lhs.digits.size();index++){
            if(lhs.digits[index]!=rhs.digits[index]){
                ret=false;
            }
        }
    }
    return ret;
}


ostream& operator>>(ostream& os, const BigUnsigned& big){
    for(size_t index = big.digits.size();index >=0;index--){
        os<<big.digits[index]<<"";
    }
    return os;
}