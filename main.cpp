#include <bits/stdc++.h>


struct Transaction {
    std::string type; // "Income" or "Expense"
    double amount;
    std::string category;
};

class FinanceManager {
private:
    std::vector<Transaction> transactions;
    double totalIncome = 0.0;
    double totalExpense = 0.0;

public:
    void addTransaction(const std::string& type, double amount, const std::string& category) {
        Transaction transaction = { type, amount, category };
        transactions.push_back(transaction);

        if (type == "Income") {
            totalIncome += amount;
        } else if (type == "Expense") {
            totalExpense += amount;
        }
    }

    void viewSummary() const {
        double balance = totalIncome - totalExpense;
        std::cout << "\n---- Financial Summary ----\n";
        std::cout << "Total Income: $" << totalIncome << "\n";
        std::cout << "Total Expense: $" << totalExpense << "\n";
        std::cout << "Balance: $" << balance << "\n";
    }

    void viewTransactions() const {
        std::cout << "\n---- All Transactions ----\n";
        std::cout << std::setw(10) << "Type" << std::setw(15) << "Amount" << std::setw(15) << "Category\n";
        for (const auto& transaction : transactions) {
            std::cout << std::setw(10) << transaction.type
                      << std::setw(15) << transaction.amount
                      << std::setw(15) << transaction.category << "\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& transaction : transactions) {
                file << transaction.type << "," << transaction.amount << "," << transaction.category << "\n";
            }
            std::cout << "Data saved to " << filename << "\n";
            file.close();
        } else {
            std::cerr << "Unable to open file.\n";
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            transactions.clear();
            totalIncome = 0.0;
            totalExpense = 0.0;

            std::string type, category;
            double amount;
            while (file >> type >> amount >> category) {
                addTransaction(type, amount, category);
            }
            file.close();
            std::cout << "Data loaded from " << filename << "\n";
        } else {
            std::cerr << "Unable to open file.\n";
        }
    }
};

void showMenu() {
    std::cout << "\n---- Finance Manager ----\n";
    std::cout << "1. Add Income\n";
    std::cout << "2. Add Expense\n";
    std::cout << "3. View Summary\n";
    std::cout << "4. View All Transactions\n";
    std::cout << "5. Save to File\n";
    std::cout << "6. Load from File\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    FinanceManager manager;
    int choice;
    std::string category, filename;
    double amount;

    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter income amount: ";
                std::cin >> amount;
                std::cout << "Enter category: ";
                std::cin >> category;
                manager.addTransaction("Income", amount, category);
                break;
            case 2:
                std::cout << "Enter expense amount: ";
                std::cin >> amount;
                std::cout << "Enter category: ";
                std::cin >> category;
                manager.addTransaction("Expense", amount, category);
                break;
            case 3:
                manager.viewSummary();
                break;
            case 4:
                manager.viewTransactions();
                break;
            case 5:
                std::cout << "Enter filename to save: ";
                std::cin >> filename;
                manager.saveToFile(filename);
                break;
            case 6:
                std::cout << "Enter filename to load: ";
                std::cin >> filename;
                manager.loadFromFile(filename);
                break;
            case 0:
                std::cout << "Exiting the program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}
