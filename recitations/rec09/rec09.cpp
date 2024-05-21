//
// Created by Will Pelech on 3/29/24.
//
#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
    //output operator does not work for derived classes
    friend ostream& operator <<(ostream& os,const PrintedMaterial& p);
public:

    PrintedMaterial(unsigned numberOfPages=0):numberOfPages(numberOfPages){ }
    virtual void displayNumPages() const =0;

protected:
    unsigned getNum() const{return numberOfPages;}
private:
    unsigned numberOfPages;
};
void PrintedMaterial::displayNumPages() const {
    cout << numberOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages=0): PrintedMaterial(numPages){}
    void displayNumPages() const override{
        cout <<"Pages: "<< PrintedMaterial::getNum() << endl;
    }
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages=0): PrintedMaterial(numPages){}

private:
};


class TextBook : public Book {
public:

    TextBook(unsigned numPages=0, unsigned index=0):Book(numPages)
            ,numOfIndexPages(index){}
    void displayNumPages() const override{
        cout <<"IndexPages: "<< numOfIndexPages<<", Pages: ";
        PrintedMaterial::displayNumPages();
    }
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages=0):Book(numPages){}
    void displayNumPages() const override{
        cout<<"Novel Pages: ";
        PrintedMaterial::displayNumPages();
    }
private:
};

void displayNumPages(PrintedMaterial& pm){
    pm.displayNumPages();
}

// tester/modeler code
int main() {
    TextBook text(12);
    Novel novel(10);
    Magazine mag(8);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();

//    cout << text << endl;
//    cout << novel << endl;
//    cout << mag << endl;



    // PrintedMaterial pm = text;
    //pm.displayNumPages();// notice how it is sliced

//    PrintedMaterial* pmPtr=&text;
//    pmPtr->displayNumPages();

    displayNumPages(text);
    displayNumPages(novel);
    displayNumPages(mag);

    //ptrs to prevent slicing
    vector<PrintedMaterial*> prints;
    prints.push_back(&text);
    prints.push_back(&novel);
    prints.push_back(&mag);

    for(const PrintedMaterial* p: prints){
        p->displayNumPages();
    }
}

ostream& operator <<(ostream& os,const PrintedMaterial& p){
    os<<p.numberOfPages<<endl;
}

//"wont compile because the constructor is for PM which cant instantiate instances
//of PM