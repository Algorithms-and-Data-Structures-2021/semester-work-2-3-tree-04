#pragma once

#include "TwoThreeNode.h"
#include "traversalAlgorithm.h"

namespace itis {
  
  struct TwoThreeTree {

    void Clear();

    void Insert(int key);

    TwoThreeNode *Search(int key);

    void *Remove(int key);

    TwoThreeNode *getRoot();

    int getHeight();

    void Traverse(const TraversalAlgorithm &algorithm) const;

   private:
    TwoThreeNode *root_{nullptr};

    TwoThreeNode *mergeNode(TwoThreeNode *leaf);

    TwoThreeNode *rotate(TwoThreeNode *leaf);

    TwoThreeNode *putRight(TwoThreeNode *leaf);

    TwoThreeNode *splitTwoTreeNode(TwoThreeNode *twoTreeNode);

    void insertIfRootExists(int key, TwoThreeNode *twoTreeNode);

    void downstreamClear(TwoThreeNode *twoTreeNode);

    TwoThreeNode *downstreamSearch(int key, TwoThreeNode *twoTreeNode);

    TwoThreeNode *downstreamRemove(int key, TwoThreeNode *twoTreeNode);

    int calculateHeight(TwoThreeNode *twoTreeNode);

    TwoThreeNode *downstreamSearchForMin(TwoThreeNode *twoTreeNode);
  };

}