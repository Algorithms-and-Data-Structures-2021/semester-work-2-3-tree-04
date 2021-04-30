#include "traversalAlgorithm.h"
#include "data_structure.hpp"
#include "iostream"

using namespace std;

namespace itis {

  void TwoThreeTree::Clear() {
    downstreamClear(root_);
    root_ = nullptr;
  }

  void TwoThreeTree::downstreamClear(TwoThreeNode *twoTreeNode) {
    if (twoTreeNode != nullptr) {
      downstreamClear(twoTreeNode->left);
      downstreamClear(twoTreeNode->middle);
      downstreamClear(twoTreeNode->right);
      delete [] twoTreeNode;
    }
  }

  void TwoThreeTree::Insert(int key){
    if (root_ != nullptr){
      insertIfRootExists(key, root_);
    } else {
      root_ = new TwoThreeNode(key);
    }
  }

  void TwoThreeTree::insertIfRootExists(int key, TwoThreeNode *twoTreeNode) {

    if (twoTreeNode->isLeaf()) {
      twoTreeNode->insertKey(key);
    } else if (key <= twoTreeNode->keys[0]) {
      insertIfRootExists(key, twoTreeNode->left);
    } else if ((twoTreeNode->size == 1) || ((twoTreeNode->size == 2) && key <= twoTreeNode->keys[1])) {
      insertIfRootExists(key, twoTreeNode->middle);
    } else {
      insertIfRootExists(key, twoTreeNode->right);
    }
    root_ = splitTwoTreeNode(twoTreeNode);
  }

  TwoThreeNode *TwoThreeTree::splitTwoTreeNode(TwoThreeNode *twoTreeNode) {
    if (twoTreeNode->size < 3) return twoTreeNode;

    TwoThreeNode *x = new TwoThreeNode(twoTreeNode->keys[0], twoTreeNode->left, twoTreeNode->middle, nullptr, nullptr,
                                       twoTreeNode->parent);
    TwoThreeNode *y = new TwoThreeNode(twoTreeNode->keys[2], twoTreeNode->right, twoTreeNode->additionalElement, nullptr, nullptr,
                                       twoTreeNode->parent);
    if (x->left)  x->left->parent = x;
    if (x->middle) x->middle->parent = x;
    if (y->left)  y->left->parent = y;
    if (y->middle) y->middle->parent = y;

    if (twoTreeNode->parent) {
      twoTreeNode->parent->insertKey(twoTreeNode->keys[1]);

      if (twoTreeNode->parent->left == twoTreeNode)
        twoTreeNode->parent->left = nullptr;
      else if (twoTreeNode->parent->middle == twoTreeNode)
        twoTreeNode->parent->middle = nullptr;
      else if (twoTreeNode->parent->right == twoTreeNode)
        twoTreeNode->parent->right = nullptr;


      if (twoTreeNode->parent->left == nullptr) {
        twoTreeNode->parent->additionalElement = twoTreeNode->parent->right;
        twoTreeNode->parent->right = twoTreeNode->parent->middle;
        twoTreeNode->parent->middle = y;
        twoTreeNode->parent->left = x;
      } else if (twoTreeNode->parent->middle == nullptr) {
        twoTreeNode->parent->additionalElement = twoTreeNode->parent->right;
        twoTreeNode->parent->right = y;
        twoTreeNode->parent->middle = x;
      } else {
        twoTreeNode->parent->additionalElement = y;
        twoTreeNode->parent->right = x;
      }

      TwoThreeNode *tmp = twoTreeNode->parent;
      delete [] twoTreeNode;
      return tmp;
    } else {
      x->parent = twoTreeNode;
      y->parent = twoTreeNode;
      twoTreeNode->becomeTwoKeyNode(twoTreeNode->keys[1], x, y);
      return twoTreeNode;
    }
  }

  TwoThreeNode *TwoThreeTree::Search(int key) {
    return downstreamSearch(key, root_);
  }

  TwoThreeNode *TwoThreeTree::downstreamSearch(int key, TwoThreeNode *twoTreeNode) {
    if(twoTreeNode == nullptr) {
      return nullptr;
    }

    if(twoTreeNode->isContains(key)) {
      return twoTreeNode;
    }
    if(key < twoTreeNode->keys[0]) {
      return downstreamSearch(key, twoTreeNode->left);
    }
    if( ((twoTreeNode->size == 2) && (key < twoTreeNode->keys[1])) || (twoTreeNode->size == 1) ) {
      return downstreamSearch(key, twoTreeNode->middle);
    }
    if(twoTreeNode->size == 2) {
      return downstreamSearch(key, twoTreeNode->right);
    }
    return nullptr;
  }

