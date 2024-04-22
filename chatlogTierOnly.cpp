#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iterator>


#include "openFileTierOnly.h"

using namespace std;





int main () {
    string filename;
    int reagentAmount = 0;
    cout << "What is the file called? " << endl;
    cin >> filename;
    cout << "Reagent amount?" << endl;
    cin >> reagentAmount;
    vector<string> vectorAllOrder;
    vector<string> items = itemsProduced(filename,reagentAmount);
    vector<int> amounts = amountProduced(filename,reagentAmount);
    vector<string> uniqueItems = uniqueStrings(items);
    vector<int> uniqueItemAmounts = sumItemAmounts(items, amounts);
    cout << "All items: " << endl;
    for(size_t i = 0; i < items.size(); ++i) {
        cout << items[i] << " " << amounts[i] << endl;
    }
    cout << "Unique Items: " << endl;
    for(size_t k = 0; k < uniqueItems.size();++k) {
        cout << uniqueItems[k] << " " << uniqueItemAmounts[k] << endl;
    }
    ifstream allOrder("allOrder.txt");
    vectorAllOrder = fillAllOrder(allOrder);
    toCSV(uniqueItems,uniqueItemAmounts,reagentAmount, vectorAllOrder);
}