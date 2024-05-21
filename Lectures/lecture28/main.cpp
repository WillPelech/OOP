#include <iostream>

//the address is likely to have memory we can use
#include <vector>

using namespace std;




void foo(){
        vector<int> v;

        v.push_back(28);
        //=============

        //what happens here
        v[17]=42;
        v.at(17)=42;//threw an exception
        return;
}

void bar(){
    foo();
}
int main(){
    try{
        //foo();//runtime decision just know that
        bar();
    }
//    catch(out_of_range& ex){//then checks second
//        cout<<ex.what();
//    }
    catch(exception& ex){//satisfy first
        cout << ex.what();//not very descriptive
    }
    //what is a
}
//C++ exception hiearchy
//out of range and exception are objects with virtual what methods so we should use &
