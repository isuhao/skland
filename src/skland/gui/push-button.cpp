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

#include <skland/gui/push-button.hpp>
#include <skland/gui/mouse-event.hpp>
#include <skland/gui/context.hpp>

#include <skland/graphic/canvas.hpp>
#include <skland/graphic/paint.hpp>
#include <skland/graphic/text-box.hpp>
#include <skland/graphic/path.hpp>
#include <skland/graphic/gradient-shader.hpp>
#include "skland/graphic/font-style.hpp"

#include <skland/gui/theme.hpp>

#include <skland/gui/timer.hpp>
#include "skland/core/color.hpp"

namespace skland {
namespace gui {

using core::RectF;
using graphic::Canvas;
using graphic::Paint;
using graphic::Path;
using graphic::Shader;
using graphic::Font;
using graphic::TextBox;
using graphic::FontStyle;

PushButton::PushButton(const std::string &text)
    : AbstractButton(text) {

  /* Debug */
  srand((unsigned int) Timer::GetClockTime());
  regular_.red = std::rand() % 255 / 255.f;
  regular_.green = std::rand() % 255 / 255.f;
  regular_.blue = std::rand() % 255 / 255.f;

  highlight_ = regular_ + 25;
  active_ = regular_ - 25;

  SetFont(Font("Noto Sans CJK SC",
               FontStyle(),
               12.f));
}

PushButton::~PushButton() {

}

void PushButton::OnDraw(const Context &context) {
  Canvas *canvas = context.canvas();

  const RectF &geometry = GetGeometry();
  int scale = context.surface()->GetScale();
  Canvas::ClipGuard guard(canvas, geometry * scale);

  canvas->Clear();
  canvas->Scale(scale, scale);

  Paint paint;
  paint.SetAntiAlias(true);
  if (IsHovered()) {
    if (IsPressed()) {
      paint.SetColor(active_);
      canvas->DrawRect(GetGeometry(), paint);
    } else {
      paint.SetColor(highlight_);
      canvas->DrawRect(GetGeometry(), paint);
    }
  } else {
    paint.SetColor(regular_);
    canvas->DrawRect(GetGeometry(), paint);
  }

  const Font &font = GetFont();
  const std::string &text = GetText();

//  paint.SetColor(schema.inactive.foreground.color);
  ColorF text_color = regular_;
  text_color.ReverseRGB();
  paint.SetColor(text_color);
  paint.SetStyle(Paint::kStyleFill);
  paint.SetFont(font);
  paint.SetTextSize(font.GetSize());

  float text_width = paint.MeasureText(text.c_str(), text.length());

  TextBox text_box;
  // Put the text at the center
  text_box.SetBox(geometry.l + (geometry.width() - text_width) / 2.f,
                  geometry.t + 1.f, // move down a little for better look
                  geometry.r - (geometry.width() - text_width) / 2.f,
                  geometry.b);
  text_box.SetSpacingAlign(TextBox::kSpacingAlignCenter);
  text_box.SetText(text.c_str(), text.length(), paint);
  text_box.Draw(*canvas);
}

} // namespace gui
} // namespace skland
