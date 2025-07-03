# 🛒 Grocery Cart Optimizer (C++) – Internship Project

A **console-based C++ application** that allows users to manage a grocery shopping cart efficiently.  
Built using **core data structures (DSA)** like `vector`, `unordered_map`, `sort`, and **greedy optimization**, it simulates real-life cart planning with budget constraints.

---

## 🚀 Why This Project?

This project was built as a **college-level internship project** to demonstrate:
- Practical C++ coding skills
- Use of core data structures and algorithms
- File I/O for data persistence
- Clean, modular, and user-friendly CLI interface

It solves a real-world problem: _"How can I plan grocery purchases within a limited budget while managing preferences and priorities?"_

---

## ✨ Features

| Feature | Description |
|--------|-------------|
| ➕ Add Item | Add new groceries with price, quantity, category, and priority |
| ❌ Delete Item | Remove items by name |
| 📃 View Cart | See current items in a table format |
| 💸 Sort by Price | Reorder items from cheapest to most expensive |
| 🚨 Sort by Priority | Group items by priority (1=High, 2=Med, 3=Low) |
| 🎯 Optimize Budget | Greedy selection of best-value items under budget |
| 💡 Top 3 Expensive | View the three costliest items |
| 💾 Save to File | Save cart to `cart.txt` manually |
| 📥 Auto Load | Automatically loads saved cart on program start |

---

## 🧠 Concepts & DSA Used

| Concept | Where Used |
|--------|-------------|
| `vector<Item>` | Storing cart dynamically |
| `unordered_map<string, int>` | Quick lookup by item name |
| `sort()` with comparator | Sorting by price or priority |
| Greedy Algorithm | Select max items within budget |
| File I/O (`fstream`) | Saving/loading cart data |

---

## 🧮 How Budget Optimization Works

When you choose "Optimize within Budget", the program:

1. Sorts items by **total cost** (price × quantity) – ascending  
2. Greedily adds items to cart **as long as budget allows**  
3. Skips remaining if not affordable  
4. Displays **total spent** and **remaining budget**

This is a simplified version of the **0/1 Knapsack problem**, implemented using a **greedy strategy** for speed.

---

## 📁 Project Structure

