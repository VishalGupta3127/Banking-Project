#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class BankAccount {
private:
    string holderName;
    long accountNumber;
    float balance;

public:
    void createAccount() {
        cout << "Enter Account Holder Name: ";
        cin >> holderName;

        accountNumber = rand() % 900000 + 100000; // 6-digit account number
        balance = 0;

        saveToFile();

        cout << "\n Account Created Successfully!";
        cout << "\nYour Account Number is: " << accountNumber << endl;
    }

    bool loadAccount(long accNo) {
        string filename = "acc" + to_string(accNo) + ".txt";
        ifstream fin(filename);

        if (!fin)
            return false;

        accountNumber = accNo;
        fin >> holderName;
        fin >> balance;

        fin.close();
        return true;
    }

    void saveToFile() {
        string filename = "acc" + to_string(accountNumber) + ".txt";
        ofstream fout(filename);

        fout << holderName << endl;
        fout << balance;

        fout.close();
    }

    void deposit() {
        float amount;
        cout << "\nEnter amount to deposit: ";
        cin >> amount;

        if (amount > 0) {
            balance += amount;
            saveToFile();
            cout << " Deposit Successful!";
        } else {
            cout << " Invalid Amount!";
        }
    }

    void withdraw() {
        float amount;
        cout << "\nEnter amount to withdraw: ";
        cin >> amount;

        if (amount > balance) {
            cout << " Insufficient Balance!";
        } else {
            balance -= amount;
            saveToFile();
            cout << " Withdrawal Successful!";
        }
    }

    void checkBalance() {
        cout << "\n===== ACCOUNT DETAILS =====";
        cout << "\nName: " << holderName;
        cout << "\nAccount No: " << accountNumber;
        cout << "\nBalance: ₹" << balance;
        cout << "\n===========================" << endl;
    }
};

int main() {
    srand(time(0)); // initialize random seed

    BankAccount acc;
    int option;

    cout << "======  BIGBANK ======\n";
    cout << "1. Create New Account\n";
    cout << "2. Login Existing Account\n";
    cout << "Enter choice: ";
    cin >> option;

    if (option == 1) {
        acc.createAccount();
    }
    else if (option == 2) {
        long accNo;
        cout << "Enter Account Number: ";
        cin >> accNo;

        if (!acc.loadAccount(accNo)) {
            cout << "\n Account Not Found!" << endl;
            return 0;
        }

        cout << "\n Login Successful!";
    }
    else {
        cout << "\n Invalid Option!";
        return 0;
    }

    int choice;
    do {
        cout << "\n\n1. Deposit";
        cout << "\n2. Withdraw";
        cout << "\n3. Check Balance";
        cout << "\n4. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: acc.deposit(); break;
            case 2: acc.withdraw(); break;
            case 3: acc.checkBalance(); break;
            case 4: cout << "\nThank you for using BIGBANK!"; break;
            default: cout << "\nInvalid Choice!";
        }

    } while(choice != 4);

    return 0;
}