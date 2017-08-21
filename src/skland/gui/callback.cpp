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

#include "skland/gui/callback.hpp"

#include "internal/display_private.hpp"
#include "internal/surface_private.hpp"

#include "skland/core/memory.hpp"

namespace skland {
namespace gui {

struct Callback::Private {

  Private(const Private &) = delete;
  Private &operator=(const Private &) = delete;

  Private() = default;

  ~Private() {
    if (nullptr != wl_callback) wl_callback_destroy(wl_callback);
  }

  void Destroy() {
    if (nullptr != wl_callback) {
      wl_callback_destroy(wl_callback);
      wl_callback = nullptr;
    }
  }

  static void OnDone(void *data,
                     struct wl_callback *wl_callback,
                     uint32_t callback_data);

  static const struct wl_callback_listener kListener;

  struct wl_callback *wl_callback = nullptr;

};

const struct wl_callback_listener Callback::Private::kListener = {
    OnDone
};

void Callback::Private::OnDone(void *data, struct wl_callback */*wl_callback*/, uint32_t callback_data) {
  auto *_this = static_cast<Callback *>(data);
  if (_this->done_) _this->done_(callback_data);
}

// -----

Callback::Callback() {
  p_ = core::make_unique<Private>();
}

Callback::Callback(const Display &display)
    : Callback() {
  Setup(display);
}

Callback::Callback(const Surface &surface)
    : Callback() {
  Setup(surface);
}

Callback::~Callback() {

}

void Callback::Setup(const Display &display) {
  p_->Destroy();
  p_->wl_callback = wl_display_sync(display.p_->wl_display);
  wl_callback_add_listener(p_->wl_callback, &Private::kListener, this);
}

void Callback::Setup(const Surface &surface) {
  p_->Destroy();
  p_->wl_callback = wl_surface_frame(surface.p_->wl_surface);
  wl_callback_add_listener(p_->wl_callback, &Private::kListener, this);
}

} // namespace gui
} // namespace skland
