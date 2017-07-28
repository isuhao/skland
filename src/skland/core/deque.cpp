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

#include "skland/core/deque.hpp"
#include "skland/core/assert.hpp"

namespace skland {
namespace core {

BiNode::~BiNode() {
  if (nullptr != previous_) previous_->next_ = next_;
  if (nullptr != next_) next_->previous_ = previous_;
}

void BiNode::PushFront(BiNode *other) {
  if (other == this) return;

  other->Unlink();

  if (nullptr != previous_) previous_->next_ = other;
  other->previous_ = previous_;
  previous_ = other;
  other->next_ = this;
}

void BiNode::PushBack(BiNode *other) {
  if (other == this) return;

  other->Unlink();

  if (nullptr != next_) next_->previous_ = other;
  other->next_ = next_;
  next_ = other;
  other->previous_ = this;
}

void BiNode::Unlink() {
  if (nullptr != previous_) previous_->next_ = next_;
  if (nullptr != next_) next_->previous_ = previous_;

  previous_ = nullptr;
  next_ = nullptr;
}

} // namespace core
} // namespace skland
