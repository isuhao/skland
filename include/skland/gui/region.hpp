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

#ifndef SKLAND_GUI_REGION_HPP_
#define SKLAND_GUI_REGION_HPP_

#include <wayland-client.h>

namespace skland {
namespace gui {

class Region {

  friend class Surface;

  Region(const Region &) = delete;
  Region &operator=(const Region &)  = delete;

 public:

  Region();

  ~Region();

  void Add(int32_t x, int32_t y, int32_t width, int32_t height) const {
    wl_region_add(wl_region_, x, y, width, height);
  }

  void Subtract(int32_t x, int32_t y, int32_t width, int32_t height) const {
    wl_region_subtract(wl_region_, x, y, width, height);
  }

 private:

  struct wl_region *wl_region_;

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_REGION_HPP_
