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

#ifndef SKLAND_CALLBACK_HPP
#define SKLAND_CALLBACK_HPP

#include "skland/core/delegate.hpp"
#include "skland/core/defines.hpp"

#include <memory>

namespace skland {
namespace gui {

class Display;
class Surface;

/**
 * @ingroup gui
 * @brief Callback class in gui module
 */
class Callback {

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Callback);

  template<typename ReturnType, typename ... ParamTypes>
  using DelegateRef = typename core::DelegateRef<ReturnType, ParamTypes...>;

  template<typename ReturnType, typename ... ParamTypes>
  using Delegate = typename core::Delegate<ReturnType, ParamTypes...>;

  Callback();

  explicit Callback(const Display &display);

  explicit Callback(const Surface &surface);

  ~Callback();

  void Setup(const Display &display);

  void Setup(const Surface &surface);

  /**
   * @brief A delegate to the 'done' event
   */
  DelegateRef<void(uint32_t)> done() { return done_; }

 private:

  struct Private;

  std::unique_ptr<Private> p_;

  Delegate<void(uint32_t)> done_;

};

} // namespace gui
} // namespace skland

#endif //SKLAND_CALLBACK_HPP
