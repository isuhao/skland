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

#include <skland/gui/task.hpp>

namespace skland {
namespace gui {

Task::~Task() {
  if (previous_) previous_->next_ = next_;
  if (next_) next_->previous_ = previous_;
}

void Task::PushBack(Task *other) {
  if (other == this) return;

  other->Unlink();

  if (next_) next_->previous_ = other;
  other->next_ = next_;
  next_ = other;
  other->previous_ = this;
}

void Task::PushFront(Task *other) {
  if (other == this) return;

  other->Unlink();

  if (previous_) previous_->next_ = other;
  other->previous_ = previous_;
  previous_ = other;
  other->next_ = this;
}

void Task::PushBack(Task *first, Task *last) {
  if (first == this) return;

  if (first->previous_) first->previous_->next_ = last->next_;
  if (last->next_) last->next_->previous_ = first->previous_;

  if (next_) next_->previous_ = last;
  last->next_ = next_;

  first->previous_ = this;
  next_ = first;
}

void Task::PushFront(Task *first, Task *last) {
  if (last == this) return;

  if (first->previous_) first->previous_->next_ = last->next_;
  if (last->next_) last->next_->previous_ = first->previous_;

  if (previous_) previous_->next_ = first;
  first->previous_ = previous_;

  previous_ = last;
  last->next_ = this;
}

void Task::Unlink() {
  if (previous_) previous_->next_ = next_;
  if (next_) next_->previous_ = previous_;

  previous_ = nullptr;
  next_ = nullptr;
}

} // namespace gui
} // namespace skland
