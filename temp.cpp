#include <iostream>
#include<conio.h>  //for _getch()
#include <vector>
#include <iomanip>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

using namespace std;

// Global variables
int totalEarnings = 0; // Total earnings of the coffee shop

// Node structure for Queue
struct QueueNode {
    pair<string, int> order;
    QueueNode* next;
};
// Node structure for Stack
struct StackNode {
    string order;
    StackNode* next;
};
// Custom Queue Implementation
class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (!empty()) {
            pop();
        }
    }

    void push(pair<string, int> order) {
        QueueNode* newNode = new QueueNode{ order, nullptr };
        if (rear) {
            rear->next = newNode;
        }
        else {
            front = newNode;
        }
        rear = newNode;
    }
    void pop() {
        if (front) {
            QueueNode* temp = front;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete temp;
        }
    }

    pair<string, int> frontOrder() {
        return front->order;
    }
    bool empty() {
        return front == nullptr;
    }
    // Method to display current orders
    void displayOrders() {
        if (empty()) {
            cout << "No current orders in the queue.\n";
            return;
        }
        cout << "Current Orders in Queue:\n";
        QueueNode* current = front;
        int index = 1;
        while (current) {
            cout << index++ << ". " << current->order.second << " x " << current->order.first << endl;
            current = current->next;
        }
    }
    //Get the size
    int size() {
        size_t count = 0;
        QueueNode* current = front;
        while (current) {
            count++;
            current = current->next;
        }
        return static_cast<int>(count);
    }


    // Get order at specific position
    pair<string, int> getOrderAt(int index) {
        QueueNode* current = front;
        for (int i = 0; i < index && current; i++) {
            current = current->next;
        }
        return current ? current->order : make_pair("", 0);
    }
};
// Custom Stack Implementation
class Stack {
private:
    StackNode* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }
    void push(string order) {
        StackNode* newNode = new StackNode{ order, top };
        top = newNode;
    }
    void pop() {
        if (top) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
    string topOrder() {
        return top->order;
    }

    bool empty() {
        return top == nullptr;
    }
};
// Coffee Shop Class
class CoffeeShop {
private:
    vector<string> menu;                  // Menu items
    vector<float> price;                  // Prices of items
    Queue orderQueue;                     // Queue for placed orders (item, quantity)
    Stack undoStack;                      // Stack for canceled orders

    string adminUsername = "admin";       // Default admin username
    string adminPassword = "password";    // Default admin password
    const string ordersFile = "orders.txt"; // File to store orders
    const string earningsFile = "earnings.txt"; // File to store total earnings

public:
    CoffeeShop() {
        // Initialize menu and prices
        menu = { "Espresso", "Flat White", "Cappuccino", "Black Coffee", "Americano",
                "Cold Coffee", "Frappe", "Affogato", "Coffee Latte", "Irish Coffee" };
        price = { 200.0f, 300.0f, 250.0f, 350.0f, 400.0f, 150.0f, 500.0f, 550.0f, 600.0f, 700.0f };

        // Load total earnings from file
        ifstream inFile(earningsFile);
        if (inFile.is_open()) {
            inFile >> totalEarnings;  // Load total earnings from file
            inFile.close();
        }
        // Load previous orders from file
        loadOrdersFromFile();
    }
    // Load previous orders from the orders file
    void loadOrdersFromFile() {
        ifstream inFile(ordersFile);
        string line;
        while (getline(inFile, line)) {
            int quantity;
            string coffeeName;
            istringstream stream(line);
            stream >> quantity;
            getline(stream, coffeeName);
            coffeeName = trim(coffeeName); // Remove leading/trailing spaces
            if (!coffeeName.empty()) {
                orderQueue.push({ coffeeName, quantity });
            }
        }
        inFile.close();
    }
    // Trim leading and trailing spaces from a string
    string trim(const string& str) {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
    }

