#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <string>

using namespace std;

class Person {
public:
    virtual string getInfo() const = 0;
    virtual ~Person() = default;
};

class Student : public Person {
private:
    string name;
    string phone;
    string speciality;
public:
    Student(const string& n, const string& p, const string& s)
        : name(n), phone(p), speciality(s) {}

    string getInfo() const override {
        return "Студент: " + name + ", телефон " + phone + ", специальность " + speciality;
    }
};
class Teacher : public Person {
private:
    string name;
    string phone;
    string subject;
public:
    Teacher(const string& n, const string& p, const string& s)
        : name(n), phone(p), subject(s) {}

    string getInfo() const override {
        return "Преподаватель " + name + ", телефон " + phone + ", предмет " + subject;
    }
};

class Colleague : public Person {
private:
    string name;
    string phone;
    string email;
public:
    Colleague(const string& n, const string& p, const string& e)
        : name(n), phone(p), email(e) {}

    string getInfo() const override {
        return "Коллега " + name + ", телефон " + phone + ", почта " + email;
    }
};

class PersonDecorator : public Person {
protected:
    shared_ptr<Person> person;

public:
    PersonDecorator(shared_ptr<Person> p) : person(p) {}

    string getInfo() const override {
        return person->getInfo();
    }
};

class BirthDecorator : public PersonDecorator {
private:
    string birthday;

public:
    BirthDecorator(shared_ptr<Person> p, const string& bd) : PersonDecorator(p), birthday(bd) {}

    string getInfo() const override {
        return PersonDecorator::getInfo() + ", дата рождения " + birthday;
    }
};

class AddressBook {
private:
    vector<shared_ptr<Person>> people;

    AddressBook() {}

public:
    static AddressBook& getInstance() {
        static AddressBook instance;
        return instance;
    }

    AddressBook(const AddressBook&) = delete;
    AddressBook& operator=(const AddressBook&) = delete;

    void addPerson(shared_ptr<Person> person) {
        people.push_back(person);
    }

    void saveFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& person : people) {
                file << person->getInfo() << endl;
            }
            file.close();
        }
        else {
            cout << "Не удалось сделать запись" << endl;
        }
    }

    void printAll() const {
        for (const auto& person : people) {
            cout << person->getInfo() << endl;
        }
    }
};

class UserInterface {
public:
    void run() {
        AddressBook& addressBook = AddressBook::getInstance();
        int choice;

        while (true) {
            cout << "1 Добавить студента\n";
            cout << "2 Добавить преподавателя\n";
            cout << "3 Добавить коллегу\n";
            cout << "4 Показать всех людей\n";
            cout << "5 Сохранить в файл\n";
            cout << "6 Выйти\n";
            cout << "Выберите номер действия ";
            cin >> choice;

            if (choice == 6) break;

            string name, phone, extra, birthday;
            shared_ptr<Person> person;

            if (choice >= 1 && choice <= 3) {
                cout << "Введите имя ";
                cin.ignore();
                getline(cin, name);
                cout << "Введите телефон ";
                getline(cin, phone);

                switch (choice) {
                case 1:
                    cout << "Введите специальность ";
                    getline(cin, extra);
                    person = make_shared<Student>(name, phone, extra);
                    break;
                case 2:
                    cout << "Введите предмет ";
                    getline(cin, extra);
                    person = make_shared<Teacher>(name, phone, extra);
                    break;
                case 3:
                    cout << "Введите электронную почту ";
                    getline(cin, extra);
                    person = make_shared<Colleague>(name, phone, extra);
                    break;
                }

                cout << "Хотите добавить дату рождения? (1 - да, 2 - нет): ";
                cin >> choice;
                if (choice == 1) {
                    cout << "Введите дату рождения ";
                    cin.ignore();
                    getline(cin, birthday);
                    person = make_shared<BirthDecorator>(person, birthday);
                }

                addressBook.addPerson(person);

            }
            else if (choice == 4) {
                addressBook.printAll();
            }
            else if (choice == 5) {
                addressBook.saveFile("addressBook.txt");
                cout << "Сохранено в addressBook.txt\n";
            }
        }
    }
};

int main() {
    system("chcp 1251");
    UserInterface ui;
    ui.run();
    return 0;
}