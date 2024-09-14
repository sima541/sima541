#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account {
private:
    string accountNumber;
    string accountHolder;
    double balance;

public:
    // Constructor to initialize account details
    Account(string accNum, string holder, double initialBalance) {
        accountNumber = accNum;
        accountHolder = holder;
        balance = initialBalance;
    }

    // Deposit method
    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: $" << amount << ". New balance: $" << balance << endl;
    }

    // Withdraw method
    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        } else {
            balance -= amount;
            cout << "Withdrawn: $" << amount << ". New balance: $" << balance << endl;
            return true;
        }
    }

    // Transfer method
    bool transfer(Account &toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            cout << "Transferred $" << amount << " to " << toAccount.getAccountHolder() << endl;
            return true;
        }
        return false;
    }

    // Display account details
    void showAccountInfo() const {
        cout << "Account Holder: " << accountHolder << ", Account Number: " << accountNumber << ", Balance: $" << balance << endl;
    }

    // Getter for account holder
    string getAccountHolder() const {
        return accountHolder;
    }

    // Getter for balance
    double getBalance() const {
        return balance;
    }
};

class Bank {
private:
    vector<Account> accounts;  // List of bank accounts

public:
    // Create a new account
    void createAccount(string accNum, string holder, double initialBalance) {
        Account newAccount(accNum, holder, initialBalance);
        accounts.push_back(newAccount);
        cout << "Account created for " << holder << " with initial balance $" << initialBalance << endl;
    }

    // Find account by account number
    Account* findAccount(const string &accNum) {
        for (auto &account : accounts) {
            if (account.getAccountHolder() == accNum) {
                return &account;
            }
        }
        cout << "Account not found!" << endl;
        return nullptr;
    }

    // Display all accounts
    void displayAllAccounts() const {
        cout << "All Accounts in the Bank:" << endl;
        for (const auto &account : accounts) {
            account.showAccountInfo();
        }
    }
};

int main() {
    Bank bank;
    int choice;
    string accNum, accHolder;
    double amount;

    // Creating sample accounts
    bank.createAccount("10021", "Sima", 50000.0);
    bank.createAccount("1002", "Simmy", 306500.0);
    bank.createAccount("10501", "Manshi", 500560.0);
    bank.createAccount("10032", "Trisha", 300800.0);

    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Transfer\n4. Show Account Info\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account holder's name for deposit: ";
                cin >> accHolder;
                if (Account* acc = bank.findAccount(accHolder)) {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    acc->deposit(amount);
                }
                break;

            case 2:
                cout << "Enter account holder's name for withdrawal: ";
                cin >> accHolder;
                if (Account* acc = bank.findAccount(accHolder)) {
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    acc->withdraw(amount);
                }
                break;

            case 3:
                cout << "Enter account holder's name to transfer from: ";
                cin >> accHolder;
                if (Account* fromAcc = bank.findAccount(accHolder)) {
                    string toAccHolder;
                    cout << "Enter account holder's name to transfer to: ";
                    cin >> toAccHolder;
                    if (Account* toAcc = bank.findAccount(toAccHolder)) {
                        cout << "Enter amount to transfer: ";
                        cin >> amount;
                        fromAcc->transfer(*toAcc, amount);
                    }
                }
                break;

            case 4:
                bank.displayAllAccounts();
                break;

            case 5:
                cout << "Exiting the program..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

