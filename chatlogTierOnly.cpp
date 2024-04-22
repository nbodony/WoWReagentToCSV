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
    ifstream allOrder("allOrder.txt");
    vectorAllOrder = fillAllOrder(allOrder);
    toCSV(uniqueItems,uniqueItemAmounts,reagentAmount, vectorAllOrder);
    cout << "output.csv created" << endl;
}