#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void addStudent() {
        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Student Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Course: ";
        getline(cin, course);

        ofstream file("students.dat", ios::app | ios::binary);
        file.write(reinterpret_cast<char*>(this), sizeof(*this));
        file.close();

        cout << "\nStudent added successfully!\n";
    }

    void displayStudents() {
        ifstream file("students.dat", ios::in | ios::binary);
        if (!file) {
            cout << "No records found!\n";
            return;
        }

        cout << "\nList of Students:\n";
        while (file.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            cout << "ID: " << id
                 << ", Name: " << name
                 << ", Age: " << age
                 << ", Course: " << course << endl;
        }
        file.close();
    }

    void searchStudent(int searchId) {
        ifstream file("students.dat", ios::in | ios::binary);
        bool found = false;

        while (file.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (id == searchId) {
                cout << "\nStudent Found!"
                     << "\nID: " << id
                     << "\nName: " << name
                     << "\nAge: " << age
                     << "\nCourse: " << course << endl;
                found = true;
                break;
            }
        }
        file.close();
        if (!found) cout << "\nStudent not found!\n";
    }

    void updateStudent(int updateId) {
        fstream file("students.dat", ios::in | ios::out | ios::binary);
        bool found = false;
        int pos = 0;

        while (file.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (id == updateId) {
                cout << "\nStudent found! Enter new details:";
                cout << "\nEnter Student Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Student Age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter Course: ";
                getline(cin, course);

                file.seekp(pos * sizeof(*this), ios::beg);
                file.write(reinterpret_cast<char*>(this), sizeof(*this));
                cout << "\nStudent updated successfully!";
                found = true;
                break;
            }
            pos++;
        }
        file.close();
        if (!found) cout << "\nStudent not found!\n";
    }

    void deleteStudent(int deleteId) {
        ifstream file("students.dat", ios::in | ios::binary);
        ofstream tempFile("temp.dat", ios::out | ios::binary);

        bool found = false;
        while (file.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            if (id == deleteId) {
                cout << "\nStudent deleted successfully!";
                found = true;
            } else {
                tempFile.write(reinterpret_cast<char*>(this), sizeof(*this));
            }
        }
        file.close();
        tempFile.close();

        remove("students.dat");
        rename("temp.dat", "students.dat");

        if (!found) cout << "\nStudent not found!\n";
    }
};

int main() {
    Student student;
    int choice, id;

    while (true) {
        cout << "\n--- Student Management System ---";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student by ID";
        cout << "\n4. Update Student by ID";
        cout << "\n5. Delete Student by ID";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                student.addStudent();
                break;
            case 2:
                student.displayStudents();
                break;
            case 3:
                cout << "Enter Student ID to search: ";
                cin >> id;
                student.searchStudent(id);
                break;
            case 4:
                cout << "Enter Student ID to update: ";
                cin >> id;
                student.updateStudent(id);
                break;
            case 5:
                cout << "Enter Student ID to delete: ";
                cin >> id;
                student.deleteStudent(id);
                break;
            case 6:
                cout << "Exiting program.";
                return 0;
            default:
                cout << "Invalid choice! Try again.";
        }
    }
}
