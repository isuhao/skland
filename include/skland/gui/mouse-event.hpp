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

#ifndef SKLAND_GUI_MOUSE_EVENT_HPP_
#define SKLAND_GUI_MOUSE_EVENT_HPP_

#include "input-event.hpp"

#include "../core/point.hpp"

#include <wayland-client.h>
#include <linux/input-event-codes.h>

#include <memory>

namespace skland {
namespace gui {

class Surface;

enum MouseButton {
  kMouseButtonLeft = BTN_LEFT,
  kMouseButtonRight = BTN_RIGHT,
  kMouseButtonMiddle = BTN_MIDDLE
};

enum MouseButtonState {
  kMouseButtonReleased = WL_POINTER_BUTTON_STATE_RELEASED,  /* 0 */
  kMouseButtonPressed = WL_POINTER_BUTTON_STATE_PRESSED /* 1 */
};

SKLAND_EXPORT class MouseEvent : public InputEvent {

  friend class Input;

  MouseEvent() = delete;
  MouseEvent(const MouseEvent &orig) = delete;
  MouseEvent &operator=(const MouseEvent &other) = delete;

 public:

  MouseEvent(Input *input);

  Surface *GetSurface() const;

  uint32_t GetSerial() const;

  const core::Point2D &GetSurfaceXY() const;

  core::Point2D GetWindowXY() const;

  uint32_t GetButton() const;

  uint32_t GetState() const;

  uint32_t GetAxis() const;

 private:

  struct Private;

  ~MouseEvent();

  std::unique_ptr<Private> p_;

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_MOUSE_EVENT_HPP_
