#include "Student.hpp"
Student::Student(){
    id = 0;
    level = "";
    major = "";
    name = "";
   
    gpa = 0.0;
    advisorId = 0;
}
void Student::writeToFile(string fileName){
    ofstream outFile;
    outFile.open(fileName, ios::app) ;
    
    outFile << id << "," << name << "," << level << "," << major << "," << gpa << "," << advisorId << endl;
}

Student::Student(int idNumber, string studentName, string studentLevel, string studentMajor, double studentGPA, int studentAdvisorID){
    id = idNumber;
    name = studentName;
    level = studentLevel;
    major = studentMajor;
    gpa = studentGPA;
    advisorId = studentAdvisorID;
}
bool Student::operator>(const Student &g){
    return (this->id > g.id);
}

void Student::setID(int studentID) {
    
id = studentID;
}
bool Student::operator<=(const Student &g){
    return (this->id <= g.id);
}

bool Student::operator>=(const Student &g){
    return (this->id >= g.id);
}

bool Student::operator<(const Student &g){
    return (this->id < g.id);
}
string Student::returnName() { 
    return name; 
}
string Student::returnStudentLevel() { 
    return level; 
}
string Student::returnStudentMajor() { 
    return major; 
}
double Student::returnGPA() {
        return gpa; 
}
int Student::returnAdvisorsID(){ 
        return advisorId;
    }


bool Student::operator!=(const Student &g){
    return (this->id != g.id);
}

bool Student::operator==(const Student &g){
    return (this->id == g.id);
}
int Student::returnStudentID() { 
        return id;
}

void Student::setName(string studentName) {
    name = studentName;
}
void Student::changeMajor(string studentMajor){ 
        major = studentMajor;
        
}
void Student::changeStudentsGPA(double studentGPA) { 
    gpa = studentGPA; 
}
void Student::changeAdvisorID(int studentAdvisorID) {
        advisorId = studentAdvisorID; 
}
void Student::changeStudentsLevel(string studentLevel) { 
    level = studentLevel; 
}