#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iterator>

std::string fileOpen(std::string filename, int reagentAmount);
std::vector<std::string> itemsProduced(std::string filename, int reagentAmount);
std::vector<int> amountProduced(std::string filename, int reagentAmount);
void toCSV(const std::vector<std::string> &names, const std::vector<int> &amounts, int reagentAmount, const std::vector<std::string> &vectorAllOrder);
std::vector<std::string> fillAllOrder(std::ifstream& allnames);
std::vector<int> sumItemAmounts(const std::vector<std::string> &names, const std::vector<int> &amounts);
std::vector<std::string> uniqueStrings(const std::vector<std::string> &names);