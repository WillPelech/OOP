//
// Created by Will Pelech on 3/15/24.
//
#include "registrar.h"
#include "student.h"
#include "course.h"
#include <iostream>
#include <string>
#include <vector>
namespace BrooklynPoly {
    std::ostream &operator<<(std::ostream &os, const Registrar &rhs) {
        os << "Registrar's report" << std::endl << "Courses:" << std::endl;
        for (const Course *course: rhs.courses) {
            os << *course;
        }
        os << "Students:" << std::endl;
        for (const Student *student: rhs.students) {
            os << *student;
        }

        return os;
    }

    Registrar::Registrar() {}

    size_t Registrar::findStudent(const std::string &str) const {
        for (size_t index = 0; index < students.size(); index++) {
            if (students[index]->getName() == str) {
                return index;
            }
        }
        return students.size();
    }

    size_t Registrar::findCourse(const std::string &str) const {
        for (size_t index = 0; index < courses.size(); index++) {
            if (courses[index]->getName() == str) {
                return index;
            }
        }
        return courses.size();

    }

    bool Registrar::addCourse(const std::string &course_name) {
        if (findCourse(course_name) == courses.size()) {
            Course *hp_course = new Course(course_name);
            courses.push_back(hp_course);
            return true;
        }
        return false;
    }

    bool Registrar::addStudent(const std::string &student_name) {
        if (findStudent(student_name) == students.size()) {
            Student *stud = new Student(student_name);
            students.push_back(stud);
            return true;
        }
        return false;
    }

    bool Registrar::enrollStudentInCourse(const std::string &studentName,
                                          const std::string &courseName) {
        if (findStudent(studentName) != students.size()
            && findCourse(courseName) != courses.size()) {
            size_t ind_s = findStudent(studentName);
            size_t ind_c = findCourse(courseName);
            return courses[ind_c]->addStudent(students[ind_s]);
        }
        return false;

    }

    bool Registrar::cancelCourse(const std::string &courseName) {
        size_t ind_c = findCourse(courseName);
        if (ind_c != courses.size()) {
            courses[ind_c]->removeStudentsFromCourse();
            delete courses[ind_c];
            courses[ind_c] = courses[courses.size() - 1];
            courses.pop_back();
            return true;
        }
        return false;

    }

    void Registrar::purge() {
        for (size_t i = 0; i < courses.size(); i++) {
            delete courses[i];
        }
        courses.clear();
        for (size_t i = 0; i < students.size(); i++) {
            delete students[i];
        }
        students.clear();
    }

}