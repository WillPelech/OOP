//
// Created by Will Pelech on 3/6/24.
//
class Complex{
    //dont want to make copy on way out

    Complex& operator+=(const Complex& rhs){
       real += rhs.real;
       imag += rhs.imag;
       return *this;
    }
    //cant return a local object by reference
    Complex operator+(const Complex& lhs , const Complex& rhs){
        Complex result(lhs);
        result+=rhs;
        return result;
    }
    //as method
    Complex& operator ++ (){
        ++real;
        return *this;
    }
    operator bool() const{
        return real==0 || imag==0;
    }
    //constructor or conversion operator
    //function call preincrement
    //unary as a method
    //c1.operator()
    //operator++(c1)
    //operator++(0){
    // c1++;
    // c1.operator(0);

};