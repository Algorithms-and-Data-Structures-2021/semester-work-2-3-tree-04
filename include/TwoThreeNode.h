//
// Created by niazh on 22.04.2021.
//

#ifndef SEMESTER_WORK_TEMPLATE_TWOTHREENODE_H
#define SEMESTER_WORK_TEMPLATE_TWOTHREENODE_H

#endif  //SEMESTER_WORK_TEMPLATE_TWOTHREENODE_H

namespace itis {
  struct TwoThreeNode {
    int size;
    int key[3];

    TwoThreeNode *first{nullptr};
    TwoThreeNode *second{nullptr};
    TwoThreeNode *third{nullptr};
    TwoThreeNode *fourth{nullptr};
    TwoThreeNode *parent{nullptr};

    explicit TwoThreeNode (int k, TwoThreeNode *first_ = nullptr, TwoThreeNode *second_ = nullptr,
                                  TwoThreeNode *third_ = nullptr, TwoThreeNode *parent_ = nullptr,
                                                                  TwoThreeNode *fourth_ = nullptr);
  };
}
