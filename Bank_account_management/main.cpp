#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Account {
private:
    static int next_id;
    int account_id;
    std::string holder_name;
    std::string passport_data;
    double balance;
    std::string login;
    std::string password;

public:
    Account(const std::string& name, const std::string& passport, double bal, const std::string& user_login, const std::string& user_password)
        : holder_name(name), passport_data(passport), balance(bal), login(user_login), password(user_password) {
        account_id = next_id++;
    }

    Account() : account_id(0), balance(0.0) {}

    int get_account_id() const { return account_id; }

    std::string get_holder_name() const { return holder_name; }

    std::string get_passport_data() const { return passport_data; }

    double get_balance() const { return balance; }

    std::string get_login() const { return login; }

    std::string get_password() const { return password; }

    void set_balance(double bal) { balance = bal; }

    void save_to_file(std::ofstream& out) const {
        out << account_id << " " << holder_name << " " << passport_data << " " << balance << " " << login << " " << password << "\n";
    }

    bool load_from_file(std::ifstream& in) {
        if (in >> account_id >> holder_name >> passport_data >> balance >> login >> password)
            return true;
        return false;
    }
};

int Account::next_id = 1;

class Bank {
private:
    std::vector<Account> accounts;

    void save_account_to_file(const Account& account) {
        std::ofstream file("accounts.txt", std::ios::app);
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }
        account.save_to_file(file);
    }

public:
    void add_account(const Account& new_acc) {
        accounts.push_back(new_acc);
        save_account_to_file(new_acc);
    }

    void delete_account(int account_id) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->get_account_id() == account_id) {
                accounts.erase(it);
                std::cout << "Account deleted successfully." << std::endl;
                save_to_file();
                return;
            }
        }
        std::cout << "Account with ID " << account_id << " not found." << std::endl;
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

    Account* login(const std::string& user_login, const std::string& user_password) {
        if (user_login == "admin" && user_password == "admin") {
            std::cout << "Admin logged in!" << std::endl;
            return nullptr;
        }

        for (auto& account : accounts) {
            if (account.get_login() == user_login && account.get_password() == user_password) {
                std::cout << "Login successful for " << account.get_holder_name() << "!" << std::endl;
                return &account;
            }
        }

        std::cout << "Invalid login or password." << std::endl;
        return nullptr;
    }

    void check_balance(const Account* account) const {
        if (account) {
            std::cout << "Your balance is: $" << account->get_balance() << std::endl;
        }
    }

    void transfer_money(Account* sender, const std::string& receiver_login, double amount) {
        if (sender == nullptr) return;

        Account* receiver = nullptr;
        for (auto& account : accounts) {
            if (account.get_login() == receiver_login) {
                receiver = &account;
                break;
            }
        }

        if (receiver == nullptr) {
            std::cout << "Receiver not found!" << std::endl;
            return;
        }

        if (sender->get_balance() < amount) {
            std::cout << "Insufficient balance!" << std::endl;
            return;
        }

        sender->set_balance(sender->get_balance() - amount);
        receiver->set_balance(receiver->get_balance() + amount);
        std::cout << "Transfer successful! $" << amount << " sent to " << receiver->get_holder_name() << "." << std::endl;
    }

    void save_to_file() const {
        std::ofstream file("accounts.txt");
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        for (const auto& account : accounts) {
            account.save_to_file(file);
        }
    }

    void load_from_file() {
        std::ifstream file("accounts.txt");
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        accounts.clear();
        while (file) {
            Account account;
            if (account.load_from_file(file)) {
                accounts.push_back(account);
            }
        }
    }

    void admin_menu() {
        int choice;
        do {
            std::cout << "Admin Menu:\n1. Add Account\n2. Delete Account\n3. List Accounts\n4. Logout\n";
            std::cin >> choice;

            if (choice == 1) {
                std::string name, passport, login, password;
                double balance;

                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter passport data: ";
                std::cin >> passport;
                std::cout << "Enter login: ";
                std::cin >> login;
                std::cout << "Enter password: ";
                std::cin >> password;
                std::cout << "Enter balance: ";
                std::cin >> balance;

                add_account(Account(name, passport, balance, login, password));
                std::cout << "Account added successfully!" << std::endl;
            } else if (choice == 2) {
                int account_id;
                std::cout << "Enter account ID to delete: ";
                std::cin >> account_id;
                delete_account(account_id);
            } else if (choice == 3) {
                list_accounts();
            }
        } while (choice != 4);
    }
};

int main() {
    Bank bank;

    bank.load_from_file();

    std::string login, password;
    Account* current_account = nullptr;

    while (true) {
        std::cout << "Enter login: ";
        std::cin >> login;
        std::cout << "Enter password: ";
        std::cin >> password;

        current_account = bank.login(login, password);

        if (login == "admin" && password == "admin") {
            bank.admin_menu();
        } else if (current_account != nullptr) {
            int choice;
            do {
                std::cout << "1. Check Balance\n2. Transfer Money\n3. Logout\n";
                std::cin >> choice;

                if (choice == 1) {
                    bank.check_balance(current_account);
                } else if (choice == 2) {
                    std::string receiver_login;
                    double amount;
                    std::cout << "Enter receiver's login: ";
                    std::cin >> receiver_login;
                    std::cout << "Enter amount to transfer: ";
                    std::cin >> amount;
                    bank.transfer_money(current_account, receiver_login, amount);
                }
            } while (choice != 3);
        }

        std::cout << "Logged out." << std::endl;

        std::cout << "Would you like to exit the program? (y/n): ";
        char exit_choice;
        std::cin >> exit_choice;
        if (exit_choice == 'y') {
            bank.save_to_file();
            break;
        }
    }

    return 0;
}

