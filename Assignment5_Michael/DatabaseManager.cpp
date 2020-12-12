#include "DatabaseManager.hpp"

void printStudentInfo(Student *student);
void printStudentName(Student *student);
void writeStudentFile(Student *student, ofstream OFile);
void printFacultyInfo(Faculty *faculty);
void printFacultyName(Faculty *faculty);
void writeFacultyFile(Faculty *faculty, ofstream OFile);

void DatabaseManager::startMenu(){
    cout << "\n Choice. choose the functions you would like to perform" << endl;
    cout << "1: Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2:Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3:Find and display student information given the students id" << endl;
    cout << "4:Find and display faculty information given the faculty id" << endl;
    cout << "5:Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6:Given a faculty id, print ALL the names and info of his/her advisees." << endl;
    cout << "7:Add a new student" << endl;
    cout << "8:Delete a student given the id" << endl;
    cout << "9:Add a new faculty member" << endl;
    cout << "10:Delete a faculty member given the id." << endl;
    cout << "11:Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "12:Remove an advisee from a faculty member given the ids" << endl;
    cout << "13:Rollback" << endl;
    cout << "14:Exit" << endl;
    cout << "15:to reset the page" << endl;
}

void DatabaseManager::runSimulation()
{
    int choice = -1;
    string t;
    string empty;
    startMenu();

while (choice != 14)
{
    cout << "Enter an option (type and enter 15 to reset window): \n";
    cin >> t;
    getline(cin, empty);
    choice = isTheIntegerValid(t);
    if (choice == 15) {
        startMenu();
    } 
    else if (choice == 1){
        printStudents();
    }
    else if (choice == 2){
        printAllFaculty();
    }
    else if (choice == 3){
        findStudent();
    }
    else if (choice == 5){
        givenStudentAdvisor();
    }
    else if (choice == 6){
        givenFacultyAdvisee();
    }
    else if (choice == 7){
        addStudent();
    }
    else if (choice == 8){
        deleteStudent();
    }
    else if (choice == 9){
        addFaculty();
    }
    else if(choice == 10) {
        deleteFaculty();
    } 
    else if (choice == 11) {
        changeAdvisee();
    } 
    else if (choice == 12) {
        deleteAdvisee();
    } 
    else if (choice == 13) {
        rollback();
    }
    else if (choice == 4){
        findFaculty();
    }
    else if (choice != 14 && choice < 14) {
        cout << "theInput you tried was invalid" << endl;
    }
} 
    clearFiles("StudentTable.txt", "FacultyTable.txt");
    writeToFile("StudentTable.txt", "FacultyTable.txt");
}

bool DatabaseManager::setUpStudentTree(string studentFile) {
ifstream inFile;
inFile.open(studentFile);
if (!inFile) {
    cout << "Student File not found" << endl;
    return false;
}
string t = "";
int count = 0;
int studentID = 0;
string studentName = "";
string studentLevel = "";
string studentMajor = "";
double GPAofStudent = 0.0;
int advisorID = 0;

while (getline(inFile, t)) {
    if (count == 0) {
        studentID = isTheIntegerValid(t);
        count++;
    } else if (count == 1) {
        studentName = t;
        count++;
    } else if (count == 2) {
        studentLevel = t;
        count++;
    } else if (count == 3) {
        studentMajor = t;
        count++;
    } else if (count == 4) {
        GPAofStudent = stoi(t);
        count++;
    } else if (count == 5) {
        advisorID = isTheIntegerValid(t);
        Student *newStudent = new Student(studentID, studentName, studentLevel, studentMajor, GPAofStudent, advisorID);
        studentTree.insert(newStudent);
        count = 0;
    }
}
    inFile.close();
    return true;
}

bool DatabaseManager::setUpFacultyTree(string facultyFile) {
    ifstream inFile;
    inFile.open(facultyFile);
    if (!inFile) {
        cout << "Faculty File not found" << endl;
        return false;
    }
    string t = "";
    int count = 0;
    
    int facID = 0;
    string facultyName = "";
    string facultyLevel = "";
    string facultyDepartment = "";
    int advisorID = 0;

while (getline(inFile, t)) {
    if (count == 0) {
        facID = isTheIntegerValid(t);
        count++;
    } else if (count == 1) {
        facultyName = t;
        count++;
    } else if (count == 2) {
        facultyLevel = t;
        count++;
    } else if (count == 3) {
        facultyDepartment = t;
        count++;
    } else if (count == 4) {
        Faculty *newFaculty = new Faculty(facID, facultyName, facultyLevel, facultyDepartment);
        string idString = "";
        int idNumber = 0;
    for (int l = 0; l < t.length(); ++l) {
        if (t[l] != ',') {
            idString += t[l];
        } else {
            idNumber = stoi(idString);
        }
        newFaculty->AddAnAdvisee(idNumber);
    }
    facultyTree.insert(newFaculty);
    count = 0;
    } 
}
    inFile.close();
    return true;
}

