#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

// Expense structure
struct Expense {
    int id;
    string date;
    string description;
    double amount;
};

// File to store expenses
const string FILE_NAME = "expenses.json";

// Function to get current date in YYYY-MM-DD format
string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-" 
       << setw(2) << setfill('0') << (1 + ltm->tm_mon) << "-" 
       << setw(2) << setfill('0') << ltm->tm_mday;
    return ss.str();
}

// Load expenses from file
vector<Expense> loadExpenses() {
    vector<Expense> expenses;
    ifstream file(FILE_NAME);
    if (!file.is_open()) return expenses;

    json j;
    file >> j;
    for (auto &item : j) {
        expenses.push_back({ item["id"], item["date"], item["description"], item["amount"] });
    }
    return expenses;
}

// Save expenses to file
void saveExpenses(const vector<Expense>& expenses) {
    json j;
    for (const auto& exp : expenses) {
        j.push_back({ {"id", exp.id}, {"date", exp.date}, {"description", exp.description}, {"amount", exp.amount} });
    }
    ofstream file(FILE_NAME);
    file << setw(4) << j << endl;
}

// Add expense
void addExpense(const string& description, double amount) {
    vector<Expense> expenses = loadExpenses();
    int newId = expenses.empty() ? 1 : expenses.back().id + 1;
    expenses.push_back({ newId, getCurrentDate(), description, amount });
    saveExpenses(expenses);
    cout << "Expense added successfully (ID: " << newId << ")" << endl;
}

// List expenses
void listExpenses() {
    vector<Expense> expenses = loadExpenses();
    cout << "ID  Date        Description  Amount" << endl;
    cout << "----------------------------------" << endl;
    for (const auto& exp : expenses) {
        cout << exp.id << "   " << exp.date << "   " << exp.description << "   $" << exp.amount << endl;
    }
}

// Delete expense
void deleteExpense(int id) {
    vector<Expense> expenses = loadExpenses();
    auto it = remove_if(expenses.begin(), expenses.end(), [id](const Expense& exp) { return exp.id == id; });
    
    if (it == expenses.end()) {
        cout << "Expense not found!" << endl;
        return;
    }

    expenses.erase(it, expenses.end());
    saveExpenses(expenses);
    cout << "Expense deleted successfully" << endl;
}

// Summary of all expenses
void summary() {
    vector<Expense> expenses = loadExpenses();
    double total = 0;
    for (const auto& exp : expenses) {
        total += exp.amount;
    }
    cout << "Total expenses: $" << total << endl;
}

// Summary by month
void summaryByMonth(int month) {
    vector<Expense> expenses = loadExpenses();
    double total = 0;
    for (const auto& exp : expenses) {
        int expMonth = stoi(exp.date.substr(5, 2));
        if (expMonth == month) {
            total += exp.amount;
        }
    }
    cout << "Total expenses for month " << month << ": $" << total << endl;
}

// Main function to handle CLI commands
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: expense-tracker <command> [options]" << endl;
        return 1;
    }

    string command = argv[1];

    if (command == "add") {
        if (argc < 5 || string(argv[2]) != "--description" || string(argv[4]) != "--amount") {
            cout << "Usage: expense-tracker add --description <text> --amount <value>" << endl;
            return 1;
        }
        string description = argv[3];
        double amount = stod(argv[5]);
        addExpense(description, amount);
    } 
    else if (command == "list") {
        listExpenses();
    } 
    else if (command == "delete") {
        if (argc < 4 || string(argv[2]) != "--id") {
            cout << "Usage: expense-tracker delete --id <number>" << endl;
            return 1;
        }
        int id = stoi(argv[3]);
        deleteExpense(id);
    } 
    else if (command == "summary") {
        if (argc == 4 && string(argv[2]) == "--month") {
            int month = stoi(argv[3]);
            summaryByMonth(month);
        } else {
            summary();
        }
    } 
    else {
        cout << "Invalid command!" << endl;
    }

    return 0;
}
