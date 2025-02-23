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
struct Expense
{
    int id;
    string date;
    string description;
    double amount;
};

// File to store expenses
const string FILE_NAME = "expenses.json";

// Function to get current date in YYYY-MM-DD format
string getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << setw(2) << setfill('0') << (1 + ltm->tm_mon) << "-"
       << setw(2) << setfill('0') << ltm->tm_mday;
    return ss.str();
}

// Load expenses from file
vector<Expense> loadExpenses()
{
    vector<Expense> expenses;
    ifstream file(FILE_NAME);
    if (!file.is_open())
        return expenses;

    json j;
    file >> j;
    for (auto &item : j)
    {
        expenses.push_back({item["id"], item["date"], item["description"], item["amount"]});
    }
    return expenses;
}

// Save expenses to file
void saveExpenses(const vector<Expense> &expenses)
{
    json j;
    for (const auto &exp : expenses)
    {
        j.push_back({{"id", exp.id}, {"date", exp.date}, {"description", exp.description}, {"amount", exp.amount}});
    }
    ofstream file(FILE_NAME);
    file << setw(4) << j << endl;
}

// Add expense
void addExpense(const string &description, double amount)
{
    vector<Expense> expenses = loadExpenses();
    int newId = expenses.empty() ? 1 : expenses.back().id + 1;
    expenses.push_back({newId, getCurrentDate(), description, amount});
    saveExpenses(expenses);
    cout << "Expense added successfully (ID: " << newId << ")" << endl;
}

// List expenses
void listExpenses()
{
    vector<Expense> expenses = loadExpenses();
    cout << "ID  Date        Description  Amount" << endl;
    cout << "----------------------------------" << endl;
    for (const auto &exp : expenses)
    {
        cout << exp.id << "   " << exp.date << "   " << exp.description << "   " << exp.amount << " ETB" << endl;
    }
}

// Delete expense
void deleteExpense(int id)
{
    vector<Expense> expenses = loadExpenses();
    auto it = remove_if(expenses.begin(), expenses.end(), [id](const Expense &exp)
                        { return exp.id == id; });

    if (it == expenses.end())
    {
        cout << "Expense not found!" << endl;
        return;
    }

    expenses.erase(it, expenses.end());
    saveExpenses(expenses);
    cout << "Expense deleted successfully" << endl;
}

// Summary of all expenses
void summary()
{
    vector<Expense> expenses = loadExpenses();
    double total = 0;
    for (const auto &exp : expenses)
    {
        total += exp.amount;
    }
    cout << "Total expenses: $" << total << endl;
}

// Summary by month
void summaryByMonth(int month)
{
    vector<Expense> expenses = loadExpenses();
    double total = 0;
    for (const auto &exp : expenses)
    {
        int expMonth = stoi(exp.date.substr(5, 2));
        if (expMonth == month)
        {
            total += exp.amount;
        }
    }
    cout << "Total expenses for month " << month << ": $" << total << endl;
}

void printBanner()
{
    cout << "Welcome to Expense Tracker CLI!" << endl;
    cout << "Type 'help' for a list of commands or 'exit' to quit." << endl;
    cout << R"(
     ___                              _____            _           
    | __|_ ___ __  ___ _ _  ___ ___  |_   _| _ __ _ __| |_____ _ _ 
    | _|\ \ / '_ \/ -_) ' \(_-</ -_)   | || '_/ _` / _| / / -_) '_|
    |___/_\_\ .__/\___|_||_/__/\___|   |_||_| \__,_\__|_\_\___|_|  
            |_|                                                    
    )" << endl;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Main function to handle CLI commands
int main()
{
    printBanner();
    string input;
    while (true)
    {
        cout << "\nexpense-tracker "; // CLI prompt
        getline(cin, input);

        // Trim spaces (optional)
        input.erase(0, input.find_first_not_of(" "));
        input.erase(input.find_last_not_of(" ") + 1);

        if (input == "exit")
        {
            cout << "Goodbye!" << endl;
            break;
        }
        else if (input == "help")
        {
            cout << "\nCommands:\n"
                 << "  add <description> <amount>   - Add a new expense\n"
                 << "  list                        - List all expenses\n"
                 << "  delete <id>                 - Delete an expense by ID\n"
                 << "  summary                     - Show total expenses\n"
                 << "  summary <month>             - Show expenses for a specific month\n"
                 << "  clear                       - clears the screen."
                 << "  exit                        - Quit the program\n";
        }
        else if (input.rfind("add ", 0) == 0)
        {
            stringstream ss(input.substr(4)); // Remove "add "
            string description;
            double amount;
            if (ss >> quoted(description) >> amount)
            {
                addExpense(description, amount);
            }
            else
            {
                cout << "Usage: add \"description\" amount" << endl;
            }
        }
        else if (input == "list")
        {
            listExpenses();
        }
        else if (input.rfind("delete ", 0) == 0)
        {
            int id = stoi(input.substr(7));
            deleteExpense(id);
        }
        else if (input == "summary")
        {
            summary();
        }
        else if (input.rfind("summary ", 0) == 0)
        {
            int month = stoi(input.substr(8));
            summaryByMonth(month);
        }
        else if (input == "clear")
        {
            clearScreen();
            printBanner();
        }
        else
        {
            cout << "Invalid command! Type 'help' for a list of commands." << endl;
        }
    }

    return 0;
}