  void *TwoThreeTree::Remove(int key) {
    root_ = downstreamRemove(key, root_);
  }

  TwoThreeNode *TwoThreeTree::downstreamRemove(int key, TwoThreeNode *twoTreeNode){
    TwoThreeNode *element = downstreamSearch(key, twoTreeNode);

    if (!element) return twoTreeNode;

    TwoThreeNode *min = nullptr;
    if (element->keys[0] == key) min = downstreamSearchForMin(element->middle);
    else min = downstreamSearchForMin(element->right);

    if (min) {
      int &z = (key == element->keys[0] ? element->keys[0] : element->keys[1]);
      element->swapKeys(z, min->keys[0]);
      element = min;
    }

    element->removeByKey(key);
    return putRight(element);
  }

  TwoThreeNode *TwoThreeTree::downstreamSearchForMin(TwoThreeNode *twoTreeNode) {
    if (!twoTreeNode) {
      return twoTreeNode;
    }
    if (!(twoTreeNode->left)) {
      return twoTreeNode;
    }
    else {
      return downstreamSearchForMin(twoTreeNode->left);
    }
  }

  TwoThreeNode *TwoThreeTree::putRight(TwoThreeNode *leaf) {
    if (leaf->size == 0 && leaf->parent == nullptr) {
      delete leaf;
      return nullptr;
    }
    if (leaf->size != 0) {
      if (leaf->parent) return putRight(leaf->parent);
      else return leaf;
    }

    TwoThreeNode *parent = leaf->parent;
    if (parent->left->size == 2 || parent->middle->size == 2 || parent->size == 2) leaf = rotate(leaf);
    else if (parent->size == 2 && parent->right->size == 2) leaf = rotate(leaf);
    else leaf = mergeNode(leaf);
    return putRight(leaf);
  }

