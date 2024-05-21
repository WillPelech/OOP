/*
  rec14_starter code
 */

#include <iostream>
#include <vector>
#include <algorithm>  // max
using namespace std;


// Node type for the linked list
struct Node {
    int data = 0;
    Node* next = nullptr;
};

// Node type for the binary tree
struct TNode {
    int data = 0;
    TNode* left = nullptr;
    TNode* mid = nullptr;
    TNode* right = nullptr;
};



/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);


//
// Your functions go here
//
//   Task 1 function:
Node* listSum(const Node* rhs, const Node* lhs){

    if(rhs== nullptr && lhs== nullptr){
        return nullptr;
    }
    else if(rhs == nullptr){
        return new Node{lhs->data, listSum(nullptr,lhs->next)};
    }
    else if(lhs == nullptr){
        return new Node{rhs->data, listSum(rhs->next, nullptr)};
    }
    else {
        return new Node{rhs->data + lhs->data,
                        listSum(rhs->next, lhs->next)};
    }

}
//   Task 2 function:
int treeMax(TNode* head){
    if(head== nullptr){
        throw "not valid tree";
    }
//    if(!head->right and !head->left and !head->mid){
//        return head->data;
//    }
//    //ac
//    if(!head->right and !head->left){
//        return max(head->data, treeMax(head->mid));
//    }else if(!head->right and !head->mid){
//        return max(head->data, treeMax(head->left));
//    }else if(!head->left and !head->mid){
//        return max(head->data, treeMax(head->right));
//    }else if(!head->right){
//        return max(head->data,max(treeMax(head->left), treeMax(head->mid)));
//    }else if(!head->left){
//        return max(head->data,max(treeMax(head->right), treeMax(head->mid)));
//    } else if(!head->mid) {
//        return max(head->data, max(treeMax(head->left), treeMax(head->right)));
//    }else{
//        return max(head->data, max(treeMax(head->left), max(treeMax(head->right),treeMax(head->mid))));
//    }

    if(!head->right && !head->left && !head->mid){
        return head->data; }
    int hd=head->data;
    if(head->left){
        hd=max(hd, treeMax(head->left));
    }
    if(head->right){
        hd=max(hd, treeMax(head->right));
    }
    if(head->mid){
        hd=max(hd, treeMax(head->mid));
    }
    return hd;


}

//   Task 3 function:
bool palindrome(char s[],int n){
    if(n<=1) return true;//the last character
    if(s[0] == s[n-1]){
        return palindrome(s+1,n-2);
    }else{
        return false;
    }

}
//   Task 4 function:
bool parity(int n){
    if(n==0){
        return true;
    }
    if(n==1){
        return false;
    }
    if(n%2==0){
        return parity(n/2);
    }else{
        return !(parity(n/2));
    }

}
//   Task 5 function:
int towers(int n, char start, char target, char spare) {
    if (n == 0) return 0;
    if (n == 1) {
        return 1;
    } else{
        return towers(n - 1, start, spare, target) +
               towers(n - 1, spare, target, start)+1;
    }
}

void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n/2);
        cout << 'b';
        mystery(n/2);
    }
    cout << 'c';
}

int main() {
    // We have provided some test code to save you time. Certainly fee
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({2, 7, 1, 8});
    cout << "List (l1): ";
    listPrint(l1);

    Node* l2 = listBuild({9, 1, 4, 1});
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({3, 1, 4, 1, 5, 9});
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);



    // Task 2:
    TNode a{1}, b{2}, c{4}, d{-8, &a, &b, &c}, e{-16}, f{-32, &d, &e};
    cout << "treeMax(&f): " << treeMax(&f) << endl;

    // How do you keep this from crashing? try/catch! Here in main!
//    try {
//        cout << treeMax(nullptr) << endl;
//    }catch(){
//        cout<<"pause";
//    }


    // Task 3:
    cout << "\n==============\n"
         << "#3) Testing palindrome\n";
    cout << boolalpha
         << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
         << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
         << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
         << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;

    // Task 4:
    cout << "\n==============\n"
         << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }
//
//
//
    // Task 5:
    cout << "\n==============\n"
         << "#5) How many moves are required for various sized towers?";
    for (int i = 1; i < 30; ++i) {
        cout << "towers(" << i << ", 'a', 'b', 'c'): "
             << towers(i, 'a', 'b', 'c') << endl;
    }

//


}



//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr) {
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
}

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        result = new Node{vals[index-1], result};
    }
    return result;
}
