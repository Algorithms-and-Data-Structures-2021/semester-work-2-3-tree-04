#include "traversalAlgorithm.h"
#include "data_structure.hpp"
#include "iostream"

using namespace std;

namespace itis {



  void TwoThreeTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  void TwoThreeTree::clear(TwoThreeNode *node) {
    if (node != nullptr) {
      clear(node->first);
      clear(node->second);
      clear(node->third);
      delete [] node;
    }
  }

  void TwoThreeTree::Insert(int k){
    if (root_ != nullptr){
      insert(k, root_);
    } else {
      root_ = new TwoThreeNode(k);
    }
  }

  void TwoThreeTree::insert(int k, TwoThreeNode *node) {

    if (node->is_leaf()) {
      node->insert_to_node(k);
    } else if (k <= node->key[0]) {
      insert(k, node->first);
    } else if ((node->size == 1) || ((node->size == 2) && k <= node->key[1])) {
      insert(k, node->second);
    } else {
      insert(k, node->third);
    }
    root_ = split(node);
  }

  TwoThreeNode *TwoThreeTree::split(TwoThreeNode *item) {
    if (item->size < 3) return item;

    TwoThreeNode *x = new TwoThreeNode(item->key[0], item->first, item->second, nullptr, nullptr, item->parent);
    TwoThreeNode *y = new TwoThreeNode(item->key[2], item->third, item->fourth, nullptr, nullptr, item->parent);
    if (x->first)  x->first->parent = x;
    if (x->second) x->second->parent = x;
    if (y->first)  y->first->parent = y;
    if (y->second) y->second->parent = y;

    if (item->parent) {
      item->parent->insert_to_node(item->key[1]);

      if (item->parent->first == item) item->parent->first = nullptr;
      else if (item->parent->second == item) item->parent->second = nullptr;
      else if (item->parent->third == item) item->parent->third = nullptr;


      if (item->parent->first == nullptr) {
        item->parent->fourth = item->parent->third;
        item->parent->third = item->parent->second;
        item->parent->second = y;
        item->parent->first = x;
      } else if (item->parent->second == nullptr) {
        item->parent->fourth = item->parent->third;
        item->parent->third = y;
        item->parent->second = x;
      } else {
        item->parent->fourth = y;
        item->parent->third = x;
      }

      TwoThreeNode *tmp = item->parent;
      delete [] item;
      return tmp;
    } else {
      x->parent = item;
      y->parent = item;
      item->become_node2(item->key[1], x, y);
      return item;
    }
  }

  TwoThreeNode *TwoThreeTree::Search(int k) {
    return search(k, root_);
  }

  TwoThreeNode *TwoThreeTree::search(int k, TwoThreeNode *node) {
    if(node == nullptr) {
      return nullptr;
    }

    if(node->find(k)) {
      return node;
    }
    if(k < node->key[0]) {
      return search(k, node->first);
    }
    if( ((node->size == 2) && (k < node->key[1])) || (node->size == 1) ) {
      return search(k, node->second);
    }
    if(node->size == 2) {
      return search(k, node->third);
    }
    return nullptr;
  }

  void *TwoThreeTree::Remove(int k) {
    root_ = remove(k, root_);
  }

  TwoThreeNode *TwoThreeTree::remove(int k, TwoThreeNode *node){
    TwoThreeNode *item = search(k, node);

    if (!item) return node;

    TwoThreeNode *min = nullptr;
    if (item->key[0] == k) min = findMin(item->second);
    else min = findMin(item->third);

    if (min) {
      int &z = (k == item->key[0] ? item->key[0] : item->key[1]);
      item->swap(z, min->key[0]);
      item = min;
    }

    item->remove_from_node(k);
    return fix(item);
  }
  TwoThreeNode *TwoThreeTree::findMin(TwoThreeNode *node) {
    if (!node) {
      return node;
    }
    if (!(node->first)) {
      return node;
    }
    else {
      return findMin(node->first);
    }
  }

