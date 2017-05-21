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

#ifndef SKLAND_GUI_INTERNAL_OUTPUT_PRIVATE_HPP_
#define SKLAND_GUI_INTERNAL_OUTPUT_PRIVATE_HPP_

#include <skland/gui/output.hpp>

namespace skland {

struct Output::Private {

  Private(const Private &) = delete;
  Private &operator=(const Private &) = delete;

  Private()
      : wl_output(nullptr),
        current_refresh_rate(0),
        preferred_refresh_rate(0),
        subpixel(0),
        transform(WL_OUTPUT_TRANSFORM_NORMAL),
        scale(1),
        id(0),
        version(0) {}

  ~Private() {
    if (wl_output)
      wl_output_destroy(wl_output);
  }

  struct wl_output *wl_output;

  /** position within the global compositor space */
  Point position_;

  /** physical_width width in millimeters of the output */
  Size physical_size_;

  /** The size of a mode, given in physical hardware units of the output device */
  Size current_mode_size_;
  Size preferred_mode_size_;
  int32_t current_refresh_rate;
  int32_t preferred_refresh_rate;

  int subpixel;  /**< enum value of wl_output_subpixel */
  int transform; /**< enum value of wl_output_transform */
  int scale;

  /* vertical refresh rate in mHz */

  std::string make_;
  std::string model_;

  uint32_t id;
  uint32_t version;
};

}

#endif // SKLAND_GUI_INTERNAL_OUTPUT_PRIVATE_HPP_