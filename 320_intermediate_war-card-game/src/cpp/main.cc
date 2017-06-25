#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parse_hand(const std::string &s) {
  std::istringstream line_stream(s);
  std::string num;
  std::vector<int> hand;
  while (getline(line_stream, num, ' ')) {
    hand.push_back(std::stoi(num));
  }
  return hand;
}

int main() {
  std::ifstream f{"../../data/challenge-input1.txt"};
  std::string line;

  std::vector<std::vector<int>> hands;
  while (std::getline(f, line)) {
    hands.push_back(parse_hand(line));
  }
  return 0;
}
