//
// Created by niazh on 22.04.2021.
//

#ifndef SEMESTER_WORK_TEMPLATE_TWOTHREENODE_H
#define SEMESTER_WORK_TEMPLATE_TWOTHREENODE_H

#endif  //SEMESTER_WORK_TEMPLATE_TWOTHREENODE_H

#pragma once

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

    bool find(int k);

    void swap(int &x, int &y);

    void sort2(int &x, int &y);

    void sort3(int &x, int &y, int &z);

    void sort();

    void insert_to_node(int k); // vstavka

    void remove_from_node(int k); // udalenie

    void become_node2(int k, TwoThreeNode *first_, TwoThreeNode *second_);

    bool is_leaf();


  };
}