void DatabaseManager::writeToFile(string studentFile, string facultyFile) {
    studentTree.writeTree(studentFile);

    facultyTree.writeTree(facultyFile);
}

void DatabaseManager::clearFiles(string studentFile, string facultyFile) {
    ofstream OFile;
    OFile.open(studentFile);
    OFile.close();

    OFile.open(facultyFile);
    OFile.close();
}



void DatabaseManager::findFaculty(){
    int facID;
    string t;
    cout << "Please enter the ID of the faculty you want to search for: " << endl;
    cin >> t;
    facID = isTheIntegerValid(t);

    Faculty *targetFaculty = new Faculty();

    targetFaculty->setID(facID);

if (facultyTree.search(targetFaculty)){
    cout << "Faculty member was found" << endl;
    targetFaculty = facultyTree.find(targetFaculty);
    printFacultyHeader();
    printFacultyInfo(targetFaculty);
}
else{
    cout << "Sorry there is no faculty with that ID" << endl;
}
}

void DatabaseManager::givenStudentAdvisor(){
    int studentID;
    string t;
    cout << "Please enter the student ID to find information on their advisor: " << endl;
    
    cin >> t;
    studentID = isTheIntegerValid(t);

    Student *targetStudent = new Student();

    targetStudent->setID(studentID);

    if (studentTree.search(targetStudent)){
        targetStudent = studentTree.find(targetStudent);
        Faculty *targetFaculty = new Faculty();

        targetFaculty->setID(targetStudent->returnAdvisorsID());
        if (facultyTree.search(targetFaculty)){
            targetFaculty = facultyTree.find(targetFaculty);
            cout << "Faculty member was found" << endl;
            printFacultyHeader();
            printFacultyInfo(targetFaculty);
        }
        else
        {
            cout << "Sorry there is no faculty with that ID" << endl;
        }
    }
    else
    {
        cout << "Sorry there is no student with that ID" << endl;
    }
}
void DatabaseManager::printStudents(){
    printStudentHeader();
    studentTree.printTree(printStudentInfo);
}

void DatabaseManager::printAllFaculty(){
    printFacultyHeader();
    facultyTree.printTree(printFacultyInfo);
}

void DatabaseManager::findStudent(){
    int studentID = 0;
    string t;
    cout << "Please enter the ID of the student you want to search for: " << endl;
    cin >> t;
    studentID = isTheIntegerValid(t);

    Student *targetStudent = new Student();

    targetStudent->setID(studentID);
    if (studentTree.search(targetStudent)){
        cout << "Student has been found" << endl;

        targetStudent = studentTree.find(targetStudent);
        printStudentHeader();
        printStudentInfo(targetStudent);
    }
    else{
        cout << "Sorry there is no student with that ID" << endl;
    }
}
void DatabaseManager::givenFacultyAdvisee(){
    int facID;
    string t;

    cout << "Please enter the faculyt ID to find information on their advisees: " << endl;
    cin >> t;
    facID = isTheIntegerValid(t);

    Faculty *targetFaculty = new Faculty();

    targetFaculty->setID(facID);
    if (facultyTree.search(targetFaculty)){
        targetFaculty = facultyTree.find(targetFaculty);
        if (targetFaculty->returnNumAdvisee() == 0) {
            cout << "This faculty member does not have any advisee" << endl;
        } else {
            printAdvisee(*targetFaculty);
        }
        
    }
    else{
        cout << "Sorry there is no faculty with that ID" << endl;
    }
}

void DatabaseManager::printAdvisee(Faculty mentor){
    printStudentHeader();
    for (int j = 0; j < mentor.returnNumAdvisee(); ++j){
        Student *targetStudent = new Student();

        targetStudent->setID(mentor.returnFacultyAdvisee(j));

        if (studentTree.search(targetStudent)){
            cout << "Student was found" << endl;
            targetStudent = studentTree.find(targetStudent);
            printStudentInfo(targetStudent);
        }
        else{
            cout << "Sorry there is no student with ID: " << mentor.returnFacultyAdvisee(j) << endl;
        }
    }
}

