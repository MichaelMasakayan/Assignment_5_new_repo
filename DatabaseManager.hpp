#ifndef _DATABASE_MANAGER_
#define _DATABASE_MANAGER_

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "GenBST.hpp"
#include "Faculty.hpp"
#include "Student.hpp"

using namespace std;
class DatabaseManager
{
private:
    GenBST<Student> studentTree;
    GenBST<Faculty> facultyTree;
    GenStack<Student> undoStudentStack;
    GenStack<Faculty> undoFacultyStack;
    Student students;

    Faculty faculty;
    GenStack<int> undoActionStack;     
public:
    bool setUpStudentTree(string studentFile);
    bool setUpFacultyTree(string facultyFile);
    DatabaseManager() {};
    ~DatabaseManager() {};
    void runSimulation();
    void writeToFile(string studentFile, string facultyFile);
    void clearFiles(string studentFile, string facultyFile);
    void startMenu();
    void givenStudentAdvisor(); 
    void givenFacultyAdvisee();
    void addStudent();        
    void deleteStudent();     
    void addFaculty();         
    void deleteFaculty();       
    void changeAdvisee();       
    void deleteAdvisee();       
    void rollback();            
    void printStudentHeader();
    void printFacultyHeader();
     void printStudents();   
    void printAllFaculty();   
    void findStudent();        
    void findFaculty();     

    int isTheIntegerValid(string t);
    bool checkInt(string t);
    void printAdvisee(Faculty mentor);
};

#endif