#include <string>
#include <iostream>
#include "Course.h"

using namespace std;


namespace PA4
{    
    Course::Course() 
    {
        name = "";
        code = "";
        student_ref = NULL;
        student_ref_count = 0;
        _id = rank++;
    }

    Course::Course(string n, string c) 
    {
        name = n;
        code = c;
        student_ref = NULL;
        student_ref_count = 0;
        _id = rank++;
    }

    void Course::setName(string n) {name = n;}
    string Course::getName() {return name;}

    void Course::setCode(string c) {code = c;}
    string Course::getCode() {return code;}


    int Course::getStudentCount() { return student_ref_count;}

    void Course::incStudentCount() {student_ref_count++;}

    Course::~Course() {delete [] student_ref; student_ref = NULL;}

} 
