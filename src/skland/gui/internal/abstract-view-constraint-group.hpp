/*
 * Copyright 2016 Freeman Zhang <zhanggyb@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SKLAND_GUI_INTERNAL_ABSTRACT_VIEW_CONSTRAINT_GROUP_HPP_
#define SKLAND_GUI_INTERNAL_ABSTRACT_VIEW_CONSTRAINT_GROUP_HPP_

#include <skland/gui/abstract-view.hpp>
#include <skland/core/types.hpp>

namespace skland {

class AbstractView::ConstraintGroup {

  ConstraintGroup() = delete;
  ConstraintGroup(const ConstraintGroup &) = delete;
  ConstraintGroup &operator=(const ConstraintGroup &) = delete;

 public:

  ConstraintGroup(Align align)
      : view(nullptr),
        first_(nullptr),
        last_(nullptr),
        count_(0),
        align_(align) {}

  ~ConstraintGroup() {}

 private:

  AbstractView *view;

  Constraint *first_;
  Constraint *last_;
  int count_;
  Align align_;

};

}

#endif // SKLAND_GUI_INTERNAL_ABSTRACT_VIEW_CONSTRAINT_GROUP_HPP_
