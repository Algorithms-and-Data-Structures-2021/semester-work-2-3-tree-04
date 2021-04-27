#pragma once

// Заголовочный файл с объявлением структуры данных

#include "TwoThreeNode.h"
#include "traversalAlgorithm.h"
namespace itis {

  // Tip 1: объявите здесь необходимые структуры, функции, константы и прочее


  // Пример: объявление структуры с полями и методами
  struct TwoThreeTree {
    void Clear();

    void Insert(int k);

    TwoThreeNode *Search(int k);

    void *Remove(int k);

    TwoThreeNode *root();

    int Height();

    void Traverse(const TraversalAlgorithm &algorithm) const; // Проход по ширине

   private:
    TwoThreeNode *root_{nullptr};

    TwoThreeNode *merge(TwoThreeNode *leaf);

    TwoThreeNode *redistribute(TwoThreeNode *leaf);

    TwoThreeNode *fix(TwoThreeNode *leaf);

    TwoThreeNode *split(TwoThreeNode *item);

    void insert(int k, TwoThreeNode *node);

    void clear(TwoThreeNode *node);

    TwoThreeNode *search(int k, TwoThreeNode *node);

    TwoThreeNode *remove(int k, TwoThreeNode *node);

    int height(TwoThreeNode *node);

    TwoThreeNode *findMin(TwoThreeNode *p);
  };

}  // namespace itis