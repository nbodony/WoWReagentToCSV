#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

#include "openFileTierOnly.h"

vector<string> itemsProduced(string filename, int reagentAmount) {
    ifstream chatlog(filename);

    if (!chatlog.is_open()){
        cout << "Can't open file!" << endl;
    }
    string content;
    string itemName;
    string qualityName;
    vector<string> contents;
    vector<string> itemNames;
    vector<int> itemCount;


    while (getline(chatlog,content)) {
        chatlog.ignore(256, ':');
        chatlog.ignore(256, ':');
        chatlog.ignore(256, ':');
        chatlog.ignore(256, ' ');
        if ((content.find("Professions") != std::string::npos)) {
            contents.push_back(content); // <-- Stores all lines of Chat Log involving profession items in a vector
        }
    }

    for (size_t i = 0; i < contents.size(); ++i) {
        int endName = 0;
        string itemName;
        string itemNamePre = contents[i];
        endName = itemNamePre.find('|'); //<-- Finds end of Item Name in an entry in the vector of Chat Log lines
        for (int i = 0; i < (endName - 1);++i) {
            itemName += itemNamePre[i]; 
        }
        if((contents[i].find("Tier") != std::string::npos)) {
            int qualityLoc = 0;
            qualityLoc = contents[i].find_last_of('-') + 1;
            qualityName = contents[i].substr(qualityLoc,5);
        }
        
        itemNames.push_back(itemName + " (" + qualityName + ")"); //<-- Saves each item name in a vector parallel to Professions Chat Log Vector
    }
    return itemNames;
}

vector<int> amountProduced(string filename, int reagentAmount) {
    ifstream chatlog(filename);

    if (!chatlog.is_open()){
        cout << "Can't open file!" << endl;
    }
    string content;
    string itemName;
    vector<string> contents;
    vector<string> itemNames;
    vector<int> itemCount;


    while (getline(chatlog,content)) {
        chatlog.ignore(256, ':');
        chatlog.ignore(256, ':');
        chatlog.ignore(256, ':');
        chatlog.ignore(256, ' ');
        if ((content.find("Professions") != std::string::npos)) {
            contents.push_back(content); // <-- Stores all lines of Chat Log involving profession items in a vector
        }
    }
    for(size_t i = 0; i < contents.size(); ++ i) {
        

        // Fix instances with crumbled stone and fractured glass and prismatic ore

        int startNum = 0;
        int amount = 0;
        startNum = contents[i].find_last_of('|') + 1;
        string itemAmounts = contents[i];
        int endNum = itemAmounts.size() - 2;
        if (startNum == endNum) { //<-- Only one item (amount section of log == "a")
            amount = 1;
        } 
        if (contents[i].find("Tier") != std::string::npos) { // <-- Multiple items (amount section of log == "ax<number>")
            cout << "Other Material Found: " << endl;
            cout << contents[i] << endl;
            string amountString = (itemAmounts.substr((startNum+2), (endNum - startNum)));
            
            cout << amountString << endl;
            if (amountString == "") {
                amount = 1;
                cout << amount << endl;
            } else {
            amount = stoi(amountString);
            cout << amount << endl;
            }
        }
        itemCount.push_back(amount);
        amount = 0;
    }

    return itemCount;
}

void toCSV(const vector<string> &names, const vector<int> &amounts, int reagentAmount, const vector<string> &vectorAllOrder) {
    ofstream fout("output.csv");
    vector<string> namePlace(vectorAllOrder.size());
    vector<int> amountPlace(vectorAllOrder.size(),0); // <-- Creat empty vectors of the size of the maximum amount of strings to hold values if the appear

    for(size_t i = 0; i < names.size(); ++i) {
        for(size_t k = 0; k < vectorAllOrder.size(); ++k) {
            if(vectorAllOrder[k] == names[i]) { // <-- For each name in the names vector, wherever it appears in the vectorAllOrder vector is
                namePlace[k] = names[i];        // now where it is placed in the empty vectors
                amountPlace[k] = amounts[i];
            }
        }
    }
    for(size_t h = 0; h < namePlace.size(); ++h) { // <-- For each value in namePlace (whether the name exists or not), print out the item name and amount
        fout << vectorAllOrder[h] << ',' << amountPlace[h] << "\n";
    }

    int reagentreturn = 0;
    for(size_t k = 0; k < names.size(); ++k) { // <-- Handle prismatic ore
        if(names[k] == "Prismatic Ore") {
            reagentreturn = amounts[k]; 
        }
    }

    fout << "Prismatic Ore/Reagent" << ',' << "Reagent return: " << (reagentreturn / reagentAmount) << ',' << reagentreturn << "\n";
}

vector<string> fillAllOrder(ifstream& allnames) { // <-- Fill vector of all possible names in order from a file
    string name;
    vector<string> vectorAllOrder;
    while(getline(allnames,name)) {
        vectorAllOrder.push_back(name);
    }
    return vectorAllOrder;
}


vector<int> sumItemAmounts(const vector<string> &names, const vector<int> &amounts) {
    vector<int> uniqueItemAmounts;
    int sum = 0;
    vector<string> uniqueNames = uniqueStrings(names);
    for(size_t h = 0; h < uniqueNames.size(); ++h) {
    }
    for(size_t i = 0; i < uniqueNames.size(); ++i) {           // <-- For all unique names, whenever that name appears in the complete names list, sum the corresponding amount
        for(size_t k = 0; k < names.size(); ++k) {   // from the parallel amounts vector 
            if (uniqueNames[i] == names[k]) {
                sum += amounts[k];
            }
        }
        uniqueItemAmounts.push_back(sum); // <-- After checking for all instances of a word in the names vector, add the sum of all instances of amounts for that name to a
        sum = 0;                          // parallel vector of amounts for each unique item. Now there is a vector of unique names as well as a parallel vector of unique 
    }                                     // item amounts
    return uniqueItemAmounts;
}


vector<string> uniqueStrings(const vector<string> &names) {
    vector<string> uniqueNames;
    int sum = 0;
    uniqueNames.push_back(names[0]); // <-- initialize vector of unique names with just one name to allow for at least one iteration
    for(size_t i = 1; i < names.size(); ++i) {
        for(size_t k = 0; k < uniqueNames.size();++k) { // <-- For each item in names, if that item appears in uniqueNames increase the occurrence counter
            if ((names[i] == uniqueNames[k])) {
                sum++;
            }
        }
        if(sum == 0) { // <-- If the occurrence counter is 0 this means there are no repetitions of the name so add the name to uniqueNames
            uniqueNames.push_back(names[i]);
        } else {
            sum = 0;
        }
    }
    return uniqueNames;
}