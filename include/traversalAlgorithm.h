//
// Created by Тимур on 24.04.2021.
//

#ifndef SEMESTER_WORK_TEMPLATE_TRAVERSALALGORITHM_H
#define SEMESTER_WORK_TEMPLATE_TRAVERSALALGORITHM_H

#endif  //SEMESTER_WORK_TEMPLATE_TRAVERSALALGORITHM_H

#pragma once

#include <ostream>

#include "TwoThreeNode.h"

namespace itis {
  struct TraversalAlgorithm {
    virtual ~TraversalAlgorithm() = default;
    virtual void Print(std::ostream &os, TwoThreeNode *twoThreeNode) const = 0;
  };

  struct BreadthFirstTraversalAlgorithm final : TraversalAlgorithm {
    void Print(std::ostream &os, TwoThreeNode *twoThreeNode) const override;
  };
}
