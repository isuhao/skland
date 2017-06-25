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

#ifndef SKLAND_GUI_OUTPUT_HPP_
#define SKLAND_GUI_OUTPUT_HPP_

#include "../core/rect.hpp"
#include "../core/size.hpp"
#include "../core/sigcxx.hpp"
#include "../core/deque.hpp"

#include <wayland-client.h>

#include <string>
#include <memory>

namespace skland {
namespace gui {

class Output : public core::Deque::Element {

  friend class Surface;

  Output() = delete;
  Output(const Output &) = delete;
  Output &operator=(const Output &) = delete;

 public:

  Output(uint32_t id, uint32_t version);

  virtual ~Output();

  core::SignalRef<Output *> destroyed() { return destroyed_; }

  int GetSubPixel() const;

  int GetTransform() const;

  int GetScale() const;

  const std::string &GetMake() const;

  const std::string &GetModel() const;

  uint32_t GetID() const;

  uint32_t GetVersion() const;

 private:

  struct Private;

  std::unique_ptr<Private> p_;

  core::Signal<Output *> destroyed_;

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_OUTPUT_HPP_
