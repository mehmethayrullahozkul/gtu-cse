#include <string>
#include <iostream>
#include "SchoolManagerSystem.h"
#include "Student.h"
#include "Course.h"

using namespace std;


namespace PA4
{
    // static int 'rank' for identifying the course
    int Course::rank = 0;

    // default constructor for school management system
    SchoolManagerSystem::SchoolManagerSystem()
    {
        student_arr = NULL;
        course_arr = NULL;
        student_count = 0;
        course_count = 0;
    }

    // main menu, the everything happens here
    void SchoolManagerSystem::MainMenu() 
    {
        // input variables to store
        string course_name;
        string student_name;
        string course_code;
        string student_id;

        // option variable will be used A LOT in menu, it stores the menu input
        int option, found;

        // lambdas for resetting option and found
        auto optionReset = [&]() {option = 1;};
        auto foundReset = [&]() {found = 0;};


        do
        {
            cout << endl << "Main Menu"<<endl;
            cout << "0 " << "exit" << endl;
            cout << "1 " << "student" << endl;
            cout << "2 " << "course" << endl;
            cout << "3 " << "list_all_students" << endl;
            cout << "4 " << "list_all_courses" << endl;
            option = Menu(4);

            switch(option)
            {

                // exiting program
                case 0:
                    break;


                // student menu
                case 1:
                {
                    do
                    {
                        cout << "0 " << "up" << endl;
                        cout << "1 " << "add_student" << endl;
                        cout << "2 " << "select_student" << endl;
                        option = Menu(2);
                        switch(option)
                        {
                            // up - main menu
                            case 0:
                                break;

                            // add_student
                            case 1:
                            {
                                // taking name and id input untill both valid
                                while((cout << "Student name : ") && !getStudentName(student_name));
                                while((cout << "Student ID : ") && !getID(student_id));

                                // if there's no student created yet, create one
                                if(student_arr == NULL) {student_arr = new Student *[1]; student_arr[0] = new Student[1];}

                                // allocate the student pointer array
                                Student **n_arr = new Student*[student_count+1];

                                // allocate the new student
                                Student *n_student = new Student(student_name, student_id);

                                // copy all the current students to n_arr
                                for(int i = 0 ; i < student_count ; i++)
                                    n_arr[i] = student_arr[i];

                                // lastly copy the newly created student.
                                n_arr[student_count] = n_student;

                                // delete old student array
                                delete [] student_arr;

                                // allocate for new one
                                student_arr = new Student*[student_count+1];

                                // copy back all the student data to student array
                                for(int i = 0 ; i < student_count + 1 ; i++)
                                    student_arr[i] = n_arr[i];

                                // increase the student data and break
                                student_count++;
                                break;
                            }

                            // select_student
                            case 2:
                            {
                                // creating an empty variable to store the selected student
                                Student *selected_student = NULL;

                                // if no student created yet, can't select one
                                if(student_count == 0) {cout << "There is no student recorded yet." << endl; break;}

                                // Print out the current students in a 'pretty' way
                                cout << "Current Student Records : " << endl;
                                for(int i = 0 ; i < student_count ; i++)
                                    cout << student_arr[i]->getID() << " | " << student_arr[i]->getName() << endl;

                                // taking name and id untill both are valid
                                while((cout << "Student name : ") && !getStudentName(student_name));
                                while((cout << "Student ID : ") && !getID(student_id));

                                // reset the found variable
                                foundReset();

                                // check the student array if there's actually a student with given name and id
                                for(int i = 0 ; i < student_count ; i++)
                                {
                                    if(student_name == student_arr[i]->getName() && student_id == student_arr[i]->getID())
                                    {
                                        selected_student = student_arr[i];
                                        found = 1;
                                    }
                                }

                                // if didnt find break
                                if(!found) {cout << "Could not find a student with given name and id." <<endl; break;}

                                // if found go ahead
                                do
                                {
                                    cout << "0 " << "up" << endl;
                                    cout << "1 " << "delete_student" << endl;
                                    cout << "2 " << "add_selected_student_to_a_course" << endl;
                                    cout << "3 " << "list_all_courses_this_student_takes" << endl;
                                    option = Menu(3);
                                    switch(option)
                                    {
                                        // up - student menu
                                        case 0:
                                            break;

                                        // delete_student
                                        case 1:
                                        {
                                            // create new student pointer array to store temporarily
                                            Student **c2_student;

                                            // count variable to count...
                                            int count = -1;

                                            // check all courses
                                            for(int a = 0 ; a < course_count ; a++)
                                            {
                                                // check all student's in courses
                                                for(int b = 0 ; b < course_arr[a]->student_ref_count ; b++)
                                                {     
                                                    // if any student match found
                                                    if(course_arr[a]->student_ref[b] == selected_student)
                                                    {
                                                        // allocate the temporarily array
                                                        c2_student = new Student *[course_arr[a]->getStudentCount()-1];

                                                        // copy data to temp array
                                                        for(int i = 0 ; i < course_arr[a]->getStudentCount() ; i++)
                                                        {
                                                            count++;
                                                            // dont copy the data for the student needs to be deleted
                                                            if(course_arr[a]->student_ref[i] == selected_student) 
                                                            {
                                                            count--; 
                                                            //delete student_arr[a]->course_ref[b];
                                                            continue;
                                                            }
                                                            c2_student[count] = course_arr[a]->student_ref[i];
                                                        }

                                                        // delete old student array
                                                        delete course_arr[a]->student_ref;

                                                        // decrement the student count
                                                        course_arr[a]->student_ref_count--;

                                                        // allocate student array again
                                                        course_arr[a]->student_ref = new Student*[course_arr[a]->student_ref_count];

                                                        // copy back the data to student array
                                                        for(int i = 0 ; i < course_arr[a]->student_ref_count ; i++)
                                                            course_arr[a]->student_ref[i] = c2_student[i];

                                                    }
                                                }
                                            }

                                            // basically totally same process with the up but this one deletes the student from student_arr declared in SchoolManagerSystem
                                            // whilst other one deleted for course's student array declared in each Course object.
                                            count = -1;
                                            Student **n_arr = new Student*[student_count-1];
                                            for(int i = 0 ; i < student_count ; i++)
                                            {
                                                count++;
                                                if(student_arr[i] == selected_student)
                                                    {count--; delete student_arr[i]; continue;}
                                                n_arr[count] = student_arr[i];
                                            }

                                            delete student_arr;
                                            student_count--;
                                            student_arr = new Student*[student_count];
                                            for(int i = 0 ; i < student_count ; i++)
                                            {
                                                student_arr[i] = n_arr[i];
                                            }
                                            option = 0;
                                            break;
                                        }

                                        // add_selected_student_to_a_course
                                        case 2:
                                        {
                                            int already_registered;
                                            int count = 0;
                                            do
                                            {
                                                // print out the available courses
                                                count = 0;
                                                cout << "Available Courses : " << endl;
                                                cout << "0 up" << endl;
                                                for(int i = 0 ; i < course_count ; i++)
                                                {   
                                                    already_registered = 0;
                                                    for(int a = 0 ; a < selected_student->getCourseCount() ; a++)
                                                    {
                                                        // if student has the course already in it course_ref array which means already_registered
                                                        if(selected_student->course_ref[a]->getCode() == course_arr[i]->getCode()) 
                                                        {
                                                            already_registered = 1;
                                                            count--;
                                                        }

                                                    }
                                                    // if already_registered, dont print out.
                                                    if(!already_registered)
                                                        cout << course_arr[i]->_id << " | " << course_arr[i]->getCode() << " - " << course_arr[i]->getName() << endl; 
                                                    count++;
                                                }

                                                // temporarily variable, doesnt really have any impact 
                                                int temp;
                                                if(course_arr == NULL) {temp = 0;}
                                                else {temp = course_arr[course_count-1]->_id;}
                                                option = Menu(temp);

                                                // if option is smaller than the temp, let user go further
                                                if(option <= temp) {break;}
                                            }while(option);

                                            // if option is 0, dont continue further, go back to loop
                                            if(!option) {optionReset(); continue;}

                                            // empty variable to hold the selected course
                                            Course *selected_course;

                                            // fill the selected_course variable
                                            for(int i = 0 ; i < course_count ; i++)
                                            {
                                                if(course_arr[i]->_id == option) 
                                                    selected_course = course_arr[i];
                                            }


                                            // connecting a student to a course has two parts, course needs to be in the student's course_ref array 
                                            // and course's student_ref array so I divided the process in two parts but they'r almost totally same-opposite of each other.

                                            // STUDENT PART

                                            // copy variable
                                            Course **c_course;
                                            
                                            // allocate copy variable
                                            c_course = new Course*[selected_student->getCourseCount() + 1];

                                            // copy data to copy variable
                                            for(int i = 0 ; i < selected_student->getCourseCount() ; i++)                                            
                                                c_course[i] = selected_student->course_ref[i];

                                            // copy lastly the new data
                                            c_course[selected_student->getCourseCount()] =  selected_course;

                                            // delete old data
                                            delete selected_student->course_ref;

                                            // increment course count for student
                                            selected_student->incCourseCount();

                                            // reallocate for course_ref
                                            selected_student->course_ref = new Course*[selected_student->getCourseCount()];

                                            // copy back the data
                                            for(int i = 0 ; i < selected_student->getCourseCount() ; i++)
                                                selected_student->course_ref[i] = c_course[i];

                                            
                                            // COURSE PART


                                            Student **c_student;
                                            c_student = new Student *[selected_course->getStudentCount() + 1];
                                            
                                            for(int i = 0 ; i < selected_course->getStudentCount() ; i++)
                                                c_student[i] = selected_course->student_ref[i];
                                            
                                            c_student[selected_course->getStudentCount()] = selected_student;

                                            delete selected_course->student_ref;
                                            
                                            selected_course->incStudentCount();

                                            selected_course->student_ref = new Student *[selected_course->getStudentCount()];

                                            for(int i = 0 ; i < selected_course->getStudentCount() ; i++)
                                                selected_course->student_ref[i] = c_student[i];

                                            optionReset();
        
                                            break;
                                        }

                                        // print all courses this student taking
                                        case 3:
                                        {
                                            if(selected_student->getCourseCount() == 0) cout << "This student has not registered to a course." << endl;
                                            else
                                            {
                                    
                                            for(int i = 0 ; i < selected_student->getCourseCount() ; i++)
                                                cout <<selected_student->course_ref[i]->getCode() << " | " << selected_student->course_ref[i]->getName() << endl;
                                            }
                                        }
                                    }
                                }while(option);
                                optionReset();
                                break;
                            }

                        }
                    }while(option);
                    optionReset();
                    break;
                }


                // courses menu

                // basically same logic and code of student menu, from copying to variables, everything pretty much same
                case 2:
                {
                    do
                    {
                        cout << "0 " << "up" << endl;
                        cout << "1 " << "add_course" << endl;
                        cout << "2 " << "select_course" << endl;
                        option = Menu(2);
                        switch(option)
                        {
                            // up - main menu
                            case 0:
                                break;
                            
                            // add_course
                            case 1:
                            {
                                while((cout << "Course name : ") && !getCourseName(course_name));
                                while((cout << "Course code : ") && !getCode(course_code));

                                if(course_arr == NULL) {course_arr = new Course *[1]; course_arr[0] = new Course[1];}

                                Course **n_arr = new Course*[course_count+1];

                                Course *n_course = new Course(course_name, course_code);

                                for(int i = 0 ; i < course_count ; i++)
                                    n_arr[i] = course_arr[i];

                                n_arr[course_count] = n_course;
                                delete [] course_arr;
                                course_arr = new Course*[course_count+1];

                                for(int i = 0 ; i < course_count + 1 ; i++)
                                    course_arr[i] = n_arr[i];
                                course_count++;
                                break;
                            }
                            
                            // select_course
                            case 2:
                            {

                                if(course_count == 0) {cout << "There is no course recorded yet." << endl; break;}
                                
                                Course *selected_course = NULL;

                                cout << "Current Course Records : " << endl;
                                for(int i = 0 ; i < course_count ; i++)
                                    cout << course_arr[i]->getCode() << " | " << course_arr[i]->getName() << endl;

                                while((cout << "Course name : ") && !getCourseName(course_name));
                                while((cout << "Course code : ") && !getCode(course_code));
                                foundReset();
                                for(int i = 0 ; i < course_count ; i++)
                                {
                                    if(course_name == course_arr[i]->getName() && course_code == course_arr[i]->getCode())
                                    {
                                        selected_course = course_arr[i];
                                        found = 1;
                                    }
                                        
                                }
                                if(!found) {cout << "Could not find a course with given name and id." <<endl; break;}
                                do
                                {
                                    cout << "0 " << "up" << endl;
                                    cout << "1 " << "delete_course" << endl;
                                    cout << "2 " << "list_all_students_registered_to_the_selected_course" << endl;
                                    option = Menu(2);
                                    switch(option)
                                    {
                                        case 0:
                                            break;

                                        case 1:
                                        {
                                            Course **c2_course;
                                            int count = -1;
                                            for(int a = 0 ; a < student_count ; a++)
                                            {
                                                for(int b = 0 ; b < student_arr[a]->course_ref_count ; b++)
                                                {     
                                                    if(student_arr[a]->course_ref[b] == selected_course)
                                                    {

                                                        c2_course = new Course *[student_arr[a]->getCourseCount()-1];
                                                        for(int i = 0 ; i < student_arr[a]->getCourseCount() ; i++)
                                                        {
                                                            count++;
                                                            if(student_arr[a]->course_ref[i] == selected_course) 
                                                            {
                                                            count--; 
                                                            continue;
                                                            }
                                                            c2_course[count] = student_arr[a]->course_ref[i];
                                                        }
                                                        delete student_arr[a]->course_ref;
                                                        student_arr[a]->course_ref_count--;

                                                        student_arr[a]->course_ref = new Course*[student_arr[a]->course_ref_count];
                                                        for(int i = 0 ; i < student_arr[a]->course_ref_count ; i++)
                                                            student_arr[a]->course_ref[i] = c2_course[i];

                                                    }
                                                }
                                            }

                                            count = -1;
                                            Course **n_arr = new Course*[course_count-1];

                                            for(int i = 0 ; i < course_count ; i++)
                                            {
                                                count++;
                                                if(course_arr[i] == selected_course)
                                                {
                                                    count--; 
                                                    delete course_arr[i]; 
                                                    continue;
                                                }
                                                n_arr[count] = course_arr[i];
                                            }

                                            delete course_arr;
                                            course_count--;
                                            course_arr = new Course*[course_count];

                                            for(int i = 0 ; i < course_count ; i++)
                                            {
                                                course_arr[i] = n_arr[i];
                                            }
                                            option = 0;
                                            break;
                                        }
                                        case 2:
                                        {
                                            if(selected_course->getStudentCount() == 0) {cout << "This course currently has no students recorded." << endl;}

                                            else
                                            {
                                                cout << selected_course->getCode() << "'s students as : " <<endl;
                                                for(int i = 0 ; i < selected_course->getStudentCount() ; i++)
                                                    cout << i+1 << " - " <<selected_course->student_ref[i]->getID() << " | " << selected_course->student_ref[i]->getName() << endl;
                                            }
                                        }
                                    }
                                }while(option);
                                optionReset();
                                break;
                            
                            }
                        }
                    }while(option);
                    optionReset();
                    break;
                }


                // list all students
                case 3:
                {
                    // if there's no student, there's nothing to print.
                    if(student_count == 0) {cout << "There is no student recorded yet." << endl; break;}
                    for(int i = 0 ; i < student_count ; i++)
                        cout << i+1 << " | " << student_arr[i]->getID() << " - " << student_arr[i]->getName() << endl; 
                    break;
                }

                // list all courses
                case 4:
                {
                    // if there's no course, there's nothing to print.
                    if(course_count == 0) {cout << "There is no course recorded yet." << endl; break;}
                    for(int i = 0 ; i < course_count ; i++)
                        cout << i+1 << " | " << course_arr[i]->getCode() << " - " << course_arr[i]->getName() << endl; 
                    break;
                }
            }
        }while(option);
    }









