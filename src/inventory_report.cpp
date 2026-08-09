#include "inventory_report.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

bool isValidQuantity(int quantity) {
    return quantity >=0;
}

bool isValidPrice(double price) {
    return price >=0.0;
}

double calculateItemValue(const InventoryItem& item) {
    if (!isValidQuantity(item.quantity) || !isValidPrice(item.price)) {
        return 0.0;
    }
    
    return item.quantity * item.price;
}

int readInventoryFile(string filename, InventoryItem items[], int maxItems) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
}

int count = 0;

while (count < maxItems &&
        inputFile >> items[count].sku
                  >> items[count].name
                  >> items[count].quantity
                  >> items[count].price) {

    if (isValidQuantity(items[count].quantity) &&
            isValidPrice(items[count].price)) {
            count++;
        }
    }

    inputFile.close();
    return count;
}  

bool writeInventoryReport(string filename, const InventoryItem items[], int count) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        return false;
    }

    outputFile << fixed << setprecision(2);

    outputFile << "Inventory Report" << endl;

    for (int i = 0; i < count; i++) {
        outputFile << items[i].sku << " "
                   << items[i].name << " "
                   << items[i].quantity << " "
                   << items[i].price << " "
                   << calculateItemValue(items[i]) << endl;
    }

    outputFile << "Total Inventory Value: "
               << calculateTotalInventoryValue(items, count)
               << endl;

    outputFile.close();

    return true;
}

double calculateTotalInventoryValue(const InventoryItem items[], int count) {
    if (items == nullptr || count <= 0) {
        return 0.0;
    }

    double total = 0.0;

    for (int i = 0; i < count; i++) {
        total += calculateItemValue(items[i]);
    }

    return total;
}

int findItemBySku(const InventoryItem items[], int count, string sku) {
     if (items == nullptr || count <= 0) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (items[i].sku == sku) {
            return i;
        }
    }

    return -1;
}

int findHighestValueItemIndex(const InventoryItem items[], int count) {
    if (items == nullptr || count <= 0) {
        return -1;
    }

    int highestIndex = 0;

    for (int i = 1; i < count; i++) {
        if (calculateItemValue(items[i]) >
            calculateItemValue(items[highestIndex])) {
            highestIndex = i;
        }
    }

    return highestIndex;
}