void DatabaseManager::addStudent(){
    
    int studentID;
    string studentName;
    string studentLevel;
    
    string studentMajor;
    
    double GPAofStudent;
    int studentAdvisorID;
    string t;

    Faculty *targetFaculty = new Faculty();

    cout << "input the ID you would like the student's to have " << endl;
    cin >> t;
    studentID = isTheIntegerValid(t);
    getline(cin, t);
    cout << "input the name you would like the student's to have:" << endl;
    getline(cin, studentName);
    cout << "input the leve you would like the student's to have:" << endl;
    cin >> studentLevel;
    getline(cin, t);
    cout << " input the major you would like the student's :" << endl;
    getline(cin, studentMajor);
    cout << "input the GPA you would like the student's to have:" << endl;
    cin >> GPAofStudent;
    cout << "input the Advisor ID you would like the student's to have" << endl;
    
    cin >> t;
    studentAdvisorID = isTheIntegerValid(t);

    targetFaculty->setID(studentAdvisorID);
    while (!facultyTree.search(targetFaculty)){
        cout << "The ID of the faculty member was not found.  Renter a valid faculty ID :" << endl;
        cin >> t;
        studentAdvisorID = isTheIntegerValid(t);
        targetFaculty->setID(studentAdvisorID);
    }
    targetFaculty = facultyTree.find(targetFaculty);
    targetFaculty->AddAnAdvisee(studentID);
    Student *newStudent = new Student(studentID, studentName, studentLevel, studentMajor, GPAofStudent, studentAdvisorID);
    studentTree.insert(newStudent);
    undoActionStack.push(0);
    undoStudentStack.push(*newStudent);
}

void DatabaseManager::addFaculty(){
    int facID;
    string facultyName;
    
    string facultyLevel;
    string department;

    string t;

    cout << "input the ID you would like the Faulty to have: " << endl;
    cin >> t;
    facID = isTheIntegerValid(t);
    
    cout << "input the Name you would like the Faulty to have: " << endl;
    cin >> facultyName;
    
    cout << "input the Level you would like the Faulty to have: " << endl;
    cin >> facultyLevel;
    
    getline(cin, t);
    cout << "input the Department you would like the Faulty to have: " << endl;
    
    getline(cin, department);

    Faculty *newFaculty = new Faculty(facID, facultyName, facultyLevel, department);
    facultyTree.insert(newFaculty);

    undoActionStack.push(1);
    undoFacultyStack.push(*newFaculty);
}

void DatabaseManager::deleteStudent(){



    int facID = 0;
    
    int studentID = 0;

    string t;
    cout << " Enter the ID of the student you wish to be deleted: " << endl;

    cin >> t;
    studentID = isTheIntegerValid(t);

    Student *targetStudent = new Student();

    targetStudent->setID(studentID);

    if (studentTree.search(targetStudent)){
        targetStudent = studentTree.find(targetStudent);
        facID = targetStudent->returnAdvisorsID();
        Faculty *targetFaculty = new Faculty();
        targetFaculty->setID(facID);
        targetFaculty = facultyTree.find(targetFaculty);
        targetFaculty->deleteAdvisee(studentID);
    }
    else{
        cout << "there seems to be no student that goes by that ID" << endl;
    }
    if (studentTree.remove(targetStudent)){
        cout << "completed. Student has been sucessfully deleted" << endl;
    }
    else{
        cout << "err. The chosen Student was not deleted." << endl;
    }
    undoActionStack.push(2);
    undoStudentStack.push(*targetStudent);
}

void DatabaseManager::deleteFaculty(){
    vector<int> advisee;
    int facID = 0;
    string t;
    cout << "Enter the faculty ID you want to delete:" << endl;
    cin >> t;
    facID = isTheIntegerValid(t);

    Faculty *targetFaculty = new Faculty();
    targetFaculty->setID(facID);


    if (facultyTree.search(targetFaculty)){
        targetFaculty = facultyTree.find(targetFaculty);

        advisee = targetFaculty->returnFacultyAdviseeList();
        Student *targetStudent = new Student();
        for (int f = 0; f < advisee.size(); f++) {
            targetStudent->setID(advisee.at(f));

            targetStudent = studentTree.find(targetStudent);
            targetStudent->changeAdvisorID(facultyTree.getRandomNode().returnStudentID());
        }
    }
    else{
        cout << " There seems to be no faculty that goes by that ID" << endl;
    }
    if (facultyTree.remove(targetFaculty)) {
        cout << "The faculty entered has been sucessfully deleted" << endl;
    }
    else
    {
        cout << "err. The chosen Faculty was not deleted." << endl;
    }
    undoActionStack.push(3);

    undoFacultyStack.push(*targetFaculty);
}

