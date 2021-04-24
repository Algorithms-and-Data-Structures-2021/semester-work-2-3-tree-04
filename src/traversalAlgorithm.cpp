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

      os << currentNode -> key[0] << currentNode -> key[1] << "\t";

      if (currentNode -> first != nullptr) {
        nodesQueue.push(currentNode -> first);
      }

      if (currentNode -> second != nullptr) {
        nodesQueue.push(currentNode -> second);
      }

      if (currentNode -> third != nullptr) {
        nodesQueue.push(currentNode -> third);
      }
    }
  }
}