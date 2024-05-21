#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

class functor{
public:
    bool operator()(int num){
        return num%2==0;
    }
private:

};

void print_l(const list<int>& l){
    for(list<int>::const_iterator i =l.begin(); i!=l.end();++i){
        cout << *i <<" ";
    }
    cout << endl;
}
void print_l_r(const list<int>& l){
    for(int num: l){
        cout<<num<<" ";
    }
    cout<<endl;
}

void every_other(const list<int>& l){
    for(auto i =l.begin(); i!=l.end();++++i){
        cout << *i <<" ";
    }
    cout << endl;
}

list<int>::const_iterator find(const list<int>& l,int target){
    for(list<int>::const_iterator i = l.begin();i!=l.end();++i ){
        if(*i == target){
            return i;
        }

    }
    return l.end();
}

auto find_auto(const list<int>& l,int target){
    for(auto i = l.begin();i!=l.end();++i ){
        if(*i == target){
            return i;
        }

    }
    return l.end();
}
int isEven(int num){return num%2==0;}

list<int>::iterator ourFind(list<int>::iterator begin,list<int>::iterator end, int target){
    for(list<int>::iterator i = begin; i!=end;++i){
        if(*i==target){
            return i;
        }
    }
    return end;
}

template <class T,class U>
T ourFind(T begin,T end, U target){
    for(T i = begin; i!=end;++i){
        if(*i==target){
            return i;
        }
    }
    return end;
}


int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vec={1,3,4,9,6,7};
    for(int num:vec){
        cout<<num << " ";
    }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> my_l(vec.begin(),vec.end());
    for(int num:my_l){
        cout<<num << " ";
    }

    cout << "\n=======\n";


    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vec.begin() ,vec.end());
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for(size_t index = 0; index<vec.size(); index+=2){
        cout << vec[index] <<" ";
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//    for(size_t index = 0; index<my_l.size(); index+=2){
//        cout << my_l[index] <<" ";
//    }
//note linked list does not have a [] operator because of ineffiecienxy
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for(vector<int>::iterator it = vec.begin();it!=vec.end();it+=2){
        cout << *it << " ";
    }

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for(list<int>::iterator it =my_l.begin();it!=my_l.end();++++it){
        cout << *it << " ";
    }
    //notice how the pre increment only works

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    my_l.sort();
    for(list<int>::iterator it =my_l.begin();it!=my_l.end();++it){
        cout << *it << " ";
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    print_l(my_l);

    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    print_l_r(my_l);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    every_other(my_l);
    cout << "=======\n";


    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    auto var=find(my_l,7);
    cout <<*var <<endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    var=find_auto(my_l,7);
    cout <<*var <<endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    auto new_v= find(my_l,9);
    cout <<*new_v<<endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    new_v = (find_if(my_l.begin(), my_l.end(), isEven));
    cout <<*new_v<<endl;
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    functor func;
    new_v = (find_if(my_l.begin(), my_l.end(),func));
    cout <<*new_v<<endl;
    cout << "=======\n";

    // 17. Lambda
    cout << "Task 17:\n";
    auto new_v2 = (find_if(my_l.begin(), my_l.end(),[](int a)->bool{return a%2==0;}));
    cout<<*new_v2;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr= new int[6];
    copy(my_l.begin(),my_l.end(),arr);
    int* curs =arr;
    for (int i=0;i<6;i++) {
        cout << *(curs + i) << " ";
    }
    cout<<endl;
    delete []arr;

    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    auto var3=ourFind(my_l.begin(),my_l.end(),9);
    cout <<*var3 <<endl;
    cout << "=======\n";

    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    auto var4=ourFind(my_l.begin(),my_l.end(),2);
    cout <<*var4 <<endl;
    //6 is the end
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    vector<string> vect1;
    ifstream ifs("pooh-nopunc.txt");
    if(!ifs){
        cerr<<"not opened";
    }
    string word;
    while(ifs>>word){
        if(find(vect1.begin(),vect1.end(),word)==vect1.end()){
            vect1.push_back(word);
        }
    }
    ifs.close();
    cout<<vect1.size();
    for(string word: vect1){
        cout << word;
    }
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> vect2;
    ifstream ifs1("pooh-nopunc.txt");
    if(!ifs1){
        cerr<<"not opened";
    }
    string word1;
    while(ifs1>>word1){
        vect2.insert(word1);
    }
    ifs1.close();
    cout<<vect2.size();
    for(string word: vect2){
        cout << word;
    }
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string,vector<int>>wordMap;
    ifstream file("pooh-nopunc.txt");
    int index3=0;
    while(file>>word){
        wordMap[word].push_back(index3);
        index3++;
    }
    cout<<wordMap.size()<<endl;
    for(auto pair:wordMap){
        cout<<pair.first <<"[";
        for(int i : pair.second){
            cout<<i<<" ";
        }
        cout <<"]";
    }

    file.close();

    cout << "=======\n";
}

