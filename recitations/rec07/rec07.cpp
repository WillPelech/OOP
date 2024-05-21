#include <iostream>
#include <string>
using namespace std;

int greatestCommonDivisor(int x, int y);
class Rational{
    //output and input operators
    friend ostream& operator<<(ostream& os,const Rational& rational);
    friend istream& operator>>(istream& is, Rational& rational);
    friend bool operator == (const Rational& lhs, const Rational& rhs);
    friend bool operator < (const Rational& lhs, const Rational& rhs);

    //private constructor
public:
    Rational(int num=0, int den=1):num(num),den(den){
        normalize();
    }
    void normalize(){
        int gcd = greatestCommonDivisor(abs(num),abs(den));
        if(den<0){
            den*=-1;
            num*=-1;
        }
        num /= gcd;
        den /= gcd;
    }
    //+= operator implement before +
    Rational& operator +=(const Rational& rhs){
        num = num * rhs.den + rhs.num * den;
        den = rhs.den * den;
        normalize();
        return *this;
    }

    Rational& operator ++() {
        num += den;
        normalize();
        return *this;
    }
    Rational operator ++(int dummy){
        Rational temp=*this;
        num+=den;
        normalize();
        return temp;
    }

    explicit operator bool() const{
        return !(num==0);
    }
    //+ operator


    //member ++

    //operator bool
private:
    int num;
    int den;
};
//non friend ptypes !=,<=,> and >=
bool operator == (const Rational& lhs, const Rational& rhs);
bool operator >=(const Rational& lhs, const Rational& rhs);
Rational operator + (const Rational& rhs,const Rational& lhs);
bool operator < (const Rational& lhs, const Rational& rhs);
bool operator >(const Rational& lhs, const Rational& rhs);
bool operator >=(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
Rational& operator --(Rational& lhs);
Rational operator --(Rational& lhs,int dummy);
bool operator <=(const Rational& lhs, const Rational rhs);
int main()
{

    Rational a, b;

    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;

    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why shouldn't it compile?
    cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}
Rational& operator --(Rational& lhs){
    lhs+=-1;
    return lhs;
}
Rational operator --(Rational& lhs,int dummy){
    Rational copy=lhs;
    lhs+=-1;
    return copy;
}
Rational operator + (const Rational& rhs,const Rational& lhs){
    Rational lhs_temp = lhs;
    lhs_temp += rhs;
    return lhs_temp;
}
//non member == operator friend
bool operator == (const Rational& lhs, const Rational& rhs){
    return lhs.num == rhs.num && lhs.num == rhs.num;
}
//< operator non friend
bool operator < (const Rational& lhs, const Rational& rhs){
    return lhs.num * rhs.den < rhs.num * lhs.den;
}
bool operator!=(const Rational& lhs, const Rational& rhs){
    return !(lhs==rhs);
}
bool operator <=(const Rational& lhs, const Rational rhs){
    return lhs < rhs || lhs == rhs;
}
bool operator >(const Rational& lhs, const Rational& rhs){
    return !(lhs<=rhs);
}
bool operator >=(const Rational& lhs, const Rational& rhs){
    return lhs > rhs || lhs == rhs;
}

//non member --
ostream& operator<<(ostream& os,const Rational& rational){
    os << rational.num << "/" << rational.den;
    return os;
}
istream& operator >> (istream& is, Rational& rational){
    char div;
    is >> rational.num >> div >>rational.den;
    rational.normalize();
    return is;
};