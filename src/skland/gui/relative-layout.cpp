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

#include <skland/gui/relative-layout.hpp>

#include "internal/abstract-view-iterators.hpp"

namespace skland {

RelativeLayout::RelativeLayout(const Padding &padding)
    : AbstractLayout(padding) {

}

RelativeLayout::~RelativeLayout() {

}

void RelativeLayout::OnGeometryWillChange(int dirty_flag, const Rect &old_geometry, const Rect &new_geometry) {
  if (dirty_flag) Update();
  else CancelUpdate();
}

void RelativeLayout::OnGeometryChange(int dirty_flag, const Rect &old_geometry, const Rect &new_geometry) {
  Iterator it(this);

  int dx = (int) (new_geometry.x() - old_geometry.x());
  int dy = (int) (new_geometry.y() - old_geometry.y());

  for (it = it.first_child(); it; ++it) {
    it.view()->MoveTo(it.view()->GetLeft() + dx, it.view()->GetTop() + dy);
  }
}

void RelativeLayout::OnViewAdded(AbstractView *view) {
  // TODO:
}

void RelativeLayout::OnViewRemoved(AbstractView *view) {
  // TODO:
}

}