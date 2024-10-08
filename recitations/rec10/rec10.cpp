//
// Created by Will Pelech on 4/5/24.
//
#include <iostream>
#include <vector>
using namespace std;


class Instrument{
    friend ostream& operator << (ostream& os, const Instrument& inst){
        inst.display(os);
        return os;
    }

public:
    Instrument(){}
    virtual void makeSound() const=0;
    virtual void display (ostream& os)const=0;
    virtual void play()=0;

    };

void Instrument::makeSound() const{
    cout << "to make a sound... ";
}

//BRASS
class Brass:public Instrument{
public:
    Brass(unsigned size):mouthSize(size){}
    void makeSound() const final{
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " <<mouthSize <<endl;
    }
protected:
    unsigned gets() const{return mouthSize;}
private:
    unsigned mouthSize=0;
};

class Trombone:public Brass{
public:
    void display(ostream& os) const override{
        os << "Trombone: " << Brass::gets()<<endl;

    }
    void play() override{cout<<"Blat";}
    Trombone(unsigned size): Brass(size){
    }
};
class Trumpet : public Brass{
public:
    void display(ostream& os) const override{
        os << "Trumpet: " << Brass::gets()<<endl;
    }
    void play() override{cout<<"Toot";}
    Trumpet(unsigned size): Brass(size){}
};

//STRING
class String: public Instrument{
public:

    String(unsigned pitch):pitch(pitch){}
    void makeSound() const override{
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch <<endl;
    }
protected:
    unsigned getP()const{return pitch;}
private:
    unsigned pitch;
};
class Violin: public String{
    void display(ostream& os) const override{
        os << "Violin: " << String::getP() <<endl;
    }
    void play() override{cout<<"Screech";}
public:
    Violin(unsigned num): String(num){}
};
class Cello : public String{
    void display(ostream& os) const override{
        os << "Cello: " << String::getP()<<endl;

    }
    void play() override{cout<<"Squawk";}
public:
    Cello(unsigned num): String(num){}
};

//PERCUSSION
class Percussion: public Instrument{
public:
    Percussion(){}
    void makeSound() const override{
        Instrument::makeSound();
            cout<<"hit me!"<<endl;
        }

};
class Drum : public Percussion{
public:
    void display(ostream& os) const override{
        os << "Drum" <<endl;
    }
    Drum(){}
    void play() override{cout<<"Boom";}
};

class Cymbal : public Percussion{
public:
    void display(ostream& os) const override{
        os << "Drum" <<endl;
    }
    void play() override{cout<<"Crash";}
};



//MILL___________-
class MILL{
    friend ostream& operator <<(ostream& os, const MILL& mill){
        os << "The MILL has the following instruments:";
        if(mill.inventory.size()==0){
            os<< " None";
        }else{
            os<<endl;
            for(const Instrument* in: mill.inventory){
                if(in!= nullptr) {
                    in->display(os);
                }
            }
        }
        return os;
    }
public:
    Instrument* loanOut(){
        Instrument* inst= nullptr;
        for(size_t index = 0;index<inventory.size();index++){
            if(inventory[index]!= nullptr){
                inst=inventory[index];
                inventory[index]=nullptr;
                return inst;
            }
        }
        return inst;
    }
    MILL(){}
    void dailyTestPlay(){
        for(const Instrument* inst: inventory){
            if(inst!= nullptr) {
                inst->makeSound();

            }
        }
    }
    void receiveInstr(Instrument& inst){
        inst.makeSound();
        for(size_t index = 0; index < inventory.size();index ++) {
            if(inventory[index] == nullptr){
                inventory[index] = &inst;
                return;
            }
        }
        inventory.push_back(&inst);
    }
private:
    vector<Instrument*> inventory;
};


// Musician class as provided to the students. Requires an Instrument class.
//

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};
class Orch{
public:
    void addPlayer(Musician& musician){ orch.push_back(&musician);}
    void play(){
        for(size_t index = 0; index<orch.size();index++){
            orch[index]->play();
        }
        cout<<endl;
    }
private:
    vector<Musician*> orch;
};


int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12) ;
     Violin violin(567) ;

    cout << "Define the MILL -----------------------------------------------\n";
     MILL mill;
     cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
     mill.receiveInstr(trpt);
     mill.receiveInstr(violin);
     mill.receiveInstr(tbone);
     mill.receiveInstr(drum);
     mill.receiveInstr(cello);
     mill.receiveInstr(cymbal);
     cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
         << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
     Musician harpo("Harpo");
     Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
     groucho.testPlay();	 // Groucho doesn't have an instrument yet.

     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

     groucho.testPlay();
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();
     harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
        mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
     cout << mill << endl;

    //
    // PART TWO
    //

    cout << "\nP A R T  T W O\n";

    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;

}

