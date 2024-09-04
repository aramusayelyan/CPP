#include <iostream>
#include <vector>
#include <string>

class Account {
private:
    static int next_id;
    int account_id;
    std::string holder_name;
    std::string passport_data;
    double balance;

public:
    Account(const std::string& name, const std::string& passport, double bal)
        : holder_name(name), passport_data(passport), balance(bal) {
        account_id = next_id++;
    }

    int get_account_id() const {
        return account_id;
    }

    void set_account_id(int id) {
        account_id = id;
    }

    std::string get_holder_name() const {
        return holder_name;
    }

    void set_holder_name(const std::string& name) {
        holder_name = name;
    }

    std::string get_passport_data() const {
        return passport_data;
    }

    void set_passport_data(const std::string& data) {
        passport_data = data;
    }

    double get_balance() const {
        return balance;
    }

    void set_balance(double bal) {
        balance = bal;
    }
};

int Account::next_id = 1;

class Bank {
private:
    std::vector<Account> accounts;

public:
    void add_account(const Account& new_acc) {
        accounts.push_back(new_acc);
    }

    void list_accounts() const {
        for (const auto& account : accounts) {
            std::cout << "Account ID: " << account.get_account_id() << std::endl
                      << "Holder Name: " << account.get_holder_name() << std::endl
                      << "Passport Data: " << account.get_passport_data() << std::endl
                      << "Balance: " << account.get_balance() << std::endl
                      << "-----------------------------------" << std::endl;
        }
    }
};

int main() {
    Bank bank;
    
    bank.add_account(Account("Alice Johnson", "AB1234567", 1500.00));
    bank.add_account(Account("Bob Smith", "CD2345678", 2500.00));
    
    std::cout << "List of Accounts:" << std::endl;
    bank.list_accounts();

    return 0;
}

