#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

struct Item {
    string name;
    string category;
    float price;
    int quantity;
    int priority; // 1 = High, 2 = Medium, 3 = Low
};

vector<Item> cart;
unordered_map<string, int> itemIndex; // name → index in cart

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void loadCartFromFile(const string& filename = "cart.txt");
void saveCartToFile(const string& filename = "cart.txt");

void addItem() {
    Item item;
    cout << "\nEnter item name: ";
    cin >> item.name;
    cout << "Enter category: ";
    cin >> item.category;

    cout << "Enter price: ";
    while (!(cin >> item.price) || item.price < 0) {
        cout << "Invalid price. Try again: ";
        clearInputBuffer();
    }

    cout << "Enter quantity: ";
    while (!(cin >> item.quantity) || item.quantity <= 0) {
        cout << "Invalid quantity. Try again: ";
        clearInputBuffer();
    }

    cout << "Enter priority (1-High, 2-Med, 3-Low): ";
    while (!(cin >> item.priority) || item.priority < 1 || item.priority > 3) {
        cout << "Invalid priority. Try again: ";
        clearInputBuffer();
    }

    if (itemIndex.count(item.name)) {
        cout << "Item already exists. Updating quantity.\n";
        cart[itemIndex[item.name]].quantity += item.quantity;
    } else {
        itemIndex[item.name] = cart.size();
        cart.push_back(item);
    }
}

void deleteItem() {
    string name;
    cout << "\nEnter item name to delete: ";
    cin >> name;

    if (!itemIndex.count(name)) {
        cout << "Item not found!\n";
        return;
    }

    int idx = itemIndex[name];
    cart.erase(cart.begin() + idx);
    
    // Rebuild index
    itemIndex.clear();
    for (int i = 0; i < cart.size(); ++i) {
        itemIndex[cart[i].name] = i;
    }

    cout << "Item deleted.\n";
}

void viewCart() {
    if (cart.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    cout << "\n--- Cart Contents ---\n";
    cout << left << setw(15) << "Name" << setw(12) << "Category"
         << setw(8) << "Price" << setw(10) << "Qty" << setw(10) << "Priority\n";

    for (const auto& item : cart) {
        cout << left << setw(15) << item.name << setw(12) << item.category
             << setw(8) << item.price << setw(10) << item.quantity
             << setw(10) << item.priority << '\n';
    }
}

void sortByPrice() {
    sort(cart.begin(), cart.end(), [](const Item& a, const Item& b) {
        return a.price < b.price;
    });
    cout << "Cart sorted by price.\n";
}

void sortByPriority() {
    sort(cart.begin(), cart.end(), [](const Item& a, const Item& b) {
        return a.priority < b.priority;
    });
    cout << "Cart sorted by priority.\n";
}

void optimizeWithinBudget() {
    float budget;
    cout << "\nEnter your budget: Rs ";
    while (!(cin >> budget) || budget < 0) {
        cout << "Invalid amount. Try again: Rs ";
        clearInputBuffer();
    }

    // Copy and sort by total cost ascending (Greedy)
    vector<Item> temp = cart;
    sort(temp.begin(), temp.end(), [](const Item& a, const Item& b) {
        return (a.price * a.quantity) < (b.price * b.quantity);
    });

    float total = 0;
    cout << "\n--- Optimal Purchase Plan ---\n";
    cout << left << setw(15) << "Name" << setw(10) << "Qty" << setw(12) << "Total Cost\n";

    for (const auto& item : temp) {
        float itemCost = item.price * item.quantity;
        if (total + itemCost <= budget) {
            total += itemCost;
            cout << left << setw(15) << item.name << setw(10) << item.quantity
                 << "Rs " << fixed << setprecision(2) << itemCost << '\n';
        }
    }
    cout << "Total spent: Rs " << fixed << setprecision(2) << total
         << " | Remaining: Rs " << budget - total << '\n';
}

void showTopExpensive() {
    if (cart.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    vector<Item> temp = cart;
    sort(temp.begin(), temp.end(), [](const Item& a, const Item& b) {
        return a.price > b.price;
    });

    cout << "\n--- Top 3 Expensive Items ---\n";
    for (int i = 0; i < min(3, (int)temp.size()); ++i) {
        cout << temp[i].name << " - Rs" << fixed << setprecision(2) << temp[i].price << '\n';
    }
}
void loadCartFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "No saved cart found. Starting fresh.\n";
        return;
    }

    Item item;
    while (fin >> item.name >> item.category >> item.price >> item.quantity >> item.priority) {
        cart.push_back(item);
        itemIndex[item.name] = cart.size() - 1;
    }
    fin.close();
    cout << "Cart loaded from file.\n";
}

void saveCartToFile(const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Failed to save cart!\n";
        return;
    }

    for (const auto& item : cart) {
        fout << item.name << ' ' << item.category << ' ' << item.price
             << ' ' << item.quantity << ' ' << item.priority << '\n';
    }
    fout.close();
    cout << "Cart saved to file.\n";
}

void showMenu() {
    cout << "\n========== Grocery Cart Optimizer ==========\n";
    cout << "1. Add Item\n";
    cout << "2. Delete Item\n";
    cout << "3. View Cart\n";
    cout << "4. Sort by Price\n";
    cout << "5. Sort by Priority\n";
    cout << "6. Optimize within Budget\n";
    cout << "7. Show Top 3 Expensive Items\n";
    cout << "8. Save Cart to File\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    loadCartFromFile(); // Load cart on startup
    int choice;
    do {
        showMenu();
        while (!(cin >> choice)) {
            cout << "Invalid input. Try again: ";
            clearInputBuffer();
        }

        switch (choice) {
            case 1: addItem(); break;
            case 2: deleteItem(); break;
            case 3: viewCart(); break;
            case 4: sortByPrice(); break;
            case 5: sortByPriority(); break;
            case 6: optimizeWithinBudget(); break;
            case 7: showTopExpensive(); break;
            case 8: saveCartToFile(); break;
            case 0: cout << "Exiting... Goodbye!\n"; break;
            default: cout << "Invalid option! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

