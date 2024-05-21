/*
  rec08_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to implement the methods and
  fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    bool removeThis(Student*);
    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);
    void setName(const string& new_n);
    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course*);


private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string&);
    // Creates a new student, if none with that name
    bool addStudent(const string&);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

    bool changeStudentName(const string& old, const string& new_n);

    bool dropStudentFromCourse(const string& student, const string& course);

    bool removeStudent(const string& student);
private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;


    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;


    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}
//course
ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.name << ": ";
    for(const Student* student: rhs.students){
        os<<student->getName()<<" ";
    }
    os << endl;
    return os;
}

Course::Course(const string& courseName):name(courseName){}
const string& Course::getName() const{return name;}
bool Course::addStudent(Student* newStud){
    for(const Student* student: students){
        if (student==newStud){
            return false;
        }
    }
    students.push_back(newStud);
    newStud->addCourse(this);
    return true;
}
void Course::removeStudentsFromCourse(){
    for(Student* student : students){
        student->removedFromCourse(this);
        student= nullptr;
    }
    students.clear();
}
//student
ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.getName() << ": ";
    for(const Course* course: rhs.courses){
        os<<course->getName()<<" ";
    }
    os<<endl;
    return os;
}
Student::Student(const string& name):name(name){}
const string& Student::getName() const{ return name;}

bool Student::addCourse(Course* course){
//    for(const Course* currCourse: courses){
//        if(currCourse->getName()==course->getName()){
//            return false;
//        }
//    }
    courses.push_back(course);
    return true;
}

// Student method needed by Course::removeStudentsFromCourse
void Student::removedFromCourse(Course* course){
    for(size_t index = 0 ; index< courses.size();index++){
        if(courses[index]==course){
            courses[index]=courses[courses.size() - 1];
            courses.pop_back();
            break;
        }
    }
}
//registrar
ostream& operator<<(ostream& os, const Registrar& rhs){
    os << "Registrar's report" << endl << "Courses:" <<endl;
    for(const Course* course : rhs.courses){
        os<<*course;
    }
    os<<"Students:"<<endl;
    for(const Student* student : rhs.students){
        os<<*student;
    }

    return os;
}
Registrar::Registrar() {}

size_t Registrar::findStudent(const std::string & str) const {
    for(size_t index = 0; index < students.size(); index++){
        if(students[index]->getName() == str){
            return index;
        }
    }
    return students.size();
}

size_t Registrar::findCourse(const std::string & str) const {
    for(size_t index = 0; index < courses.size(); index++){
        if(courses[index]->getName() == str){
            return index;
        }
    }
    return courses.size();

}
bool Registrar::addCourse(const string& course_name){
    if(findCourse(course_name)==courses.size()){
        Course* hp_course=new Course(course_name );
        courses.push_back(hp_course);
        return true;
    }
    return false;
}

bool Registrar::addStudent(const std::string & student_name) {
    if(findStudent(student_name)==students.size()){
        Student* stud = new Student(student_name);
        students.push_back(stud);
        return true;
    }
    return false;
}
bool Registrar::enrollStudentInCourse(const string& studentName,
                                      const string& courseName){
    if(findStudent(studentName) != students.size()
       && findCourse(courseName)!= courses.size()){
        size_t ind_s = findStudent(studentName);
        size_t ind_c = findCourse(courseName);
        return courses[ind_c]->addStudent(students[ind_s]);
    }
    return false;

}

bool Registrar::cancelCourse(const string& courseName){
    size_t ind_c = findCourse(courseName);
    if(ind_c!=courses.size()) {
        courses[ind_c]->removeStudentsFromCourse();
        delete courses[ind_c];
        courses[ind_c]=courses[courses.size() - 1];
        courses.pop_back();
        return true;
    }
    return false;

}

void Registrar::purge(){
    for(size_t i = 0; i<courses.size();i++){
        delete courses[i];
    }
    courses.clear();
    for(size_t i = 0; i<students.size();i++){
        delete students[i];
    }
    students.clear();
}

void Student::setName(const std::string &new_n) {
    name=new_n;
}
bool Registrar::changeStudentName(const string& old, const string& new_n){
    size_t ind_s = findStudent(old);
    if(ind_s!=students.size()) {
        students[ind_s]->setName(new_n);
        return true;
    }else{
      return false;
    }
}
bool Course::removeThis(Student* student){
    for(size_t i = 0; i<students.size(); i++){
        if(students[i]==student){
            cout << students[i]->getName() << endl;
            students[i]->removedFromCourse(this);
            students[i]=students[students.size()-1];
            students.pop_back();
            return true;
        }
    }
    return false;
}

bool Registrar::dropStudentFromCourse(const string& student, const string& course){
    size_t ind_s= findStudent(student);
    size_t ind_c= findCourse(course);
    if (ind_s==students.size()||ind_c==courses.size()){
        return false;
    }
    return courses[ind_c]->removeThis(students[ind_s]);
}

bool Registrar::removeStudent(const string& student){
    size_t ind_s= findStudent(student);
    if(ind_s==students.size()){
        return false;
    }
    Student* stud=students[ind_s];
    for(size_t i=0;i<courses.size();i++){
        courses[i]->removeThis(stud);
    }
    return true;
}
