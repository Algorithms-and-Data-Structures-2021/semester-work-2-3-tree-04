//
// Created by Тимур on 24.04.2021.
//

#include "traversalAlgorithm.h"

#include <queue>

namespace itis {
  void BreadthFirstTraversalAlgorithm::Print(std::ostream &os, TwoThreeNode *node) const {
    std::queue<TwoThreeNode*> nodesQueue;
    nodesQueue.push(node);

    while (!nodesQueue.empty()) {
      const auto *currentNode = nodesQueue.front();
      nodesQueue.pop();

      os << currentNode ->keys[0] << currentNode ->keys[1] << "\t";

      if (currentNode ->left != nullptr) {
        nodesQueue.push(currentNode ->left);
      }

      if (currentNode ->middle != nullptr) {
        nodesQueue.push(currentNode ->middle);
      }

      if (currentNode ->right != nullptr) {
        nodesQueue.push(currentNode ->right);
      }
    }
  }
}