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

#include "surface_private.hpp"

#include <skland/gui/abstract-event-handler.hpp>

namespace skland {

const struct wl_surface_listener Surface::Private::kListener = {
    OnEnter,
    OnLeave
};

void Surface::Private::OnEnter(void *data, struct wl_surface *wl_surface, struct wl_output *wl_output) {
  const Surface *_this = static_cast<const Surface *>(data);
  const Output *output = static_cast<const Output *>(wl_output_get_user_data(wl_output));
  _this->p_->event_handler->OnEnterOutput(_this, output);
}

void Surface::Private::OnLeave(void *data, struct wl_surface *wl_surface, struct wl_output *wl_output) {
  const Surface *_this = static_cast<const Surface *>(data);
  const Output *output = static_cast<const Output *>(wl_output_get_user_data(wl_output));
  _this->p_->event_handler->OnLeaveOutput(_this, output);
}

}
