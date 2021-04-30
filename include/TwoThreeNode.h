//
// Created by niazh on 22.04.2021.
//

#pragma once

namespace itis {

  struct TwoThreeNode {

    int size;
    int keys[3];

    TwoThreeNode *left{nullptr};
    TwoThreeNode *middle{nullptr};
    TwoThreeNode *right{nullptr};
    TwoThreeNode *additionalElement{nullptr};
    TwoThreeNode *parent{nullptr};

    explicit TwoThreeNode (int key, TwoThreeNode *left_ = nullptr, TwoThreeNode *middle_ = nullptr,
                                  TwoThreeNode *right_ = nullptr, TwoThreeNode *parent_ = nullptr,
                                                                  TwoThreeNode *additionalElement_ = nullptr);

    bool isContains(int key);

    void swapKeys(int &a, int &b);

    void sortTwoElements(int &a, int &b);

    void sortThreeElements(int &a, int &b, int &c);

    void sortKeys();

    void insertKey(int newKey);

    void removeByKey(int key);

    void becomeTwoKeyNode(int key, TwoThreeNode *left_, TwoThreeNode *right_);

    bool isLeaf();
  };
}
