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

#ifndef SKLAND_BUFFER_PRIVATE_HPP
#define SKLAND_BUFFER_PRIVATE_HPP

#include <skland/gui/buffer.hpp>

namespace skland {

struct Buffer::Private {

  Private(const Private &) = delete;
  Private &operator=(const Private &) = delete;

  Private()
      : wl_buffer(nullptr),
        stride(0),
        format(0),
        offset(0),
        data(nullptr) {}

  ~Private() {
    if (wl_buffer)
      wl_buffer_destroy(wl_buffer);
  }

  struct wl_buffer *wl_buffer;

  /**
   * @brief Position on surface
   */
  Point position;

  Size size;

  int32_t stride;

  uint32_t format;

  int offset;

  void *data;

};

}

#endif //SKLAND_BUFFER_PRIVATE_HPP