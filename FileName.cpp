#include <iostream>
#include <string>

using namespace std;

class Person {
private:
    string surname, initials;
    double salary, bonus, rate;
    int tariffPosition;

    const double tariffRates[25] = {
         1.0, 1.09, 1.18, 1.27, 1.36, 1.45, 1.54, 1.64, 1.73, 1.82,
        1.97, 2.12, 2.27, 2.42, 2.58, 2.79, 3.0, 3.21, 3.42, 3.64,
        3.85, 4.06, 4.27, 4.36, 4.51

    };

    void calculateRate() {
        if (tariffPosition >= 1 && tariffPosition <= 25) {
            rate = tariffRates[tariffPosition - 1];
        }
        else {
            rate = 1.0;
        }
    }

public:
    Person() : surname("Невідомий"), initials("Н.Н."), salary(0.0), bonus(0.0), rate(0.0), tariffPosition(1) {
        calculateRate();
    }

    Person(string s, string i, double sal, int tp) : surname(s), initials(i), salary(sal), tariffPosition(tp) {
        calculateRate();
        bonus = 0.0;
    }

    ~Person() {

    }

    void assignBonus(double averageSalary) {
        if (salary < averageSalary) {
            bonus = 0.5 * salary;
        }
        else {
            bonus = 0.3 * salary;
        }
    }

    double getTotalSalary() const {
        return salary + bonus;
    }

    void printInfo() const {
        cout << "\nEmployee: " << surname << " " << initials;
        cout << "\nSalary: " << salary;
        cout << "\nPremium: " << bonus;
        cout << "\nTotal salary: " << getTotalSalary();
        cout << "\nTariff position: " << tariffPosition;
        cout << "\nRate: " << rate;
        cout << "\n---------------------------------";
    }

    double getSalary() const {
        return salary;
    }
};

double calculateAverageSalary(Person** employees, int numEmployees) {
    double totalSalary = 0.0;
    for (int i = 0; i < numEmployees; ++i) {
        totalSalary += employees[i]->getSalary();
    }
    return totalSalary / numEmployees;
}

int main() {
    int numEmployees;
    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    Person** employees = new Person * [numEmployees];

    for (int i = 0; i < numEmployees; ++i) {
        string surname, initials;
        double salary;
        int tariffPosition;

        cout << "Last name of the employee: ";
        cin >> surname;
        cout << "Initials of the employee: ";
        cin >> initials;
        cout << "Employee's salary: ";
        cin >> salary;
        cout << "Position in the tariff grid (1-25): ";
        cin >> tariffPosition;

        employees[i] = new Person(surname, initials, salary, tariffPosition);
    }

    double averageSalary = calculateAverageSalary(employees, numEmployees);

    for (int i = 0; i < numEmployees; ++i) {
        employees[i]->assignBonus(averageSalary);
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Show information about all employees\n";
        cout << "2. Exit\n";
        cout << "Your choise: ";
        cin >> choice;

        switch (choice) {
        case 1:
            for (int i = 0; i < numEmployees; ++i) {
                employees[i]->printInfo();
            }
            break;
        case 2:
            cout << "Exit the program." << endl;
            break;
        default:
            cout << "Incorrect selection, try again." << endl;
        }
    } while (choice != 2);

    for (int i = 0; i < numEmployees; ++i) {
        delete employees[i];
    }
    delete[] employees;

    return 0;
}