    // Save order to file
    void saveOrderToFile(const string& coffeeName, int quantity) {
        ofstream outFile(ordersFile, ios::app);
        if (outFile.is_open()) {
            outFile << quantity << " x " << coffeeName << endl;
            outFile.close();
        }
        else {
            cout << "Error: Unable to save the order.\n";
        }
    }
    // Save total earnings to file
    void saveTotalEarnings() {
        ofstream outFile(earningsFile);
        if (outFile.is_open()) {
            outFile << totalEarnings << endl; // Save earnings to the file
            outFile.close();
        }
    }
    // Display a greeting screen
    void greeting() {

        cout << MAGENTA << "\n\n\n\n\n\n\t\t\t\tP L E A S E       W A I T\n" << RESET << endl;
        cout << MAGENTA << "\n\t\t\t\t     L O A D I N G" << RESET << endl;
        cout << "\n\n\t\t";
        for (int i = 0; i <= 60; i++) {
            char c = 219;
            Sleep(15);
            cout << MAGENTA << c << RESET;
            Sleep(50);
        }
        system("CLS");
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t" << MAGENTA << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *" << RESET << WHITE << "      W  E  L  C  O  M  E      " << RESET << MAGENTA << "* *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *" << RESET << WHITE << "            T O                " << RESET << MAGENTA << "* *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *" << RESET << WHITE << "    C O F F E E    S H O P     " << RESET << MAGENTA << "* *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
        cout << "\t\t\t\t\t" << MAGENTA << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
        Sleep(2000);
    }

    // Display menu in table format
    void displayMenu() {
        system("CLS");
        cout << "\n\n\n\n\n\n\n\n";

        cout << "\t\t\t\t\t                       ---(Coffee Menu)---                       " << endl;
        cout << "\t\t\t\t\t" << endl;
        cout << "\t\t\t\t\t" << BLUE << "-----------------------------------------------------------------" << RESET << endl;
        cout << BLUE << "\t\t\t\t\t|\t" << RESET << YELLOW << "Coffee No.\t" << RESET << BLUE << "|" << RESET << YELLOW << "\tCoffee Name\t" << RESET << BLUE << "|" << RESET << YELLOW << "Price(Rs)\t" << RESET << BLUE << "|" << RESET << endl;
        for (size_t i = 0; i < menu.size(); i++) {
            cout << "\t\t\t\t\t" << BLUE << "-----------------------------------------------------------------" << RESET << endl;
            cout << BLUE << "\t\t\t\t\t|" << RESET << setw(5) << i + 1 << setw(25) << BLUE "||" << RESET << menu[i] << "\t\t" << BLUE "|| " << RESET << setw(10) << price[i] << "\t" << BLUE << "|" << RESET << endl;
        }
        cout << "\t\t\t\t\t" << BLUE << "-----------------------------------------------------------------" << RESET << endl;
        cout << "\t\t\t\t\t" << endl;
        Sleep(3000);
    }
    // Add an order
    void addOrder() {
        char moreOrders = 'y'; // Variable to check if user wants to order more
        do {
            displayMenu();
            int choice, quantity;
            cout << "\t\t\t\t\tEnter the number of the coffee you want to order: ";
            cin >> choice;

            if (choice >= 1 && choice <= (int)menu.size()) {
                cout << "\t\t\t\t\tEnter the quantity: ";
                cin >> quantity;

                if (quantity > 0) {
                    orderQueue.push({ menu[choice - 1], quantity });
                    saveOrderToFile(menu[choice - 1], quantity); // Save order to file
                    cout << "\t\t\t\t\tAdded " << quantity << " x " << menu[choice - 1] << " to your order.\n";
                }
                else {
                    cout << "\t\t\t\t\tInvalid quantity. Order not added.\n";
                }
            }
            else {
                cout << "\t\t\t\t\tInvalid choice. Try again.\n";
            }

            // Ask if the user wants to order more
            cout << "\t\t\t\t\tDo you want to order more? (y/n): ";
            cin >> moreOrders;
            moreOrders = tolower(moreOrders); // Handle case sensitivity

        } while (moreOrders == 'y'); // Loop until user says no

        cout << "\t\t\t\t\tThank you for your order!\n";
    }

