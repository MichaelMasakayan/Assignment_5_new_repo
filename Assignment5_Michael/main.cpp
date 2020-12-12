#include "DatabaseManager.hpp"
#include <fstream>

int main(int argc, char const *argv[])
{
    DatabaseManager manager;
    if (argc == 3) {
        ifstream studentInFile;
        ifstream facultyInFile;
        studentInFile.open(argv[1]);
        facultyInFile.open(argv[2]);
        manager.setUpStudentTree(argv[1]);
        manager.setUpFacultyTree(argv[2]);
    } else if (argc == 2) {
        cout << "ERROR! Cannot read Files in. Need to have 2 text files" << endl;
    }
    manager.runSimulation();

    return 0;
}
