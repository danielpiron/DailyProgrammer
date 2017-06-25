#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream f{"../../data/challenge-input1.txt"};
  std::string line;

  std::vector<std::vector<int>> hands;
  while (std::getline(f, line)) {
    std::istringstream line_stream(line);

    std::string num;
    std::vector<int> hand;
    while (getline(line_stream, num, ' ')) {
      hand.push_back(std::stoi(num));
    }
    hands.push_back(hand);
  }
  return 0;
}
