// Copyright 2021 NNTU-CS
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include "bst.h"

void processCharacter(char ch, std::string& current_word,
                      BST<std::string>& tree) {
  ch = tolower(ch);
  if (isalpha(static_cast<unsigned char>(ch))) {
    current_word += ch;
  } else if (!current_word.empty()) {
    tree.add(current_word);
    current_word.clear();
  }
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream input_file(filename, std::ios::binary);
  if (!input_file) {
    std::cerr << "File error!" << std::endl;
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
}

void printFreq(BST<std::string>& tree) {
  auto frequencies = tree.getFrequencies();

  std::sort(frequencies.begin(), frequencies.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second ||
                     (a.second == b.second && a.first < b.first);
            });

  mkdir("result", 0755);
  std::ofstream output_file("result/freq.txt");
  if (!output_file) {
    std::cerr << "Error creating output file!" << std::endl;
    return;
  }

  for (const auto& entry : frequencies) {
    output_file << entry.first << ": " << entry.second << "\n";
  }

  output_file.close();
}
