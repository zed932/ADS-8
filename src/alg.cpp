// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "bst.h"

void processCharacter(char ch, std::string& current_word, BST<std::string>& tree) {
  if (ch >= 'A' && ch <= 'Z') {
    ch = static_cast<char>(ch + ('a' - 'A'));
  }
  
  if (ch >= 'a' && ch <= 'z') {
    current_word += ch;
  } else if (!current_word.empty()) {
    tree.add(current_word);
    current_word.clear();
  }
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream input_file(filename);
  if (!input_file) {
    std::cerr << "Error opening input file!" << std::endl;
    return;
  }

  std::string current_word;
  char ch;
  while (input_file.get(ch)) {
    processCharacter(ch, current_word, tree);
  }

  if (!current_word.empty()) {
    tree.add(current_word);
  }

  input_file.close();
  std::cout << "Tree depth: " << tree.depth() << std::endl;
}

void printFreq(BST<std::string>& tree) {
  auto frequencies = tree.getFrequencies();
  
  std::sort(frequencies.begin(), frequencies.end(),
      [](const auto& a, const auto& b) {
        return a.second > b.second ||
              (a.second == b.second && a.first < b.first);
      });

  std::ofstream output_file("result/freq.txt");
  if (!output_file) {
    std::cerr << "Error creating output file!" << std::endl;
    return;
  }

  for (const auto& entry : frequencies) {
    std::cout << entry.first << ": " << entry.second << std::endl;
    output_file << entry.first << ": " << entry.second << std::endl;
  }

  output_file.close();
}
