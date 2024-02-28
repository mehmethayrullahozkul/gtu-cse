#include <string>
#include <iostream>

using namespace std;

#ifndef sch_system
#define sch_system


namespace PA4
{
    class Student;
    class Course;
    
    enum CODES {INVALID = 999, SUCCES = 1, QUIT = 0, };

    // functions to use in getting user inputs correctly
    int getStudentName(string&);
    int getCourseName(string&);
    int getID(string&);
    int getCode(string&);

    // function to return digit count of an integer
    int cDigit(int);

    class SchoolManagerSystem {
        private:
            Student **student_arr;
            Course **course_arr;
            int student_count;
            int course_count;
        public:
            void MainMenu();
            int Menu(int);
            SchoolManagerSystem();
    };
} 
#endif