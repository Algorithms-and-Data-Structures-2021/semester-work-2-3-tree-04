//
// Created by niazh on 23.04.2021.
//

#include <TwoThreeNode.h>
#include "node.h"

namespace itis {

  TwoThreeNode::TwoThreeNode(int k, TwoThreeNode *first_, TwoThreeNode *second_, TwoThreeNode *third_, TwoThreeNode *fourth_, TwoThreeNode *parent_):
      size(1), key{k, 0}, first(first_), second(second_),
      third(third_), fourth(fourth_), parent(parent_) {}

  bool TwoThreeNode::find(int k) {
    for (int i = 0; i < size; ++i) {
      if (key[i] == k) {
        return true;
      }
    }
    return false;
  }

  void TwoThreeNode::swap(int &x, int &y) {
    int r = x;
    x = y;
    y = r;
  }

  void TwoThreeNode::sort2(int &x, int &y) {
    if(x > y) {
      swap(x, y);
    }
  }

  void TwoThreeNode::sort3(int &x, int &y, int &z) {
    if(x > y) {
      swap(x, y);
    }
    if(x > z) {
      swap(x, z);
    }
    if(y > z) {
      swap(y, z);
    }
  }

  void TwoThreeNode::sort() {
    if(size == 1) {
      return;
    }
    if(size == 2) {
      sort2(key[0], key[1]);
    }
    if(size == 3) {
      sort3(key[0], key[1], key[2]);
    }
  }

  void TwoThreeNode::insert_to_node(int k) {
    key[size] = k;
    size++;
    sort();
  }

  void TwoThreeNode::remove_from_node(int k) {
    if (size >= 1 && key[0] == k) {
      key[0] = key[1];
      key[1] = 0;
      size--;
    } else if (size == 2 && key[1] == k) {
      key[1] = 0;
      size--;
    }
  }

  void TwoThreeNode::become_node2(int k, TwoThreeNode *first_, TwoThreeNode *second_) {
    key[0] = k;
    key[1] = 0;
    first = first_;
    second = second_;
    third = nullptr;
    parent = nullptr;
    size = 1;
  }

  bool TwoThreeNode::is_leaf() {
    return (first == nullptr) && (second == nullptr) && (third == nullptr);
  }
};