  TwoThreeNode *TwoThreeTree::rotate(TwoThreeNode *leaf) {
    TwoThreeNode *parent = leaf->parent;
    TwoThreeNode *first = parent->left;
    TwoThreeNode *second = parent->middle;
    TwoThreeNode *third = parent->right;

    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
      if (first == leaf) {
        parent->left = parent->middle;
        parent->middle = parent->right;
        parent->right = nullptr;
        parent->left->insertKey(parent->keys[0]);
        parent->left->right = parent->left->middle;
        parent->left->middle = parent->left->left;

        if (leaf->left != nullptr) parent->left->left = leaf->left;
        else if (leaf->middle != nullptr) parent->left->left = leaf->middle;

        if (parent->left->left != nullptr) parent->left->left->parent = parent->left;

        parent->removeByKey(parent->keys[0]);
        delete [] first;
      } else if (second == leaf) {
        first->insertKey(parent->keys[0]);
        parent->removeByKey(parent->keys[0]);
        if (leaf->left != nullptr) first->right = leaf->left;
        else if (leaf->middle != nullptr) first->right = leaf->middle;

        if (first->right != nullptr) first->right->parent = first;

        parent->middle = parent->right;
        parent->right = nullptr;

        delete [] second;
      } else if (third == leaf) {
        second->insertKey(parent->keys[1]);
        parent->right = nullptr;
        parent->removeByKey(parent->keys[1]);
        if (leaf->left != nullptr) second->right = leaf->left;
        else if (leaf->middle != nullptr) second->right = leaf->middle;

        if (second->right != nullptr)  second->right->parent = second;

        delete [] third;
      }
    } else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
      if (third == leaf) {
        if (leaf->left != nullptr) {
          leaf->middle = leaf->left;
          leaf->left = nullptr;
        }

        leaf->insertKey(parent->keys[1]);
        if (second->size == 2) {
          parent->keys[1] = second->keys[1];
          second->removeByKey(second->keys[1]);
          leaf->left = second->right;
          second->right = nullptr;
          if (leaf->left != nullptr) leaf->left->parent = leaf;
        } else if (first->size == 2) {
          parent->keys[1] = second->keys[0];
          leaf->left = second->middle;
          second->middle = second->left;
          if (leaf->left != nullptr) leaf->left->parent = leaf;

          second->keys[0] = parent->keys[0];
          parent->keys[0] = first->keys[1];
          first->removeByKey(first->keys[1]);
          second->left = first->right;
          if (second->left != nullptr) second->left->parent = second;
          first->right = nullptr;
        }
      } else if (second == leaf) {
        if (third->size == 2) {
          if (leaf->left == nullptr) {
            leaf->left = leaf->middle;
            leaf->middle = nullptr;
          }
          second->insertKey(parent->keys[1]);
          parent->keys[1] = third->keys[0];
          third->removeByKey(third->keys[0]);
          second->middle = third->left;
          if (second->middle != nullptr) second->middle->parent = second;
          third->left = third->middle;
          third->middle = third->right;
          third->right = nullptr;
        } else if (first->size == 2) {
          if (leaf->middle == nullptr) {
            leaf->middle = leaf->left;
            leaf->left = nullptr;
          }
          second->insertKey(parent->keys[0]);
          parent->keys[0] = first->keys[1];
          first->removeByKey(first->keys[1]);
          second->left = first->right;
          if (second->left != nullptr) second->left->parent = second;
          first->right = nullptr;
        }
      } else if (first == leaf) {
        if (leaf->left == nullptr) {
          leaf->left = leaf->middle;
          leaf->middle = nullptr;
        }
        first->insertKey(parent->keys[0]);
        if (second->size == 2) {
          parent->keys[0] = second->keys[0];
          second->removeByKey(second->keys[0]);
          first->middle = second->left;
          if (first->middle != nullptr) first->middle->parent = first;
          second->left = second->middle;
          second->middle = second->right;
          second->right = nullptr;
        } else if (third->size == 2) {
          parent->keys[0] = second->keys[0];
          second->keys[0] = parent->keys[1];
          parent->keys[1] = third->keys[0];
          third->removeByKey(third->keys[0]);
          first->middle = second->left;
          if (first->middle != nullptr) first->middle->parent = first;
          second->left = second->middle;
          second->middle = third->left;
          if (second->middle != nullptr) second->middle->parent = second;
          third->left = third->middle;
          third->middle = third->right;
          third->right = nullptr;
        }
      }
    } else if (parent->size == 1) {
      leaf->insertKey(parent->keys[0]);

      if (first == leaf && second->size == 2) {
        parent->keys[0] = second->keys[0];
        second->removeByKey(second->keys[0]);

        if (leaf->left == nullptr) leaf->left = leaf->middle;

        leaf->middle = second->left;
        second->left = second->middle;
        second->middle = second->right;
        second->right = nullptr;
        if (leaf->middle != nullptr) leaf->middle->parent = leaf;
      } else if (second == leaf && first->size == 2) {
        parent->keys[0] = first->keys[1];
        first->removeByKey(first->keys[1]);

        if (leaf->middle == nullptr) leaf->middle = leaf->left;

        leaf->left = first->right;
        first->right = nullptr;
        if (leaf->left != nullptr) leaf->left->parent = leaf;
      }
    }
    return parent;
  }

  TwoThreeNode *TwoThreeTree::mergeNode(TwoThreeNode *leaf) {
    TwoThreeNode *parent = leaf->parent;

    if (parent->left == leaf) {
      parent->middle->insertKey(parent->keys[0]);
      parent->middle->right = parent->middle->middle;
      parent->middle->middle = parent->middle->left;

      if (leaf->left != nullptr) parent->middle->left = leaf->left;
      else if (leaf->middle != nullptr) parent->middle->left = leaf->middle;

      if (parent->middle->left != nullptr) parent->middle->left->parent = parent->middle;

      parent->removeByKey(parent->keys[0]);
      delete parent->left;
      parent->left = nullptr;
    } else if (parent->middle == leaf) {
      parent->left->insertKey(parent->keys[0]);

      if (leaf->left != nullptr) parent->left->right = leaf->left;
      else if (leaf->middle != nullptr) parent->left->right = leaf->middle;

      if (parent->left->right != nullptr) parent->left->right->parent = parent->left;

      parent->removeByKey(parent->keys[0]);
      delete [] parent->middle;
      parent->middle = nullptr;
    }

    if (parent->parent == nullptr) {
      TwoThreeNode *tmp = nullptr;
      if (parent->left != nullptr) tmp = parent->left;
      else tmp = parent->middle;
      tmp->parent = nullptr;
      delete [] parent;
      return tmp;
    }
    return parent;
  }

  TwoThreeNode *TwoThreeTree::getRoot() {
    return root_;
  }

  int TwoThreeTree::getHeight() {
    return calculateHeight(root_);
  }

  int TwoThreeTree::calculateHeight(TwoThreeNode *twoTreeNode) {
    if (twoTreeNode == nullptr) {
      return 0;
    }

    const int height = calculateHeight(twoTreeNode->left);

    return height + 1;
  }

  void TwoThreeTree::Traverse(const TraversalAlgorithm &algorithm) const {
    algorithm.Print(std::cout, root_);
  }
}