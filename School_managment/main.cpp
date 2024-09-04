#include <iostream>
#include <vector>
#include <string>
int _id = 1;

class Person {
private:
    int id;
    std::string name;
    std::string surname;
    std::string type;
    int working_hours;
    double GPA;
    double salary;
    int age;

public:
    double get_GPA() {
        return GPA;
    }
    void set_GPA(const double &n) {
        GPA = n;
    }
    std::string get_name() {
        return name;
    }
    std::string get_surname() {
        return surname;
    }
    int get_age() {
        return age;
    }
    void set_name(const std::string &n) {
        name = n;
    }
    void set_surname(const std::string &n) {
        surname = n;
    }
    void set_age(const int &n) {
        age = n;
    }
    void set_id(int num) {
        id = num;
    }
    int get_id() {
        return id;
    }
    std::string get_type() {
        return type;
    }
    void set_type(const std::string &_type) {
        type = _type;
    }
    virtual double get_salary() {
        return salary;
    }
    int get_working_hours() {
        return working_hours;
    }
    void set_working_hours(int n) {
        working_hours = n;
    }
};

class School {
private:
    std::vector<Person*> persons;

public:
    void add_person(Person* tmp) {
        tmp->set_id(_id++);
        persons.push_back(tmp);
    }

    void print_persons_info() {
        for (int i = 0; i < persons.size(); i++) {
            std::cout << "Person by id " << persons[i]->get_id()
                      << std::endl
                      << std::endl
                      << "Name: " << persons[i]->get_name()
                      << std::endl
                      << "Surname: " << persons[i]->get_surname()
                      << std::endl
                      << "Type: " << persons[i]->get_type()
                      << std::endl
                      << "Age: " << persons[i]->get_age() << std::endl
                      << std::endl << std::endl;
        }
    }

    void print_students_info() {
        for (int i = 0; i < persons.size(); i++) {
            if (persons[i]->get_type() == "Student") {
                std::cout << "Person by id " << persons[i]->get_id()
                          << std::endl
                          << std::endl
                          << "Name: " << persons[i]->get_name()
                          << std::endl
                          << "Surname: " << persons[i]->get_surname()
                          << std::endl
                          << "Type: " << persons[i]->get_type()
                          << std::endl
                          << "Age: " << persons[i]->get_age() << std::endl
                          << std::endl
                          << "GPA: " << persons[i]->get_GPA() << std::endl
                          << std::endl << std::endl;
            }
        }
    }

    void print_persons_salary() {
        for (int i = 0; i < persons.size(); i++) {
            std::cout << "Person by id " << persons[i]->get_id()
                      << std::endl
                      << std::endl
                      << "Name: " << persons[i]->get_name()
                      << std::endl
                      << "Surname: " << persons[i]->get_surname()
                      << std::endl
                      << "Salary: " << persons[i]->get_salary()
                      << std::endl << std::endl;
        }
    }
};

class Student : public Person {
public:
    Student() {
        set_type("Student");
    }
    double get_salary() override {
        std::cout << "Dear student, he does not receive a salary." << std::endl;
        return {};
    }
};

class Professor : public Person {
public:
    Professor() {
        set_type("Professor");
    }
    double get_salary() override {
        return (get_working_hours() * 9);
    }
};

class Employee : public Person {
public:
    Employee() {
        set_type("Employee");
    }
    double get_salary() override {
        return (get_working_hours() * 5);
    }
};

void add_person(School &temp) {
    int option = 0;
    std::cout << "Please select the type of person you want to add to the system." << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "[ 1. Student ]" << std::endl
              << "[ 2. Professor ]" << std::endl
              << "[ 3. Employee ]" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Please enter the appropriate order number: ";
    
    do {
        std::cin >> option;
        std::cin.ignore(); 
        switch (option) {
        case 1: {
            Student *tmp = new Student();
            int age = 0;
            double gpa;

            std::string tmp_string;
            std::cout << "Please enter student name: ";
            std::getline(std::cin, tmp_string);
            tmp->set_name(tmp_string);
            std::cout << "Please enter student surname: ";
            std::getline(std::cin, tmp_string);
            tmp->set_surname(tmp_string);
            std::cout << "Enter student age: ";
            std::cin >> age;
            tmp->set_age(age);
            std::cout << "Please enter the student's most recent GPA: ";
            std::cin >> gpa;
            tmp->set_GPA(gpa);
            temp.add_person(tmp);
            break;
        }
        case 2: {
            Professor *tmp = new Professor();
            int age = 0;
            int working_hours;

            std::string tmp_string;
            std::cout << "Please enter professor name: ";
            std::getline(std::cin, tmp_string);
            tmp->set_name(tmp_string);
            std::cout << "Please enter professor surname: ";
            std::getline(std::cin, tmp_string);
            tmp->set_surname(tmp_string);
            std::cout << "Enter professor age: ";
            std::cin >> age;
            tmp->set_age(age);
            std::cout << "Please enter how much time you can devote to the job: ";
            std::cin >> working_hours;
            tmp->set_working_hours(working_hours);
            temp.add_person(tmp);
            break;
        }
        case 3: {
            Employee *tmp = new Employee();
            int age = 0;
            int working_hours;

            std::string tmp_string;
            std::cout << "Please enter employee name: ";
            std::getline(std::cin, tmp_string);
            tmp->set_name(tmp_string);
            std::cout << "Please enter employee surname: ";
            std::getline(std::cin, tmp_string);
            tmp->set_surname(tmp_string);
            std::cout << "Enter employee age: ";
            std::cin >> age;
            tmp->set_age(age);
            std::cout << "Please enter how much time you can devote to the job: ";
            std::cin >> working_hours;
            tmp->set_working_hours(working_hours);
            temp.add_person(tmp);
            break;
        }
        default:
            std::cout << "Please enter a valid number between 1 and 3." << std::endl;
            break;
        }
    } while (!(option > 0 && option < 4));
}

void active(School &temp, int option) {
    switch (option) {
        case 1: {
            add_person(temp);
            break;
        }
        case 2: {
            temp.print_persons_info();
            break;
        }
        case 3: {
            temp.print_students_info();
            break;
        }
        case 4: {
            temp.print_persons_salary();
            break;
        }
    }
}

void _commands(School &temp) {
    int option = 0;
    do {
        std::cout << "Available commands. " << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
       std::cout << "[ 1. Add person ]" << std::endl
                  << "[ 2. Print all person data ]" << std::endl
                  << "[ 3. Print all student data ]" << std::endl
                  << "[ 4. Get the salary ]" << std::endl               
                  << "[ 5. Exit]" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Please enter the appropriate order number: ";
        std::cin >> option;
        active(temp, option);
    } while (option != 5);
}

int main() {
    School school;
    _commands(school);
    return 0;
}
