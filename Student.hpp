#ifndef _STUDENT_HPP_
#define _STUDENT_HPP_
#include <iostream>
#include <fstream>

using namespace std;
class Student
{
private:
    double gpa;
    int advisorId;
    int id;
    string name;
    string level;
    string major;
  

public:
    Student();
    Student(int idNumber, string studentName, string studentLevel, string studentMajor, double studentGPA, int studentAdvisorID);

  void setID(int studentID);
    void setName(string studentName);
    void changeMajor(string studentMajor);
    void changeStudentsGPA(double studentGPA);
    void changeAdvisorID(int studentAdvisorID);

    void changeStudentsLevel(string studentLevel);
    string returnName();
    string returnStudentLevel();
    string returnStudentMajor();
    int returnStudentID();
    int returnAdvisorsID();
    double returnGPA();

    void writeToFile(string fileName);
   bool operator>(const Student &g);
    bool operator>=(const Student &g);
    bool operator<(const Student &g);
    bool operator==(const Student &g);
    bool operator<=(const Student &g);
    bool operator!=(const Student &g);
    int operator+(const Student &g1) const;
};

#endif