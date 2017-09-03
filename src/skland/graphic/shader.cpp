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

#include "internal/shader_private.hpp"

#include <skland/core/defines.hpp>

namespace skland {
namespace graphic {

Shader::Shader() {
  p_.reset(new Private);
}

Shader::Shader(Private *p)
    : p_(p) {
  _ASSERT(p_);
}

Shader::Shader(const Shader &other) {
  p_.reset(new Private(other.p_->sk_shader));
}

Shader::~Shader() {

}

Shader &Shader::operator=(const Shader &other) {
  *p_ = *other.p_;
  return *this;
}

Shader::operator bool() const {
  return p_->sk_shader.get() != nullptr;
}

} // namespace graphic
} // namespace skland
