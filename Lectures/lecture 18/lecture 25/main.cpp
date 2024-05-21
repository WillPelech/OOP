#include <iostream>
//started with vectors and unordered sets


using namespace std;

class IsEvenFunctor{
public:
    //function call operator
    bool operator() (int val){ return val%2==0;}

};
class isMultiple{


};
//similar to templating
void bar(auto what){

}

pair<int,bool> foo(){//could alos be auto
    //pair<int,bool> result {6,true};
    return make_pair(6,true);
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto imAlambda =[] { cout <<"h";};
    imAlambda();



    IsEvenFunctor aninstance;//define a variable that is an instance
    if (aninstance(28)){
        cout<<"28 is an even number";

    }else{
        cout<<"28 is not";
    }
    //first and second names of make pair pair


    auto [who,what] = foo();//}structured Unbinding in C++ 17

    //review -- lambda,instance of functor
    //we could just use the constructor to cretae a temporary instance
    //infinite number of functions
    //lambda expressions in C++ create a functor
    //auto must know  the types at compile time -> because C++ defines all types at compile time
    //do not use auto unless it really simplifies things
//
//    a,b = b,a;//swaps in python what will it do?
//    //
//    // this is how c++ does it
//    a,(b=b), a;// a becomes the value of the whole thing
//
//    swap(a,b);//function templated{works for everything}



}
//New topic
Node * listDup(Node* p){
    if(p==nullptr) return nullptr;
    return new Node {pp->};
}

