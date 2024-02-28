#include <string>
#include <iostream>

using namespace std;

#ifndef stu_dent
#define stu_dent


namespace PA4
{
    class Course;
    class Student {
        friend class SchoolManagerSystem;
        private:
            string name;
            string ID;
            Course **course_ref;
            int course_ref_count;
        public:

        Student();

        Student(string, string);

        int getCourseCount();
        void incCourseCount();

        void setName(string);
        string getName();

        void setID(string);
        string getID();

        ~Student();

    };
} 
#endif