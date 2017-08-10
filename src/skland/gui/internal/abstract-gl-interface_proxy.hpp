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

#ifndef SKLAND_GUI_INTERNAL_ABSTRACT_GRAPHICS_INTERFACE_PROXY_HPP_
#define SKLAND_GUI_INTERNAL_ABSTRACT_GRAPHICS_INTERFACE_PROXY_HPP_

#include "skland/gui/abstract-gl-interface.hpp"

#include "surface_private.hpp"

namespace skland {
namespace gui {

struct AbstractGLInterface::Proxy {

  static inline struct wl_surface *GetWaylandSurface(const Surface *surface) {
    return surface->p_->wl_surface;
  }

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_INTERNAL_ABSTRACT_GRAPHICS_INTERFACE_PROXY_HPP_
