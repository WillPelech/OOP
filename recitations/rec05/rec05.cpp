/*
  rec05-start.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


// Test code
//void doNothing(Section sec) { cout << sec << endl; }





class Section{
    //initialization of the classes early
    class Student_Record;
    class TimeSlot;
    //output operators
    friend ostream& operator << (ostream& os, const Section& section);
    friend ostream& operator << (ostream& os, const TimeSlot& time);
    friend ostream& operator << (ostream& os, const Student_Record& student);

public:
    //initialization lists
    Section(const string& name, string day, int hour):name(name),time(day,hour){}
    Section(const Section& section) : name(section.name), time(section.time){
        for(const Student_Record* student:section.classlist){
            classlist.push_back(new Student_Record(*student));
        }
    }
    //adds a student pointer to the vector
    void addStudent(const string& name){
        classlist.push_back(new Student_Record(name));
    }


    void addGrade(const string& name, int grade, int week){
        for(Student_Record* student:classlist){
            if(student->get_name()==name){
                student->addGrade(grade,week);
            }
        }
    }

    ~Section(){
        for(Student_Record* student: classlist){
            delete student;
        }
        classlist.clear();
    }

private:

    class Student_Record{
       friend ostream& operator << (ostream& os, const Student_Record& student);
    public:
        //constructor

        Student_Record(string name):student_name(name), weekly_grades(14, -1){
        }
        const string &get_name() { return student_name; };
        void addGrade(int grade, int week) {
            weekly_grades[week-1]=grade;
        }
    private:
        vector<int> weekly_grades;
        string student_name;
    };

    class TimeSlot{
        friend ostream& operator << (ostream& os, const TimeSlot& time);
    public:
        TimeSlot(string day, size_t time_slot):day(day),time_slot(time_slot){}

        string day;
        size_t time_slot;
    };

    string name;
    TimeSlot time;
    vector<Student_Record*> classlist;
};




class LabWorker{
    friend ostream& operator << (ostream& os,const LabWorker& labworker);
public:
    LabWorker(const string& name):instructor_name(name){
    }
    void addSection(Section& section1){
        section=&section1;
    }
    void addGrade(const string& name, int grade, int week){
        section->addGrade(name,grade,week);
    }
private:
    string instructor_name;
    Section* section;
};

//

void doNothing(Section section){}

int main() {

    cout << "Test 1: Defining a section\n";
     Section secA2("A2", "Tuesday", 16);
     cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
     secA2.addStudent("John");
     secA2.addStudent("George");
     secA2.addStudent("Paul");
     secA2.addStudent("Ringo");
     cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
     LabWorker moe( "Moe" );
     cout << moe << endl;


    cout << "\nTest 4: Adding a section to a lab worker.\n";
     moe.addSection( secA2 );
     cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);
     moe.addGrade("Paul", 19, 1);
     moe.addGrade("George", 16, 1);
     moe.addGrade("Ringo", 7, 1);
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);
     moe.addGrade("Paul", 20, 3);
     moe.addGrade("Ringo", 0, 3);
     moe.addGrade("George", 16, 3);
     cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
     doNothing(secA2);
     cout << "Back from doNothing\n\n";

} // main
ostream& operator<<(ostream& os, const Section& section){
    os << "Section: " << section.name << " " << section.time <<" ";
    os<<"Students: "<<endl;
    if(section.classlist.size()==0){
        os<<"None ";
        return os;
    }else{
        for(size_t i = 0; i< section.classlist.size();i++){
            os << *section.classlist[i]<<endl;
        }
    }
    return os;
}
ostream& operator << (ostream& os, const Section::TimeSlot& time){
    os << "Time slot: [Day: " << time.day <<", Start time: ";
    if(time.time_slot>12){
        os<<(time.time_slot-12)<<"pm],";
    }else{
        os<<time.time_slot<<"am],";
    }
    return os;
}
ostream& operator << (ostream& os, const Section::Student_Record& student){
    os<<"Name: "<<student.student_name <<", Grades: ";
    for(int index=0; index<student.weekly_grades.size(); index++){
        os << student.weekly_grades[index]<<" ";
    }
    return os;
}
ostream& operator << (ostream& os,const LabWorker& labworker){
    os<<labworker.instructor_name;
    if(labworker.section == nullptr) {
        os << " does not have a section";
        return os;
    }
    os<<"has a Section: " << *labworker.section;
    return os;
}