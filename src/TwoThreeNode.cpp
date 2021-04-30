//
// Created by niazh on 23.04.2021.
//

#include <TwoThreeNode.h>

namespace itis {

  TwoThreeNode::TwoThreeNode(int key, TwoThreeNode *first_, TwoThreeNode *second_, TwoThreeNode *third_, TwoThreeNode *fourth_, TwoThreeNode *additionalElement_):
      size(1), keys{key, 0}, left(first_), middle(second_), right(third_), additionalElement(fourth_), parent(additionalElement_) {}

  bool TwoThreeNode::isContains(int key) {
    for (int i = 0; i < size; ++i) {
      if (keys[i] == key) {
        return true;
      }
    }
    return false;
  }

  void TwoThreeNode::swapKeys(int &a, int &b) {
    int r = a;
    a = b;
    b = r;
  }

  void TwoThreeNode::sortTwoElements(int &a, int &b) {
    if(a > b) {
      swapKeys(a, b);
    }
  }

  void TwoThreeNode::sortThreeElements(int &a, int &b, int &c) {
    if(a > b) {
      swapKeys(a, b);
    }
    if(a > c) {
      swapKeys(a, c);
    }
    if(b > c) {
      swapKeys(b, c);
    }
  }

  void TwoThreeNode::sortKeys() {
    if(size == 1) {
      return;
    }
    if(size == 2) {
      sortTwoElements(keys[0], keys[1]);
    }
    if(size == 3) {
      sortThreeElements(keys[0], keys[1], keys[2]);
    }
  }

  void TwoThreeNode::insertKey(int newKey) {
    keys[size] = newKey;
    size++;
    sortKeys();
  }

  void TwoThreeNode::removeByKey(int key) {
    if (size >= 1 && keys[0] == key) {
      keys[0] = keys[1];
      keys[1] = 0;
      size--;
    } else if (size == 2 && keys[1] == key) {
      keys[1] = 0;
      size--;
    }
  }

  void TwoThreeNode::becomeTwoKeyNode(int key, TwoThreeNode *first_, TwoThreeNode *second_) {
    keys[0] = key;
    keys[1] = 0;
    left = first_;
    middle = second_;
    right = nullptr;
    parent = nullptr;
    size = 1;
  }

  bool TwoThreeNode::isLeaf() {
    return (left == nullptr) && (middle == nullptr) && (right == nullptr);
  }
};