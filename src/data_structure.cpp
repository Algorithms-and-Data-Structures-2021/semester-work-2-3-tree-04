#include "data_structure.hpp"

// файл с определениями

namespace itis {

  struct TwoThreeTree {
    void Clear();

    void Insert(int k);

    TwoThreeNode *Search(int k);
  };

}  // namespace itis