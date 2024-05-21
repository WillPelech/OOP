
#include <iostream>


class Vector{

private:
    Vector(){
        theSize=0;
        theCapacity=0;
        //good possibility
        data = nullptr;
    }


    // to first single element in the array
    //big 3: dest, cop cons, assignment
    //pass by reference instead of by value, bc of infinite sequence
    explicit Vector (const Vector& rhs){
        theSize = rhs.theSize;
        theCapacity= rhs.theCapacity;
        data = new int[theCapacity];
        for (size_t index =0 ; index < theSize; ++index){
            //(data + index) = *(rhs.data + index);
            data[index] = rhs.data[index];
        }
    }
    //assignment operator
    //difference initiaalize constructor, vs overriding
    Vector& operator=(const Vector& rhs){
        //0.self asisgnment check
        //this is a pointer
        if(&rhs != this) {//not doing self
            //1.free up heap
            delete[] data;
            //2. allocate and copy

        }

            //3. return yourself
            return *this;
    }

    //legit the size = the capacity = size
    //free up the heap
    ~Vector(){
    //delete data; not right bc  only first element in data
        delete[] data;
    }
    void push_back(int val) {
        // In case we defined a vector with zero capacity
        if (theCapacity == 0) {
            ++theCapacity;
            data = new int[theCapacity];
        }
        // Have we run out of room?
        if (theSize == theCapacity) {
            int* oldData = data;
            data = new int[2*theCapacity];
            theCapacity *= 2;
            for (size_t i = 0; i < theSize; ++i) {
                data[i] = oldData[i];
            }
            delete [] oldData;
        }

        data[theSize] = val;
        ++theSize;
    }
    //square bracket
    int operator[] (size_t index) const{return data[index];}
    int& operator[](size_t index){ return data[index];}

    size_t size() const{return theSize;}
    void pop_back(){--theSize;}
    const int* begin() const{
        return &data[0];
    }
    const int* end() const{
        //square brackets has precedence of address of
        return &data[theSize];
    }

private:
    int* data;
    size_t theSize;
    size_t theCapacity;

};
//pointer to const cant modify what is pointing to
int main(){
    //size 0 def, cap small default is 0,s
    Vector v();
}
//what is the
//v[0]=100;
// other way of doing this is v.operator[](i)
//v = Vector(17)
//creates a temporary vector, explicit keyword for no accidents

//ranged for code
//address of one after the last for end()
//for(int val:
//for (int* p = v.begin; p != v.end(); p++){
//
//}
