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

  void collectFrequencies(Node* node,
                          std::vector<std::pair<T, int>>& freqs) const {
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
    if (value.empty()) return;
    root = addNode(root, value);
  }

  int search(T value) const {
    Node* current = root;
    while (current) {
      if (value == current->key) {
        return current->count;
      } else if (value < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return 0;
  }

  int computeDepth(Node* curr) const {
    if (curr == nullptr) return -1;
    int left_depth = computeDepth(curr->left);
    int right_depth = computeDepth(curr->right);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
  }

  int depth() const {
    return computeDepth(root);
  }

  std::vector<std::pair<T, int>> getFrequencies() const {
    std::vector<std::pair<T, int>> frequencies;
    collectFrequencies(root, frequencies);
    return frequencies;
  }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

#endif  // INCLUDE_BST_H_
