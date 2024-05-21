/*
  rec03_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account{
    string name;
    int number;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Accounts{
    friend ostream& operator<< (ostream& os, const Accounts& account);
public:
    Accounts(const string& n,int a):name(n),number(a){}
    const string& getName() const {
        return name;
    }
    int getNumber() const{
        return number;
    }
private:
    string name;
    int number;
};
ostream& operator<< (ostream& os, const Accounts& account){
//    os<<account.getName()<<" "<<account.getNumber();
    os<<account.name<<" "<<account.number;
    return os;
}

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes
class Transaction{
    friend ostream& operator <<(ostream& os, const Transaction& transaction);
public:
    Transaction(string name, int amount):type(name),amount(amount) { }
private:
    string type;
    int amount;

};
ostream& operator <<(ostream& os, const Transaction& transaction){
    os<< transaction.type<<": "<< transaction.amount<<" ";
    return os;
}

class Tran_Account{
    friend ostream& operator <<(ostream& os, const Tran_Account& transaction);
public:
    Tran_Account (const string& name,int num ):name(name),acc(num){}
    void deposit(int amount, vector<Transaction>& history){
        balance+=amount;
        Transaction new_transaction("Deposit",amount);
        history.push_back(new_transaction);
    }
    void withdrawal(int amount,vector<Transaction>& history){
        balance+=amount;
        Transaction new_transaction("Deposit",amount);
        history.push_back(new_transaction);
    }
    int get_num(){
        return acc;
    }
    void set_num(const string& type, int amount){
        if (type=="Deposit"){
            balance+=amount;
        }else{
            balance-=amount;
            if (balance<0){
                cout<<"Account is less than zero"<<endl;
                balance=0;
            }
        }
        Transaction new_transaction(type, amount);
        history.push_back(new_transaction);
    }
private:
    vector<Transaction> history;
    string name;
    int acc;
    int balance;
};
ostream& operator <<(ostream& os, const Tran_Account& account) {

    os << account.name << "Balance:" << account.balance << "Transactions:";
    for (size_t index = 0; index < account.history.size(); index++) {
    os<<account.history[index];
    }
    cout<<endl;
    return os;
}

// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)
class Tran_Accounts{
    friend ostream& operator <<(ostream& os, const Tran_Accounts& transaction);

public:

    Tran_Accounts (const string& name,int num ):name(name),acc(num){}
    class Transactions{
        friend ostream& operator <<(ostream& os, const Transactions& transaction);
    public:
        Transactions(string name, int amount):type(name),amount(amount) { }
    private:
        string type;
        int amount;

    };
    void deposit(int amount, vector<Transaction>& history){
        balance+=amount;
        Transaction new_transaction("Deposit",amount);
        history.push_back(new_transaction);
    }
    void withdrawal(int amount,vector<Transaction>& history){
        balance+=amount;
        Transaction new_transaction("Deposit",amount);
        history.push_back(new_transaction);
    }
    int get_num(){
        return acc;
    }
    void set_num(const string& type, int amount){
        if (type=="Deposit"){
            balance+=amount;
        }else{
            balance-=amount;
            if (balance<0){
                cout<<"Account is less than zero"<<endl;
                balance=0;
            }
        }
        Transaction new_transaction(type, amount);
        history.push_back(new_transaction);
    }
private:
    vector<Transaction> history;
    string name;
    int acc;
    int balance;
};
ostream& operator <<(ostream& os, const Tran_Accounts::Transactions& transaction){
    os<< transaction.type<<": "<< transaction.amount<<" ";
    return os;
}

ostream& operator <<(ostream& os, const Tran_Accounts& account) {

    os << account.name << "Balance:" << account.balance << "Transactions:";
    for (size_t index = 0; index < account.history.size(); index++) {
        os<<account.history[index];
    }
    cout<<endl;
    return os;
}


// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)
class Tran_Accounts1{
    class Transactions1;
    friend ostream& operator <<(ostream& os, const Tran_Accounts1& transaction);
    friend ostream& operator <<(ostream& os, const Tran_Accounts1::Transactions1& transaction);
public:

    void deposit(int amount, vector<Transaction>& history){
        balance+=amount;
        Transaction new_transaction("Deposit",amount);
        history.push_back(new_transaction);
    }
    void withdrawal(int amount,vector<Transaction>& history){
        balance+=amount;
        Transaction new_transaction("Deposit",amount);
        history.push_back(new_transaction);
    }
    int get_num(){
        return acc;
    }
    void set_num(const string& type, int amount){
        if (type=="Deposit"){
            balance+=amount;
        }else{
            balance-=amount;
            if (balance<0){
                cout<<"Account is less than zero"<<endl;
                balance=0;
            }
        }
        Tran_Accounts:Transactions1 new_transaction(type, amount);
        history.push_back(new_transaction);
    }
private:
    Tran_Accounts1 (const string& name,int num ):name(name),acc(num){}
    class Transactions1{
        friend ostream& operator <<(ostream& os, const Transactions1& transaction);
    public:
        Transactions1(string name, int amount):type(name),amount(amount) { }
    private:
        string type;
        int amount;
    };
    vector<Transactions1> history;
    string name;
    int acc;
    int balance;
};
ostream& operator <<(ostream& os, const Tran_Accounts1::Transactions1& transaction){
    os<< transaction.type<<": "<< transaction.amount<<" ";
    return os;
}

ostream& operator <<(ostream& os, const Tran_Accounts1& account) {

    os << account.name << "Balance:" << account.balance << "Transactions:";
    for (size_t index = 0; index < account.history.size(); index++) {
        os<<account.history[index];
    }
    cout<<endl;
    return os;
}

int main() {

    // Task 1: account as struct
    //      1a
    string name;
    int acc_num;
    vector<Account> accounts;
    Account new_account;
    cout << "Task1a:\n";
    ifstream file("accounts.txt");
    if(!file) {
        cerr << "the file failed to open";
        exit(1);
    }
    while(file>>name>>acc_num){
        new_account.name=name;
        new_account.number=acc_num;
        accounts.push_back(new_account);
    }
    file.close();
    for (size_t index=0;index<accounts.size();index++){
        cout<<accounts[index].name<<" ";
    }
    cout<<endl;
    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    accounts.clear();
    fstream file_2("accounts.txt");
    if(!file_2) {
        cerr << "the file failed to open";
        exit(1);
    }
    while(file>>name>>acc_num){
       Account new_account{name,acc_num};
       accounts.push_back(new_account);
    }
    for (size_t index=0;index<accounts.size();index++){
        cout<<accounts[index].name<<" ";
    }
    file.close();






    //==================================
    // Task 2: account as class

    //      2a
    vector<Accounts> vf;
    vector<Accounts> vf1;
    vector<Accounts> vf2;
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";

    file.open("accounts.txt");
    if(!file) {
        cerr << "the file failed to open";
        exit(1);
    }
    while(file>>name>>acc_num){
        Accounts new1(name,acc_num);
        vf.push_back(new1);
    }
    for (size_t index=0;index<vf.size();index++){
        cout<<vf[index].getName()<<" "<<vf[index].getNumber()<<" ";
    }
    file.close();





    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";

    for (size_t index=0;index<vf.size();index++){
        cout<<vf[index];
    }

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    for (size_t index=0;index<vf.size();index++){
        cout<<vf[index];
    }
    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    file.open("accounts.txt");
    if(!file) {
        cerr << "the file failed to open";
        exit(1);
    }
    while(file>>name>>acc_num){
        vf1.push_back(Accounts(name,acc_num));
    }
    for (size_t index=0;index<vf1.size();index++){
        cout<<vf1[index]<<" "<<vf1[index];
    }
    file.close();

    cout<<endl;

    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    file.open("accounts.txt");
    if(!file) {
        cerr << "the file failed to open";
        exit(1);
    }
    while(file>>name>>acc_num){
        vf2.emplace_back(name,acc_num);
    }
    for (size_t index=0;index<vf2.size();index++){
        cout<<vf2[index]<<" "<<vf2[index];
    }
    file.close();

    cout<<endl;

    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";




    vector<Tran_Account> trans_accounts;
    string first_word;
    string second;
    int num1;
    int num2;
    ifstream tran_file("transactions.txt");
    if (!tran_file){
        cerr<<"NO FILE";
        exit(1);
    }
    while(tran_file>>first_word){
        if(first_word=="Account"){
            tran_file>>second>>num1;
            //name and num
            trans_accounts.push_back(Tran_Account(second,num1));

        }else{
            tran_file>>num1>>num2;
            for (size_t index=0;index<trans_accounts.size();index++){
                if (trans_accounts[index].get_num()==num1){
                    trans_accounts[index].set_num(first_word,num2);
                }
            }



        }

    }
    for (size_t in=0;in<trans_accounts.size();in++){
        cout<<trans_accounts[in];
    }


    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";


    trans_accounts.clear();
    vector<Tran_Accounts> trans_accounts1;
    ifstream tran_file1("transactions.txt");
    if (!tran_file1){
        cerr<<"NO FILE";
        exit(1);
    }
    while(tran_file1>>first_word){
        if(first_word=="Account"){
            tran_file1>>second>>num1;
            //name and num
            trans_accounts1.push_back(Tran_Accounts(second,num1));

        }else{
            tran_file1>>num1>>num2;
            for (size_t index=0;index<trans_accounts1.size();index++){
                if (trans_accounts1[index].get_num()==num1){
                    trans_accounts1[index].set_num(first_word,num2);
                }
            }



        }

    }
    for (size_t in=0;in<trans_accounts1.size();in++){
        cout<<trans_accounts1[in];
    }

    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";
    trans_accounts.clear();
    vector<Tran_Accounts> trans_accounts2;
    ifstream tran_file2("transactions.txt");
    if (!tran_file2){
        cerr<<"NO FILE";
        exit(1);
    }
    while(tran_file2>>first_word){
        if(first_word=="Account"){
            tran_file2>>second>>num1;
            //name and num
            trans_accounts2.push_back(Tran_Accounts(second,num1));

        }else{
            tran_file2>>num1>>num2;
            for (size_t index=0;index<trans_accounts1.size();index++){
                if (trans_accounts1[index].get_num()==num1){
                    trans_accounts1[index].set_num(first_word,num2);
                }
            }



        }

    }
    for (size_t in=0;in<trans_accounts1.size();in++){
        cout<<trans_accounts2[in];
    }

}