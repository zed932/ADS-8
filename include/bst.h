// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* addNode(Node* node, T value) {
    if (!node) return new Node(value);
    if (value == node->key) {
      node->count++;
    } else if (value < node->key) {
      node->left = addNode(node->left, value);
    } else {
      node->right = addNode(node->right, value);
    }
    return node;
  }

  int calculateDepth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(calculateDepth(node->left),
                        calculateDepth(node->right));
  }

  void collectFrequencies(Node* node, std::vector<std::pair<T, int>>& freqs) const {
    if (!node) return;
    collectFrequencies(node->left, freqs);
    freqs.emplace_back(node->key, node->count);
    collectFrequencies(node->right, freqs);
  }

  void clearTree(Node* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clearTree(root); }

  void add(T value) {
    root = addNode(root, value);
  }

  int depth() const {
    return calculateDepth(root);
  }

  std::vector<std::pair<T, int>> getFrequencies() const {
    std::vector<std::pair<T, int>> frequencies;
    collectFrequencies(root, frequencies);
    return frequencies;
  }
};

#endif  // INCLUDE_BST_H_