  TwoThreeNode *TwoThreeTree::fix(TwoThreeNode *leaf) {
    if (leaf->size == 0 && leaf->parent == nullptr) {
      delete leaf;
      return nullptr;
    }
    if (leaf->size != 0) {
      if (leaf->parent) return fix(leaf->parent);
      else return leaf;
    }

    TwoThreeNode *parent = leaf->parent;
    if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) leaf = redistribute(leaf);
    else if (parent->size == 2 && parent->third->size == 2) leaf = redistribute(leaf);
    else leaf = merge(leaf);
    return fix(leaf);
  }

  TwoThreeNode *TwoThreeTree::redistribute(TwoThreeNode *leaf) {
    TwoThreeNode *parent = leaf->parent;
    TwoThreeNode *first = parent->first;
    TwoThreeNode *second = parent->second;
    TwoThreeNode *third = parent->third;

    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
      if (first == leaf) {
        parent->first = parent->second;
        parent->second = parent->third;
        parent->third = nullptr;
        parent->first->insert_to_node(parent->key[0]);
        parent->first->third = parent->first->second;
        parent->first->second = parent->first->first;

        if (leaf->first != nullptr) parent->first->first = leaf->first;
        else if (leaf->second != nullptr) parent->first->first = leaf->second;

        if (parent->first->first != nullptr) parent->first->first->parent = parent->first;

        parent->remove_from_node(parent->key[0]);
        delete [] first;
      } else if (second == leaf) {
        first->insert_to_node(parent->key[0]);
        parent->remove_from_node(parent->key[0]);
        if (leaf->first != nullptr) first->third = leaf->first;
        else if (leaf->second != nullptr) first->third = leaf->second;

        if (first->third != nullptr) first->third->parent = first;

        parent->second = parent->third;
        parent->third = nullptr;

        delete [] second;
      } else if (third == leaf) {
        second->insert_to_node(parent->key[1]);
        parent->third = nullptr;
        parent->remove_from_node(parent->key[1]);
        if (leaf->first != nullptr) second->third = leaf->first;
        else if (leaf->second != nullptr) second->third = leaf->second;

        if (second->third != nullptr)  second->third->parent = second;

        delete [] third;
      }
    } else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
      if (third == leaf) {
        if (leaf->first != nullptr) {
          leaf->second = leaf->first;
          leaf->first = nullptr;
        }

        leaf->insert_to_node(parent->key[1]);
        if (second->size == 2) {
          parent->key[1] = second->key[1];
          second->remove_from_node(second->key[1]);
          leaf->first = second->third;
          second->third = nullptr;
          if (leaf->first != nullptr) leaf->first->parent = leaf;
        } else if (first->size == 2) {
          parent->key[1] = second->key[0];
          leaf->first = second->second;
          second->second = second->first;
          if (leaf->first != nullptr) leaf->first->parent = leaf;

          second->key[0] = parent->key[0];
          parent->key[0] = first->key[1];
          first->remove_from_node(first->key[1]);
          second->first = first->third;
          if (second->first != nullptr) second->first->parent = second;
          first->third = nullptr;
        }
      } else if (second == leaf) {
        if (third->size == 2) {
          if (leaf->first == nullptr) {
            leaf->first = leaf->second;
            leaf->second = nullptr;
          }
          second->insert_to_node(parent->key[1]);
          parent->key[1] = third->key[0];
          third->remove_from_node(third->key[0]);
          second->second = third->first;
          if (second->second != nullptr) second->second->parent = second;
          third->first = third->second;
          third->second = third->third;
          third->third = nullptr;
        } else if (first->size == 2) {
          if (leaf->second == nullptr) {
            leaf->second = leaf->first;
            leaf->first = nullptr;
          }
          second->insert_to_node(parent->key[0]);
          parent->key[0] = first->key[1];
          first->remove_from_node(first->key[1]);
          second->first = first->third;
          if (second->first != nullptr) second->first->parent = second;
          first->third = nullptr;
        }
      } else if (first == leaf) {
        if (leaf->first == nullptr) {
          leaf->first = leaf->second;
          leaf->second = nullptr;
        }
        first->insert_to_node(parent->key[0]);
        if (second->size == 2) {
          parent->key[0] = second->key[0];
          second->remove_from_node(second->key[0]);
          first->second = second->first;
          if (first->second != nullptr) first->second->parent = first;
          second->first = second->second;
          second->second = second->third;
          second->third = nullptr;
        } else if (third->size == 2) {
          parent->key[0] = second->key[0];
          second->key[0] = parent->key[1];
          parent->key[1] = third->key[0];
          third->remove_from_node(third->key[0]);
          first->second = second->first;
          if (first->second != nullptr) first->second->parent = first;
          second->first = second->second;
          second->second = third->first;
          if (second->second != nullptr) second->second->parent = second;
          third->first = third->second;
          third->second = third->third;
          third->third = nullptr;
        }
      }
    } else if (parent->size == 1) {
      leaf->insert_to_node(parent->key[0]);

      if (first == leaf && second->size == 2) {
        parent->key[0] = second->key[0];
        second->remove_from_node(second->key[0]);

        if (leaf->first == nullptr) leaf->first = leaf->second;

        leaf->second = second->first;
        second->first = second->second;
        second->second = second->third;
        second->third = nullptr;
        if (leaf->second != nullptr) leaf->second->parent = leaf;
      } else if (second == leaf && first->size == 2) {
        parent->key[0] = first->key[1];
        first->remove_from_node(first->key[1]);

        if (leaf->second == nullptr) leaf->second = leaf->first;

        leaf->first = first->third;
        first->third = nullptr;
        if (leaf->first != nullptr) leaf->first->parent = leaf;
      }
    }
    return parent;
  }

  TwoThreeNode *TwoThreeTree::merge(TwoThreeNode *leaf) {
    TwoThreeNode *parent = leaf->parent;

    if (parent->first == leaf) {
      parent->second->insert_to_node(parent->key[0]);
      parent->second->third = parent->second->second;
      parent->second->second = parent->second->first;

      if (leaf->first != nullptr) parent->second->first = leaf->first;
      else if (leaf->second != nullptr) parent->second->first = leaf->second;

      if (parent->second->first != nullptr) parent->second->first->parent = parent->second;

      parent->remove_from_node(parent->key[0]);
      delete parent->first;
      parent->first = nullptr;
    } else if (parent->second == leaf) {
      parent->first->insert_to_node(parent->key[0]);

      if (leaf->first != nullptr) parent->first->third = leaf->first;
      else if (leaf->second != nullptr) parent->first->third = leaf->second;

      if (parent->first->third != nullptr) parent->first->third->parent = parent->first;

      parent->remove_from_node(parent->key[0]);
      delete [] parent->second;
      parent->second = nullptr;
    }

    if (parent->parent == nullptr) {
      TwoThreeNode *tmp = nullptr;
      if (parent->first != nullptr) tmp = parent->first;
      else tmp = parent->second;
      tmp->parent = nullptr;
      delete [] parent;
      return tmp;
    }
    return parent;
  }

  TwoThreeNode *TwoThreeTree::root() {
    return root_;
  }

  int TwoThreeTree::Height() {
    return height(root_);
  }

  int TwoThreeTree::height(TwoThreeNode *node) {
    if (node == nullptr) {
      return 0;
    }

    const int first_height = height(node->first);

    return first_height + 1;
  }

  void TwoThreeTree::Traverse(const TraversalAlgorithm &algorithm) const {
    algorithm.Print(std::cout, root_);
  }
}