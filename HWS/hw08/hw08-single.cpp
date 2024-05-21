#include <iostream>
#include <vector>
# include <string>

using namespace std;
class Noble;
class Lord;


//pure virtual class
class Protector{
public:
    //constructor
    Protector(const string& name, double num);
    //getters and setters
    const string& get_name() const;
    double get_strength() const;
    bool get_hired() const;
    virtual void set_strength(double new_s);
    void set_hiring(Lord* ldptr);
    const string& lord_name() const;//this function gets lords name

    bool runaway();

    virtual void display() const=0;//I think that every subclass should
//implement a display function
private:
    //private data members
    string name;
    Lord* lptr;
    double strength;
};


class Warrior:public Protector{
public:
    Warrior(const string& name, double num);
protected:
    void display() const override;
};

class Archer: public Warrior{
public:
    Archer(const string& name, double num);
protected:
    void display() const override;
};

class Swordsman: public Warrior{
public:
    Swordsman(const string& name, double strength);
    void display() const override;
};

class Wizard: public Protector{
public:
    Wizard(const string& name, double strength);
    void display() const override;
};




//another pure virtual class
class Noble{
    friend ostream& operator << (ostream& os, const Noble& noble);
public:
    //constructor
    Noble(const string& name);
    //public getters
    const string& get_name() const;
    virtual double get_strength() const = 0;
    bool get_alive() const;
    //public battle function
    void battle(Noble& other_noble);

protected:

    //method called in the output operator needs to be overriden
    //by every subclass
    virtual ostream& display(ostream& os) const=0;
    //protected setters
    bool set_alive(bool al);
    virtual void set_strength(double multiplier)=0;
    //auxillary ratio method
    double ratio(double weaker, double stronger);
    //protected battle_cry method every Lord uses when defending
    void virtual battle_cry() const=0;

private:
    //kill method
    virtual void kill()=0;

    string name;
    bool alive;
};


class Lord : public Noble{
public:
    //constructor for Lord
    Lord(const string& name);
    //hire and fire methods
    bool hires(Protector& protector);
    bool fires(Protector& protector);
    //overridden get strength method
    double get_strength() const override;
    //displays the warrior defending battle cry
    void virtual battle_cry() const;
    //removes a protector from the warriors army
    bool remove_protector(const Protector *protector);
protected:
    //method called by output operator
    ostream& display(ostream& os)  const override;
    //protected setter
    void set_strength(double multiplier) override;

private:
    //sets alive to false and sets the army strength to zero
    void kill() override;
    //finds the index of a protector in the Lord's army
    size_t find_protector(const Protector *protector);
    //private field
    vector<Protector*> army;
};



class PersonWithStrengthToFight: public Noble{
public:
    //constructor for PersonWithStrength to fight
    PersonWithStrengthToFight(const string& name, double strength);
    //public getter
    double get_strength() const override;
    //battle cry method
    void virtual battle_cry() const;
protected:
    // called in the output operator
    ostream& display(ostream& os) const override;
    //sets strength of a ratio
    void set_strength(double multiplier) override;
private:
    //sets strength to zero and alive to false
    void kill() override;
    double strength;
};

int main() {

    Lord sam("Sam");
    Archer samantha("Samantha", 200);

    sam.hires(samantha);

    Lord joe("Joe");

    PersonWithStrengthToFight randy("Randolf the Elder", 250);

    Lord janet("Janet");

    Swordsman hardy("TuckTuckTheHardy", 100);

    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "\n==========\n";

    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "==========\n";

}

//constructors
Protector::Protector(const string& name, double num):
name(name),strength(num),lptr(nullptr){}
Warrior::Warrior(const string& name, double num):Protector(name, num){}
Archer::Archer(const string& name, double num): Warrior(name,num){}
Swordsman::Swordsman(const string& name, double strength):
        Warrior(name,strength){}
Wizard::Wizard(const string& name, double strength):Protector(name,strength){}

//protector getter and setter methods
//gets name
const string& Protector::get_name() const{
    return name;
}
//sets hiring
void Protector::set_hiring(Lord *ldptr) {
    lptr = ldptr;
}
//sets strength of a protector
void Protector::set_strength(double new_s) {
    strength=new_s;
}
//gets strength of a protector
double Protector::get_strength() const {
    return strength;
}

//gets the hiring status of a protector
bool Protector::get_hired() const{
    return lptr;
}
//gets the name of the warrior that the protector has
//this method can only be called when the warrior has a lord
const string& Protector::lord_name() const{
    return lptr->get_name();
}

//runaway method
bool Protector::runaway(){
    if (lptr != nullptr) {//makes sure the warrior has a noble
        cout << name << " flees in terror, abandoning his lord, "
             << lptr->get_name() << endl;
    }

    if (lptr->remove_protector(this)) {//removes the warrior
        lptr = nullptr;
        return true;
    }
    return false;
}

//display methods

//shared text that all warriors say
void Warrior::display() const {
    cout<<get_name() << " says: Take that in the "
                  "name of my lord, "<< lord_name()<<endl;
}
//arcber battle display
void Archer::display() const {
    cout << "TWANG! ";
    Warrior::display();

}
//wizard battle display
void  Wizard::display() const {
    cout<< "POOF"<<endl;

}
//swordsmen battle display
void Swordsman::display() const {
    cout<< "CLANG! ";
    Warrior::display();
}




//noble methods

