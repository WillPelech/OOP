//
// Created by Will Pelech on 3/15/24.
//
#include<iostream>
#include<string>
#include "course.h"
#include "student.h"
using namespace std;

namespace BrooklynPoly {
    ostream &operator<<(ostream &os, const Course &rhs) {
        os << rhs.name << ": ";
        for (const Student *student: rhs.students) {
            os << student->getName() << " ";
        }
        os << endl;
        return os;
    }

    Course::Course(const string &courseName) : name(courseName) {}

    const string &Course::getName() const { return name; }

    bool Course::addStudent(Student *newStud) {
        for (const Student *student: students) {
            if (student == newStud) {
                return false;
            }
        }
        students.push_back(newStud);
        newStud->addCourse(this);
        return true;
    }

    void Course::removeStudentsFromCourse() {
        for (Student *student: students) {
            student->removedFromCourse(this);
            student = nullptr;
        }
        students.clear();
    }
}
