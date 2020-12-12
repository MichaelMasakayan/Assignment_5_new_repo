#ifndef _FACULTY_HPP_
#define _FACULTY_HPP_
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Faculty
{
private:
 vector<int> advisee;
    int id;
    unsigned int numberOfAdvisee;
    string name;
    string level;
    string department;

public:
  friend ostream &operator<<(ostream &streamO, Faculty &file){
        streamO << "Faculty ID: " << file.id;
        return streamO;
    }
    bool operator>(const Faculty &f1) const;
    bool operator<=(const Faculty &f1) const;
    Faculty();
    void setName(string facultyName);
    Faculty(int facultyID, string facultyName, string facultyLevel, string facultyDepartment);
    ~Faculty();
    void setID(int facultyID);
    void writeToFile(string fileName);
    void AddAnAdvisee(int studentID);
    void deleteAdvisee(int studentID);
    int returnNumAdvisee();
    string returnFacultyAdviseeWrite();
    bool operator>=(const Faculty &f1) const;
    string returnStudentLevel();
    string ReturnFacultiesDep();
    string returnName();
    bool operator!=(const Faculty &f1) const;
    bool operator==(const Faculty &f1) const;
    bool operator<(const Faculty &f1) const;
    vector<int> returnFacultyAdviseeList();
    int returnFacultyAdvisee(int id);
    int returnStudentID();
    void changeStudentsLevel(string facultyLevel) { level = facultyLevel; }
    void setDepartment(string facultyDepartment) { department = facultyDepartment; }
    void printAdvisee();
    int operator+(const Faculty &f1) const;

  

   
};

#endif