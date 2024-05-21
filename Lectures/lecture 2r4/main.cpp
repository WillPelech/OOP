#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
//
//char* myFind(char* start, char* stop, char target){
//    for(char* p = start; p!= stop; ++p){
//        if(*p == target){
//            return p;
//        }
//    }
//    return stop;
//}
list<int>::itr
bool isEven(int val){
    return val%2==0;
}


template<class InputIterator, class T>
InputIterator myFind (InputIterator first, InputIterator last, const T& val)
{
    while (first!=last) {
        if (*first==val) return first;
        ++first;
    }
    return last;
}
//would have to know how to express a parameter type
T find_if(li.begin,li.end(),isEven//address){



} //have to write function

int main() {
    list<int> li{3,5,7,11,12,1};
    std::cout << "Hello, World!" << std::endl;
    return 0;
}



