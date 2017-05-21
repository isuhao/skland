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

#include "internal/input_private.hpp"

#include "internal/display_registry.hpp"

namespace skland {

Input::Input(uint32_t id, uint32_t version)
    : Deque::Element() {
  p_.reset(new Private);
  p_->id = id;
  p_->version = version;

  p_->wl_seat =
      static_cast<struct wl_seat *>(wl_registry_bind(Display::Registry().wl_registry(),
                                                     id,
                                                     &wl_seat_interface,
                                                     version));
  wl_seat_add_listener(p_->wl_seat, &Private::kSeatListener, this);
}

Input::~Input() {
  p_.reset();
}

void Input::SetCursor(const Cursor *cursor) const {
  wl_pointer_set_cursor(p_->wl_pointer, p_->mouse_event->GetSerial(),
                        cursor->wl_surface_,
                        cursor->hotspot_x(), cursor->hotspot_y());
  cursor->Commit();
}

uint32_t Input::GetID() const {
  return p_->id;
}

uint32_t Input::GetVersion() const {
  return p_->version;
}

}