//constructors for Noble and derived classes
Noble::Noble(const string& name):name(name),alive(true) {}
Lord::Lord(const string& name): Noble(name){}
PersonWithStrengthToFight::PersonWithStrengthToFight
        (const std::string &name,double strength): Noble(name),strength(strength) {

}

//getters and setters
// get_strength methods
bool Noble::get_alive() const{
    return alive;
}

bool Noble::set_alive(bool al) {
    alive=al;
}

const string& Noble::get_name() const{
    return name;
}

double Lord::get_strength() const{
    double total_strength = 0;
    for (const Protector * protector : army) {
        total_strength += protector->get_strength();
    }
    return total_strength;
}

void PersonWithStrengthToFight::set_strength(double multiplier) {
    strength = strength * multiplier;
}

void Lord::set_strength(double multiplier) {
    //warrior off the ratio
    for (Protector* protector : army) {//goes through and changes evry
        //warrior off the ratio
        double new_strength = (protector->get_strength() * (multiplier));
        protector -> set_strength(new_strength);
    }
}

bool Lord::hires(Protector &protector) {
    if (!get_alive()) {
        cout << get_name() <<
             " failed to hire " << protector.get_name() << endl;
        return false;
    }//checks the warrior is alive
    if (protector.get_hired()) {//makes sure the warrior isn't dead
        cout << get_name() <<
             " failed to hire " << protector.get_name() << endl;
        return false;
    } else {

        army.push_back(&protector);//adds warrior to army
        protector.set_hiring(this);//sets noble ptr
        return true;
    }
}



bool Lord::remove_protector(const Protector *protector) {
    size_t war_ind = find_protector(protector);
    if (war_ind != army.size()) {
        for (size_t index = war_ind + 1; index < army.size(); index++) {
            army[index - 1] = army[index];
        }
        army.pop_back();
        return true;
    }
    return false;
}


size_t Lord::find_protector(const Protector *protector) {
    for (size_t index = 0; index < army.size(); index++) {
        if (army[index] == protector) {
            return index;
        }
    }
    return army.size();
}

double PersonWithStrengthToFight::get_strength() const {
    return strength;
}


bool Lord::fires(Protector &protector) {
    if (!get_alive()) {//checks warrior is alive
        cout << "The Noble is dead and can't hire" << endl;
        return false;
    }
    //finds the index of the warrior
    size_t index = find_protector(&protector);
    if (index != army.size()) {//makes sure the warrior exists
        cout << army[index]->get_name() <<
             ", you don't work for me anymore ! -- " <<
             get_name()<< "." << endl;
    }
    //removes it from the army
    bool war_rem = remove_protector(&protector);
    if (war_rem) {
        protector.set_hiring(nullptr);//sets to null ptr
    }
    return war_rem;
}




//kill methods
void Lord::kill(){
    set_alive(false);//sets alive field to false
    for(Protector* protector : army){
        protector-> set_strength(0);// goes through and sets strength 0
    }
}

void PersonWithStrengthToFight::kill() {
    set_alive(false);//set alive false
    strength=0;// strength to zero
}



void Noble::battle(Noble& other_noble){

    cout << get_name() << " battles " << other_noble.get_name() << endl;

    //strengths of nobles
    double noble1_strength = get_strength();
    double noble2_strength = other_noble.get_strength();

    battle_cry();
    other_noble.battle_cry();
    //makes sure both are alive outputs if not
    if(!get_alive() && !other_noble.get_alive()) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
    }else if(!get_alive()){
        cout<<"He's dead, "<<other_noble.get_name()<<endl;
        return;}
    else if(!other_noble.get_alive()){
        cout<<"He's dead, "<<get_name()<<endl;
        //compares strengths
        return;
    }
//    battle_cry();
//    other_noble.battle_cry();
    if (noble1_strength==noble2_strength){
        kill();
        other_noble.kill();
        cout << "Mutual Annihilation " << get_name() <<" and " <<
             other_noble.get_name() << " die at each other's hands " << endl;
        //kills weaker Noble
    }else if(noble1_strength>noble2_strength){

        cout<<get_name()<<" defeats "<<other_noble.get_name()<<endl;
        double multiplier = ratio(noble2_strength,noble1_strength);
        other_noble.kill();
        set_strength(multiplier);

    }else if(noble1_strength<noble2_strength){
        cout<<other_noble.get_name()<<" defeats "<<get_name()<<endl;
        double multiplier = ratio(noble1_strength,noble2_strength);
        kill();
        other_noble.set_strength(multiplier);
    }
}



double Noble::ratio(double weaker, double stronger) {
    if(stronger == 0){
        return 1.0;
    }
    return 1 - (weaker / stronger);
}


ostream& operator << (ostream& os, const Noble& noble){
    noble.display(os);
    return os;
}

//displays

ostream& Lord::display(ostream& os) const{
    os << get_name() << " has an army of size:" << army.size();
    for(const Protector* protector: army){
        os << endl << "\t" << protector->get_name()<<" has strength "
           <<protector->get_strength();
    }
    return os;
}

ostream& PersonWithStrengthToFight::display(ostream& os) const{
    os << get_name() << " has strength:" << strength;
    return os;
}

void Lord::battle_cry() const {
    if(get_alive()) {
        for (const Protector *protector: army) {
            protector->display();
        }
    }
}
void PersonWithStrengthToFight::battle_cry() const {
    if(get_alive()) {
        cout << "Ugh!" << endl;
    }
}
