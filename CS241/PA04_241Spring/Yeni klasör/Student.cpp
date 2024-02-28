#include <string>
#include <iostream>
#include "Student.h"

using namespace std;



namespace PA4
{

        // default constuctor
        Student::Student() 
        {
            ID = "";
            name = "";
            course_ref = NULL;
            course_ref_count = 0;
        }


        // constructor with two parameters name and id
        Student::Student(string n, string i) 
        {
            name = n;
            ID = i;
            course_ref = NULL;
            course_ref_count = 0;
        }


        // setter and getter for easy use
        void Student::setName(string n) {name = n;}
        string Student::getName() {return name;}

        int Student::getCourseCount() {return course_ref_count;}
        void Student::incCourseCount() {course_ref_count++;}

        void Student::setID(string i) {ID = i;}
        string Student::getID() {return ID;}

        Student::~Student() {delete [] course_ref; course_ref = NULL;}


} 
