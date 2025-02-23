# Expense-Tracker-CLI

A simple expense tracker using C++
[Road map](https://roadmap.sh/projects/expense-tracker)

## Project Overview

A CLI-based Expense Tracker that lets users manage their expenses by adding, deleting, updating, and summarizing them. The data will be stored in a file (JSON or CSV), and users can interact with the program using command-line arguments.

## Features

- Add new expenses with a description and amount.
- List all recorded expenses.
- Delete expenses by their ID.
- Display a summary of total expenses.
- Show expenses for a specific month.
- Interactive CLI that allows real-time user input.

## Getting Started

### Prerequisites

- Ensure you have the following installed on your system:
- A C++ compiler (e.g., g++ for GCC)
- nlohmann/json library for JSON handling

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/Expense-Tracker-CLI.git
    cd Expense-Tracker-CLI
    ```

2. Compile the program:

    ```bash
    g++ -o expense-tracker main.cpp -std=c++11
    ```

### Usage

Run the program:

```bash
./Expense_Tracker.exe 
```

Once started, use the following commands:

```bash
Commands:
  add "description" amount  - Add a new expense
  list                      - List all expenses
  delete id                 - Delete an expense by ID
  summary                   - Show total expenses
  summary month             - Show expenses for a specific month
  clear                     - clears the screen
  exit                      - Quit the program
```

### Example Usage

#### Adding an expense

```bash
expense-tracker add "Gym membership" 2000
Expense added successfully (ID: 1)

expense-tracker add "Taxi" 200
Expense added successfully (ID: 2)
```

#### Listing expenses

```bash
expense-tracker list
ID  Date        Description  Amount
----------------------------------
1   2025-02-23   Gym membership   2000 ETB
2   2025-02-23   Taxi   200 ETB
```

#### Deleting an expense

```bash
expense-tracker delete 2
Expense deleted successfully
```

#### Viewing summary

```bash
expense-tracker list
ID  Date        Description  Amount
----------------------------------
1   2025-02-23   Gym membership   2000 ETB
```

#### Viewing summary for a specific month

```bash
expense-tracker summary 2
Total expenses for month 2: 2000 ETB
```

## Future Improvements

- Support for exporting expenses to CSV.
- Ability to categorize expenses.
- Advanced filtering and reporting features.

## Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you would like to change.

--------------------------------------------------------------

### Author

Daniot Mihrete - GitHub Profile
