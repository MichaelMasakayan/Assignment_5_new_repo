#include "Faculty.hpp"

Faculty::Faculty(){
    id = 0;
    name = "";
    level = "";
    department = "";
    numberOfAdvisee = 0;
}

Faculty::Faculty(int idNumber, string facultyName, string facultyLevel, string facultyDepartment){
    id = idNumber;
    name = facultyName;
    level = facultyLevel;
    department = facultyDepartment;
    numberOfAdvisee = 0;
}

Faculty::~Faculty(){

}

void Faculty::printAdvisee(){
    if (numberOfAdvisee == 0){
        cout << "This faculty member doesn't not have any advisees." << endl;
    }
    else
    {
        for (int i = 0; i < numberOfAdvisee; ++i)
        {
            if (i > 0)
            {
                cout << ", ";
            }
            if (advisee.at(i) != 0)
            {
                cout << advisee.at(i);
            }
        }
    }
}

void Faculty::writeToFile(string fileName) {
    ofstream outFile;
    outFile.open(fileName, ios::app);

    outFile << id << "," << name << "," << level << "," << department << ",";
    for (int i = 0; i < numberOfAdvisee; ++i) {
        if (i == 0) {
            outFile << returnFacultyAdvisee(i);
        } else {
            outFile << "," << returnFacultyAdvisee(i);
        }
    }
    outFile << endl;

    outFile.close();
}

void Faculty::AddAnAdvisee(int studentID){
    advisee.push_back(studentID);
    ++numberOfAdvisee;
}

vector<int> Faculty::returnFacultyAdviseeList(){
    return advisee;
}

int Faculty::returnFacultyAdvisee(int id){
    return advisee.at(id);
}

string Faculty::returnFacultyAdviseeWrite() {
    string result = "";
    for (int i = 0; i < advisee.size(); i++)
    {
        result += (advisee.at(i) + ",");
    }
}
void Faculty::setName(string facultyName) {
     name = facultyName; 
}

void Faculty::setID(int facultyID) { 
         id = facultyID;
}

void Faculty::deleteAdvisee(int studentID)
{
    int adviseeIndex = -1;
    for (int j = 0; j < advisee.size(); j++)
    {
        if (advisee.at(j) == studentID)
        {
            adviseeIndex = j;
        }
    }
    if (adviseeIndex == -1)
    {
        cout << "ID was not found. Cannot perform deletion" << endl;
    }
    else
    {   
        advisee.erase(advisee.begin() + adviseeIndex);
    }
    numberOfAdvisee--;
}

bool Faculty::operator<(const Faculty &f) const
{
    return (this->id < f.id);
}

bool Faculty::operator>(const Faculty &f) const
{
    return (this->id > f.id);
}
int  Faculty::returnNumAdvisee() {
     return numberOfAdvisee; }
bool Faculty::operator<=(const Faculty &f) const
{
    return (this->id <= f.id);
}
int Faculty::returnStudentID() {
     return id; 
}
string Faculty::returnStudentLevel() {
     return level; 
}
string Faculty::ReturnFacultiesDep() {
     return department; 
}
string Faculty::returnName() {
     return name; 
}

bool Faculty::operator>=(const Faculty &f) const{
    return (this->id >= f.id);
}

bool Faculty::operator!=(const Faculty &f) const{
    return (this->id != f.id);
}

bool Faculty::operator==(const Faculty &f) const{
    return (this->id == f.id);
}

int Faculty::operator+(const Faculty &f) const{
    return (this->id + f.id);
}