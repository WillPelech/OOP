//
// Created by Will Pelech on 3/15/24.
//
#include <iostream>
#include "course.h"
#include "student.h"
using namespace std;

namespace BrooklynPoly{
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
}}