    int  SchoolManagerSystem::Menu(int numberOfOptions) 
    {

        string entry;

        cin >> entry;

        // lets say our menu has 0-1-2-3-4 options, entered strings size can not be greater than 1, cDigit(4) = 1;
        if(entry.size() > cDigit(numberOfOptions)) {return INVALID;}

        // if 0 entered, quit
        else if(entry == "0") {return QUIT;}

        // menu does not accept any character input other than numeric, if there's any return INVALID
        for(int i = 0 ; i < cDigit(numberOfOptions) ; i++) {if(entry[i] < '1' || entry[i] > '9') {return INVALID;}}

        // lets say our menu has 0-1-2-3-4 options, input can not be 5
        if(stoi(entry) > numberOfOptions) {return INVALID;}

        // return int version of entry if everything's ok so far
        else  {return stoi(entry);}
            
    }

    // return digit count of the given number
    int cDigit(int n)
    {
        if (n == 0) return 1;
        int count = 0;
        while (n != 0) {n = n / 10; count++;}
        return count;
    }

    // checking entered string, name's can not have numbers in it.
    int getStudentName(string&s) 
    {
        cin.ignore();
        std::getline(std::cin, s);
        for(int i = 0 ; i < s.size() ; i++) 
        {
            if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || s[i] == ' ')) {return 0;}
        }
        return SUCCES;
    }

    // checking entered string, course name can not have numbers in it
    int getCourseName(string&s) 
    {
        cin.ignore();
        std::getline(std::cin, s);
        for(int i = 0 ; i < s.size() ; i++) 
        {
            if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || s[i] == ' ')) {return 0;}
        }
        return SUCCES;
    }

    // checking entered string ID cant have letters in it
    int getID(string&s) 
    {
        cin >> s;
        if(s.size() > 8) {return INVALID;}
        for(int i = 0 ; i < s.size() ; i++)
        {
            if(s[i] > '9' || s[i] < '0') {return 0;}
        }
        return SUCCES;
    }

    // checking code,  code should not be longer than 8 characters
    int getCode(string&s) 
    {
        cin >> s;
            if(s.size() > 8) {return 0;}
            return SUCCES;
    }


} 
