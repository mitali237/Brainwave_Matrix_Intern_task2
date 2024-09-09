#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account {
private:
    string accountNumber;
    string accountHolder;
    int pin;
    double balance;

public:
    Account(string number, string holder, int accountPin, double initialBalance = 0.0) {
        accountNumber = number;
        accountHolder = holder;
        pin = accountPin;
        balance = initialBalance;
    }

    string getAccountNumber() {
        return accountNumber;
    }

    string getAccountHolder() {
        return accountHolder;
    }

    bool verifyPin(int entered_pin){
        return pin == entered_pin;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Current balance: Rs." << balance << endl;
        }
        else{
            cout << "Invalid or insufficient amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Current Balance: Rs." << balance << endl;
        }
        else {
            cout << "Invalid or insufficient amount!" << endl;
        }
    }

    void transfer(Account &recipient, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            recipient.deposit(amount);
            cout << "Transferred: Rs. " << amount << " to " << recipient.getAccountHolder() << endl;
        } 
        else {
            cout << "Invalid Transaction" << endl;
        }
    }
};

class Bank {
private:
    vector<Account> accounts;

public:
    void createAccount(string number, string holder, int accountPin, double initialDeposit = 0.0) {
        Account newAccount(number, holder, accountPin, initialDeposit);
        accounts.push_back(newAccount);
        cout << "Account created successfully!! " << endl;
    }

    Account* findAccount(string number) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == number) {
                return &account;
            }
        }
        return nullptr;
    }

    void displayAccountDetails(string number, int pin) {
        Account* account = findAccount(number);
        if(account && account->verifyPin(pin)){
            cout << "Account Holder: " << account->getAccountHolder() << endl;
            cout << "Balance: " << account->getBalance() << endl;
        }
        else {
            cout << "Invalid account number or pin!" << endl;
        }
    }

    void deposit(string number, int pin, double amount) {
        Account* account = findAccount(number);
        if(account && account->verifyPin(pin)){
            account->deposit(amount);
        } 
        else {
            cout << "Invalid account number or pin!" << endl;
        }
    }

    void withdraw(string number, int pin, double amount) {
        Account* account = findAccount(number);
        if (account && account->verifyPin(pin)) {
            account->withdraw(amount);
        } 
        else {
            cout << "Invalid account number or pin!" << endl;
        }
    }

    void transfer(string fromAccountNumber, string toAccountNumber, int pin, double amount) {
        Account* fromAccount = findAccount(fromAccountNumber);
        Account* toAccount = findAccount(toAccountNumber);

        if (fromAccount && toAccount) {
            fromAccount->transfer(*toAccount, amount);
        } else {
            cout << "Invalid account details!" << endl;
        }
    }
};

int main() {
    Bank bank;
    int choice;
    int pin;
    string accountNumber, holderName, toAccountNumber;
    double amount;

    do {
        cout << "\n--- Online Banking System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Display Account Details\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Account Holder Name: ";
                cin >> holderName;
                cout << "Enter Pin: ";
                cin >> pin;
                cout << "Enter Initial Deposit: ";
                cin >> amount;
                bank.createAccount(accountNumber, holderName, pin, amount);
                break;
            case 2:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Pin: ";
                cin >> pin;
                cout << "Enter Amount to Deposit: ";
                cin >> amount;
                bank.deposit(accountNumber, pin, amount);
                break;
            case 3:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Pin: ";
                cin >> pin;
                cout << "Enter Amount to Withdraw: ";
                cin >> amount;
                bank.withdraw(accountNumber, pin, amount);
                break;
            case 4:
                cout << "Enter From Account Number: ";
                cin >> accountNumber;
                cout << "Enter To Account Number: ";
                cin >> toAccountNumber;
                cout << "Enter Pin: ";
                cin >> pin;
                cout << "Enter Amount to Transfer: ";
                cin >> amount;
                bank.transfer(accountNumber, toAccountNumber,pin, amount);
                break;
            case 5:
                cout << "Enter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Pin: ";
                cin >> pin;
                bank.displayAccountDetails(accountNumber, pin);
                break;
            case 6:
                cout << "Thank You! Have a nice day";
                exit(1);
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}