#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

std::queue<int> parse_hand(const std::string &s) {
  std::istringstream line_stream(s);
  std::string num;
  std::queue<int> hand;
  while (getline(line_stream, num, ' ')) {
    hand.push(std::stoi(num));
  }
  return hand;
}

int main() {
  std::ifstream f{"../../data/challenge-input1.txt"};
  std::string line;

  std::vector<std::queue<int>> hands;
  while (std::getline(f, line)) {
    hands.push_back(parse_hand(line));
  }

  std::stack<int> table;
  int card = hands[0].front();
  hands[0].pop();
  table.push(card);
  return 0;
}