    // Cancel an order
    void cancelOrder() {
        if (orderQueue.empty()) {
            cout << "\t\t\t\t\tNo orders to cancel.\n";
            return;
        }

        orderQueue.displayOrders();
        int orderNumber;
        cout << "\t\t\t\t\tEnter the order number to cancel: ";
        cin >> orderNumber;

        if (orderNumber < 1 || orderNumber > orderQueue.size()) {
            cout << "\t\t\t\t\tInvalid order number.\n";
            return;
        }


        auto orderToCancel = orderQueue.getOrderAt(orderNumber - 1);
        orderQueue.pop(); // Remove the order from the queue
        undoStack.push("Cancelled: " + to_string(orderToCancel.second) + " x " + orderToCancel.first); // Push the canceled order to the undo stack
        cout << "\t\t\t\t\tCancelled: " << orderToCancel.second << " x " << orderToCancel.first << endl; // Display confirmation message


        vector<pair<string, int>> orders;
        ifstream inFile(ordersFile);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                int quantity;
                string coffeeName;
                istringstream stream(line);
                stream >> quantity;
                getline(stream, coffeeName);
                coffeeName = trim(coffeeName); // Remove leading/trailing spaces
                if (!coffeeName.empty()) {
                    orders.push_back({ coffeeName, quantity });
                }
            }
            inFile.close();
        }


        orders.erase(remove_if(orders.begin(), orders.end(), [&](const pair<string, int>& order) {
            return order.first == orderToCancel.first && order.second == orderToCancel.second;
            }), orders.end());


        ofstream outFile(ordersFile);
        if (outFile.is_open()) {
            for (const auto& order : orders) {
                outFile << order.second << " x " << order.first << endl;
            }
            outFile.close();
        }
        else {
            cout << "\t\t\t\t\tError: Unable to update the orders file.\n";
        }
    }

    // Display receipt and calculate total
    void displayReceipt() {
        if (orderQueue.empty()) {
            cout << "\t\t\t\t\tNo orders to display.\n";
            return;
        }
        int total = 0;
        cout << "\n\n";
        cout << "\t\t\t\t\t                            ---(Receipt)---                       " << endl;
        cout << "\t\t\t\t\t" << BLUE << "-------------------------------------------------------------------------" << RESET << endl;
        cout << BLUE << "\t\t\t\t\t|\t" << RESET << YELLOW << "No.\t" << RESET << BLUE << "|" << RESET << YELLOW << "\tCoffee Name\t" << RESET << BLUE << "|" << RESET << YELLOW << "\tQty\t" << RESET << BLUE << "|" << RESET << YELLOW << "Price(Rs)\t" << RESET << BLUE << "|" << RESET << endl;
        cout << "\t\t\t\t\t" << BLUE << "-------------------------------------------------------------------------" << RESET << endl;
        int count = 1;
        Queue tempQueue = orderQueue; // Create a copy of the queue
        while (!tempQueue.empty()) {
            auto order = tempQueue.frontOrder();
            tempQueue.pop();
            int index = findMenuIndex(order.first);
            if (index != -1) { // Check if the index is valid

                int cost = static_cast<int>(price[index] * order.second);
                total += cost;
                cout << BLUE << "\t\t\t\t\t|" << RESET << setw(5) << count++ << BLUE "\t\t||" << RESET << setw(10) << order.first << "\t\t" << BLUE "||" << RESET << setw(10) << order.second << BLUE << "\t\t||" << RESET << cost << BLUE << "\t\t|" << RESET << endl;
            }
           // else {
              //  cout << BLUE << "\t\t\t\t\t|" << RESET << setw(5) << count++ << BLUE "\t\t||" << RESET << setw(10) << order.first << "\t\t" << BLUE "|| " << RESET << setw(10) << order.second << BLUE << "\t||" << RESET << "N/A" << BLUE << "\t\t|" << RESET << endl;
           // }
        }
        cout << "\t\t\t\t\t" << BLUE << "------------------------------------------------------------------------" << RESET << endl;
        cout << setw(35) << GREEN << "\t\t\t\t\t\tTotal: " << RESET << total << " Rs." << endl;
        totalEarnings += total; // Update total earnings
        saveTotalEarnings(); // Save updated earnings
    }
    // Admin login

    bool adminLogin() {
        string username, password;
        int attempts = 3;

        while (attempts--) {
            cout << "\t\t\t\t\tEnter admin username: ";
            cin >> username;

            cout << "\t\t\t\t\tEnter admin password: ";
            password = ""; // Reset password for each attempt
            char ch;

            while ((ch = _getch()) != '\r') { // '\r' is the Enter key
                if (ch == '\b' && !password.empty()) { // Handle backspace
                    cout << "\b \b"; // Erase last character
                    password.pop_back();
                }
                else if (ch != '\b') {
                    cout << '*'; // Display asterisks
                    password += ch;
                }
            }
            cout << endl;

            if (username == adminUsername && password == adminPassword) {
                cout << "\033[32m\t\t\t\t\tLogin successful!\033[0m" << endl; // GREEN
                Sleep(500);
                return true;
            }
            else {
                cout << "\t\t\t\t\tIncorrect username or password. Attempts remaining: " << attempts << endl;
                if (attempts > 0) {
                    string retry;
                    cout << "\t\t\t\t\tDo you want to retry? (yes/no): ";
                    cin >> retry;
                    if (retry != "yes") break;
                }
            }
        }
        cout << "\t\t\t\t\tAccess denied. Returning to main menu.\n";
        return false;
    }



    // View total orders from file
    void viewTotalOrders() {
        ifstream inFile(ordersFile);
        cout << "\n\t\t\t\t\t--- Total Orders ---\n\n";
        if (inFile.is_open()) {
            string order;
            while (getline(inFile, order)) {
                cout << "\t\t\t\t\t" << order << endl;
            }
            inFile.close();
        }
        else {
            cout << "\t\t\t\t\tNo orders placed yet.\n";
        }
    }

    // Admin Panel
    void adminPanel() {
        if (!adminLogin()) return;

        int choice;
        system("CLS");
        do {
            cout << "\n\n\n\n\n\n\n\n";
            cout << "\t\t\t\t\t          ---(Admin Panel)---        \n";
            cout << "\t\t\t\t\t" << YELLOW << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *                               * *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *                               * *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *                               * *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *" << RESET << WHITE << "    1. View Total Orders       " << RESET << YELLOW << "* *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *" << RESET << WHITE << "    2. View Earnings           " << RESET << YELLOW << "* *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *" << RESET << WHITE << "    3. Change Coffee Prices    " << RESET << YELLOW << "* *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *" << RESET << WHITE << "    4. Log Out                 " << RESET << YELLOW << "* *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *                               * *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *                               * *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* *                               * *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
            cout << "\t\t\t\t\t" << YELLOW << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;

            cout << "\n\t\t\t\t\tEnter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                viewTotalOrders();
                break;
            case 2:
                cout << "\t\t\t\t\tTotal Earnings: " << totalEarnings << " Rs.\n";
                break;
            case 3:
                changeCoffeePrices();
                break;
            case 4:
                cout << "\t\t\t\t\tLogging out...\n";
                break;
            default:
                cout << "\t\t\t\t\tInvalid choice. Try again.\n";
            }
        } while (choice != 4);
    }

    // Change coffee prices
    void changeCoffeePrices() {
        int choice;
        float newPrice;
        displayMenu();
        cout << "\t\t\t\t\tEnter the number of the coffee to change price: ";
        cin >> choice;
        if (choice >= 1 && choice <= (int)menu.size()) {
            cout << "\t\t\t\t\tEnter the new price for " << menu[choice - 1] << ": ";
            cin >> newPrice;
            price[choice - 1] = newPrice;

            cout << "\t\t\t\t\tPrice updated for " << menu[choice - 1] << " to " << newPrice << " Rs.\n";
        }
        else {
            cout << "\t\t\t\t\tInvalid choice. Try again.\n";
        }
    }

    // Find menu index
    int findMenuIndex(const string& coffeeName) {
        for (size_t i = 0; i < menu.size(); i++) {
            if (menu[i] == coffeeName) {
                return static_cast<int>(i);
            }
        }

        return -1;
    }
};

// Main function
int main() {

    CoffeeShop shop;
    shop.greeting();
    int choice;
    system("CLS");
    do {
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t           ---(Main Menu)---         \n";
        cout << "\t\t\t\t\t" << CYAN << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *" << RESET << WHITE << "    1. Add Order              " << RESET << CYAN << " * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *" << RESET << WHITE << "    2. Cancel Order           " << RESET << CYAN << " * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *" << RESET << WHITE << "    3. View Receipt           " << RESET << CYAN << " * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *" << RESET << WHITE << "    4. View Coffee Menu       " << RESET << CYAN << " * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *" << RESET << WHITE << "    5. Admin Panel            " << RESET << CYAN << " * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *" << RESET << WHITE << "    6. Exit                   " << RESET << CYAN << " * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* *                               * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;
        cout << "\t\t\t\t\t" << CYAN << "* * * * * * * * * * * * * * * * * * *" << RESET << endl;

        cout << "\n\t\t\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            shop.addOrder();
            break;
        case 2:
            shop.cancelOrder();
            break;
        case 3:
            shop.displayReceipt();
            break;
        case 4:
            shop.displayMenu();  // Show coffee menu
            break;
        case 5:
            shop.adminPanel();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "\t\t\t\t\tInvalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}