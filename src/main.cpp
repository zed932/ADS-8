// Copyright 2021 NNTU-CS
#include <string>
#include "bst.h"

int main() {
  BST<std::string> word_tree;
  makeTree(word_tree, "src/war_peace.txt");
  printFreq(word_tree);
  return 0;
}
