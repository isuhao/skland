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

#include <skland/gui/slider.hpp>

#include <skland/gui/mouse-event.hpp>
#include <skland/gui/key-event.hpp>

#include <skland/gui/context.hpp>
#include <skland/graphic/canvas.hpp>
#include <skland/graphic/paint.hpp>

#include <skland/gui/timer.hpp>

namespace skland {
namespace gui {

Slider::Slider(Orientation orientation)
    : AbstractSlider<int>(orientation),
      hover_(false) {

  /* Debug */
  srand((unsigned int) Timer::GetClockTime());
  regular_.red = std::rand() % 255 / 255.f;
  regular_.green = std::rand() % 255 / 255.f;
  regular_.blue = std::rand() % 255 / 255.f;

  highlight_ = regular_ + 25;
  active_ = regular_ - 25;

}

Slider::~Slider() {

}

void Slider::OnConfigureGeometry(const RectF &old_geometry, const RectF &new_geometry) {
  if (old_geometry != new_geometry) {
    RequestSaveGeometry();
  }
}

void Slider::OnSaveGeometry(const RectF &old_geometry, const RectF &new_geometry) {
  Update();
}

void Slider::OnMouseEnter(MouseEvent *event) {
  hover_ = true;
  Update();
  event->Accept();
}

void Slider::OnMouseLeave() {
  hover_ = false;
  Update();
//  event->Accept();
}

void Slider::OnMouseMove(MouseEvent *event) {
  event->Accept();
}

void Slider::OnMouseDown(MouseEvent *event) {
  event->Accept();
}

void Slider::OnMouseUp(MouseEvent *event) {
  event->Accept();
}

void Slider::OnKeyDown(KeyEvent *event) {
  event->Accept();
}

void Slider::OnKeyUp(KeyEvent *event) {
  event->Accept();
}

void Slider::OnSetValue(const int &value) {
  int new_value = value - value % step();

  if (new_value != this->value()) {
    set_value(value - value % step());
    Update();
    EmitSignal();
  }
}

void Slider::OnSetMinimum(const int &minimum) {
  // int new_minimum = minimum - minimum % step();

  set_minimum(minimum);
}

void Slider::OnSetMaximum(const int &maximum) {
  set_maximum(maximum);
}

void Slider::OnDraw(const Context &context) {
  using graphic::Canvas;
  using graphic::Paint;

  Canvas *canvas = context.canvas();
  Paint paint;

  if (hover_) {
    paint.SetColor(highlight_);
  } else {
    paint.SetColor(regular_);
  }
  canvas->DrawRect(GetGeometry(), paint);

  paint.SetColor(active_);

  const Rect &rect = GetGeometry();
  int hw = 8;
  int hh = 8;
  if (orientation() == kHorizontal) {
    hh = rect.height() / 2;
  } else {
    hw = rect.width() / 2;
  }
  canvas->DrawRect(core::RectF::MakeFromLTRB(rect.center_x() - hw,
                                             rect.center_y() - hh,
                                             rect.center_x() + hw,
                                             rect.center_y() + hh), paint);


//  paint.SetStyle(Paint::Style::kStyleStroke);
//  paint.SetColor(0xEF444444);
//  paint.SetStrokeWidth(1.f);
//  canvas->DrawLine(GetGeometry().l, GetGeometry().center_y(), GetGeometry().r, GetGeometry().center_y(), paint);
//  paint.SetAntiAlias(true);
//  paint.SetColor(0xFFDF5E00);
//  canvas->DrawCircle(GetGeometry().center_x(), GetGeometry().center_y(), 5.f, paint);
//  paint.SetColor(0xFFFF7E00);
//  paint.SetStyle(Paint::Style::kStyleFill);
//  canvas->DrawCircle(GetGeometry().center_x(), GetGeometry().center_y(), 5.f, paint);
}

} // namespace gui
} // namespace skland
