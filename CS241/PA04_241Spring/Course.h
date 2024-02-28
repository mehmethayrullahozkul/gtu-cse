#include <string>
#include <iostream>

using namespace std;

#ifndef co_urse
#define co_urse


namespace PA4
{
    class Student;
        class Course {
            friend class SchoolManagerSystem;
            private:
                string name;
                string code;
                Student **student_ref;
                int student_ref_count;

            public:
                 int _id;
                 static int rank;
                 Course();

                 Course(string, string);

                 void setName(string);
                 string getName();

                 int getStudentCount();
                 void incStudentCount();

                 void setCode(string);
                 string getCode();

                 ~Course();

    };
} 
#endif