void DatabaseManager::changeAdvisee() {
    int facID = 0;
    int pastAdvisor = 0;
    int studentID = 0;
    string t;
    cout << "Enter the student ID you want to delete:" << endl;
    cin >> t;
    studentID = isTheIntegerValid(t);

    Student *targetStudent = new Student();
    targetStudent->setID(studentID);

    while (!studentTree.search(targetStudent))
    {
        cout << " There seems to be no student that goes by that ID. Reenter a valid ID:" << endl;

        cin >> t;
        studentID = isTheIntegerValid(t);

        targetStudent->setID(studentID);
    }

    cout << "Enter the ID of the faculty you want to be paired with student: " << endl;

    cin >> t;
    facID = isTheIntegerValid(t);
    Faculty *targetFaculty = new Faculty();

    targetFaculty->setID(facID);
    
    while (!facultyTree.search(targetFaculty))
    {
        cout << "Sorry there seems to be no faculty that goes by that ID. Reenter a valid ID:" << endl;
        cin >> t;
        facID = isTheIntegerValid(t);
        targetFaculty->setID(facID);
    }
    targetStudent = studentTree.find(targetStudent);

    pastAdvisor = targetStudent->returnAdvisorsID();

    targetStudent->changeAdvisorID(facID);

    targetFaculty->setID(pastAdvisor);
    targetFaculty->deleteAdvisee(studentID);
}

void DatabaseManager::deleteAdvisee() {
    int facID = 0;


    int studentID = 0;
    string t;
    string userResponse;

    cout << "Enter the ID of the faculty so the related advisee can be removed: " << endl;
    cin >> t;
    facID = isTheIntegerValid(t);

    Faculty *targetFaculty = new Faculty();
    targetFaculty->setID(facID);

    while (!facultyTree.search(targetFaculty))
    {
        cout << "Sorry there seems to be no faculty that goes by that ID. Reenter a valid ID:" << endl;
        cin >> t;
        facID = isTheIntegerValid(t);
        targetFaculty->setID(facID);
    } 

    cout << "Enter the ID of the student that you wish to be taken off the advisee list. " << endl;
    
    cin >> t;

    studentID = isTheIntegerValid(t);

    Student *targetStudent = new Student();
    Faculty facultyEntry;

    targetStudent->setID(studentID);
    while (!studentTree.search(targetStudent))
    {
        cout << "There seems to be no student by that ID please reenter a valid Id:" << endl;
        cin >> t;
        studentID = isTheIntegerValid(t);
        targetStudent->setID(studentID);
    }
    targetFaculty = facultyTree.find(targetFaculty);
    targetFaculty->deleteAdvisee(studentID);
    
    cout << "To ramdomly assign an advisor type R:Rand To enter an advisor press E:Enter: " << endl;

    cin >> userResponse;
    while (userResponse != "R" && userResponse != "E" && userResponse != "r" && userResponse != "e" ) {
        cout << "Invalid Response Try Again..." << endl;
        cin >> userResponse;
    }

    if (userResponse == "E" || userResponse == "e") {
        cout << " Enter the ID of the advisor: " << endl;
        cin >> t;
        facID = isTheIntegerValid(t);
        Faculty *targetFaculty = new Faculty();
        targetFaculty->setID(facID);
        while (!facultyTree.search(targetFaculty))
        {
            cout << "There seems to be no faculty that goes by that ID please reenter a valid ID:" << endl;
            cin >> t;
            facID = isTheIntegerValid(t);
            targetFaculty->setID(facID);
        } 
        targetFaculty = facultyTree.find(targetFaculty);
        targetStudent = studentTree.find(targetStudent);
        targetStudent->changeAdvisorID(facID);
        targetFaculty->AddAnAdvisee(studentID);
    } 
    else {
        facultyEntry = facultyTree.getRandomNode();
        Faculty *newFaculty = new Faculty();
        newFaculty->setID(facultyEntry.returnStudentID());
        targetFaculty = facultyTree.find(newFaculty);
        targetStudent = studentTree.find(targetStudent);

        targetStudent->changeAdvisorID(facultyEntry.returnStudentID());
        targetFaculty->AddAnAdvisee(studentID);
    }
}

