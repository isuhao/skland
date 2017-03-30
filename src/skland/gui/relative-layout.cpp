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

RelativeLayout::~RelativeLayout() {

}

void RelativeLayout::OnViewAdded(AbstractView *view) {
  if (view->IsVisible())
    Update();
}

void RelativeLayout::OnViewRemoved(AbstractView *view) {
  if (view->IsVisible())
    Update();
}

void RelativeLayout::OnLayout(int dirty_flag, int left, int top, int right, int bottom) {
  const AnchorGroup &left_group = GetAnchorGroup(kAlignLeft);
  for (Anchor *anchor = left_group.first(); anchor; anchor = anchor->next()) {
    anchor->contrary()->group()->view()->SetLeft(left + anchor->distance());
  }

  const AnchorGroup &top_group = GetAnchorGroup(kAlignTop);
  for (Anchor *anchor = top_group.first(); anchor; anchor = anchor->next()) {
    anchor->contrary()->group()->view()->SetTop(top + anchor->distance());
  }

  const AnchorGroup &right_group = GetAnchorGroup(kAlignRight);
  for (Anchor *anchor = right_group.first(); anchor; anchor = anchor->next()) {
    anchor->contrary()->group()->view()->SetRight(right - anchor->distance());
  }

  const AnchorGroup &bottom_group = GetAnchorGroup(kAlignBottom);
  for (Anchor *anchor = bottom_group.first(); anchor; anchor = anchor->next()) {
    anchor->contrary()->group()->view()->SetBottom(bottom - anchor->distance());
  }
}

}