void DatabaseManager::rollback() {
    int action = undoActionStack.pop();
if (action == 0) {  
        cout << "These are the students that have been added from the rollback" << endl;
    Student undoStudent = undoStudentStack.pop();
    Student *studentToDelete = new Student();

    studentToDelete->setID(undoStudent.returnStudentID());
    studentToDelete = studentTree.find(studentToDelete);  
    studentTree.remove(studentToDelete);
    
}
   
    else if (action == 3) {   
    cout << "rollback delete function, Faculty" << endl;
    Faculty undoFaculty = undoFacultyStack.pop();
    Faculty *facultyToDelete = new Faculty();
    facultyToDelete->setID(undoFaculty.returnStudentID());
    facultyToDelete->setName(undoFaculty.returnName());
    facultyToDelete->setDepartment(undoFaculty.ReturnFacultiesDep());
    facultyToDelete->changeStudentsLevel(undoFaculty.returnStudentLevel());
    Student *advisee = new Student();
    for (int j = 0; j < undoFaculty.returnNumAdvisee(); ++j) {
        advisee->setID(undoFaculty.returnFacultyAdvisee(j));
        advisee = studentTree.find(advisee);
        advisee->changeAdvisorID(undoFaculty.returnStudentID());
    }
        
        facultyTree.insert(facultyToDelete);
       
    } 
else if (action == 2) {   
        cout << "delete function rollback " << endl;
    Student undoStudent = undoStudentStack.pop();
    Student *studentToDelete = new Student();
    studentToDelete->setID(undoStudent.returnStudentID());
    studentToDelete->setName(undoStudent.returnName());
    studentToDelete->changeStudentsLevel(undoStudent.returnStudentLevel());

    studentToDelete->changeMajor(undoStudent.returnStudentMajor());
    studentToDelete->changeStudentsGPA(undoStudent.returnGPA());
    studentToDelete->changeAdvisorID(undoStudent.returnAdvisorsID());
    studentTree.insert(studentToDelete);
    
} 

    else if (action == 1) {   
    cout << " roll back of faculty add"<< endl;
    Faculty undoFaculty = undoFacultyStack.pop();
    Faculty *facultyToDelete = new Faculty();
    facultyToDelete->setID(undoFaculty.returnStudentID());
    facultyToDelete = facultyTree.find(facultyToDelete);  
    facultyTree.remove(facultyToDelete);
    
} 
     
   
}

int DatabaseManager::isTheIntegerValid(string t){
    while (checkInt(t))
    {
        cout << "Invalid Input. reenter : " << endl;
        cin >> t;
    }
return stoi(t);
}

bool DatabaseManager::checkInt(string t){
    bool check = false;
    for (int k = 0; k < t.length() && !check; ++k)
    {
        if (!isdigit(t[k]))
        {
            check = true;
        }
    }
    return check;
}

void DatabaseManager::printStudentHeader(){
    cout << "----- | ------------------ | --------- | ------------------------ |    ----- |  ------------ " << endl;
    cout << "ID:   | Name:              | Level:    | Major:                   |    GPA:  | Advisor ID    " << endl;
    cout << "----- | ------------------ | --------- | ------------------------ |    ----- |  ------------ " << endl;
}

void printStudentInfo(Student *student){
    cout << left << setw(10) << student->returnStudentID() << "~~~ "
         << setw(25) << student->returnName() << "  "
         << setw(11) << student->returnStudentLevel() << " "
         << setw(25) << student->returnStudentMajor() << " "
         << setw(5) << student->returnGPA() << " "
         << setw(12) << student->returnAdvisorsID() << endl;
}

void printStudentName(Student *student) {
    cout << student->returnStudentID() << ": " << student->returnName() << endl;
}

void writeStudentFile(Student *student, ofstream OFile) {
    OFile << student->returnStudentID() << "," 
            << student->returnName() << ","
            << student->returnStudentLevel() << ","
            << student->returnStudentMajor() << ","
            << student->returnGPA() << ","
            << student->returnAdvisorsID() << endl;
}

void printFacultyInfo(Faculty *faculty){
    cout << left << setw(10) << faculty->returnStudentID() << ""
         << setw(25) << faculty->returnName() << ""
         << setw(11) << faculty->returnStudentLevel() << ""
         << setw(25) << faculty->ReturnFacultiesDep() << ""
         << setw(18);
    faculty->printAdvisee();
    cout << endl;
}

void printFacultyName(Faculty *faculty) {
    cout << faculty->returnStudentID() << ": " << faculty->returnName() << endl;
}

void writeFacultyFile(Faculty *faculty, ofstream OFile) {
    OFile << faculty->returnStudentID() << ","
            << faculty->returnName() << ","
            << faculty->ReturnFacultiesDep() << ","
            << faculty->returnFacultyAdviseeWrite() << endl;
}
void DatabaseManager::printFacultyHeader(){
    cout << "----- | ------------------- |  ------- |  ---------------------- | -------------------  " << endl;
    cout << "ID:   | Name:               |  Level:  |  Department:            | Advisee IDs:         " << endl;
    cout << "----- | ------------------- |  ------- | ----------------------  | -------------------  " << endl;
}
