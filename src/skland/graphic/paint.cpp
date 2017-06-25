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

#include <skland/graphic/paint.hpp>
#include <skland/graphic/shader.hpp>

#include "SkPaint.h"
#include "SkTypeface.h"

#include "internal/font_private.hpp"
#include "internal/shader_private.hpp"

namespace skland {
namespace graphic {

using core::RectF;
using core::ColorF;

struct Paint::Private {

  Private() {}

  Private(const Private &orig)
      : sk_paint(orig.sk_paint) {}

  ~Private() {}

  SkPaint sk_paint;

};

Paint::Paint() {
  p_.reset(new Private);
}

Paint::Paint(const Paint &orig) {
  p_.reset(new Private(*orig.p_));
}

Paint::~Paint() {
}

Paint &Paint::operator=(const Paint &other) {
  *p_ = *other.p_;
  return *this;
}

uint32_t Paint::GetHash() const {
  return p_->sk_paint.getHash();
}

void Paint::Reset() {
  p_->sk_paint.reset();
}

Paint::Hinting Paint::GetHinting() const {
  return static_cast<Hinting>(p_->sk_paint.getHinting());
}

void Paint::SetHinting(Hinting hinting) {
  p_->sk_paint.setHinting(static_cast<SkPaint::Hinting >(hinting));
}

bool Paint::IsAntiAlias() const {
  return p_->sk_paint.isAntiAlias();
}

void Paint::SetAntiAlias(bool aa) {
  p_->sk_paint.setAntiAlias(aa);
}

void Paint::SetStyle(Style style) {
  p_->sk_paint.setStyle(static_cast<SkPaint::Style>(style));
}

ColorF Paint::GetColor() const {
  uint32_t value = p_->sk_paint.getColor();
  return ColorF::FromUCharRGBA(SkToU8(SkColorGetR(value)),
                              SkToU8(SkColorGetG(value)),
                              SkToU8(SkColorGetB(value)),
                              SkToU8(SkColorGetA(value)));
}

void Paint::SetColor(uint32_t argb) {
  p_->sk_paint.setColor(argb);
}

void Paint::SetColor(const ColorF &color) {
  p_->sk_paint.setARGB(color.uchar_alpha(),
                       color.uchar_red(),
                       color.uchar_green(),
                       color.uchar_blue());
}

float Paint::GetStrokeWidth() const {
  return p_->sk_paint.getStrokeWidth();
}

void Paint::SetStrokeWidth(float width) {
  p_->sk_paint.setStrokeWidth(width);
}

void Paint::SetFont(const Font &font) {
  SkTypeface *ptr = font.GetSkTypeface();
  sk_sp<SkTypeface> typeface = SkTypeface::MakeFromTypeface(ptr, ptr->style());
  p_->sk_paint.setTypeface(typeface);
}

void Paint::SetShader(const Shader &shader) {
  p_->sk_paint.setShader(shader.p_->sk_shader);
}

Paint::Align Paint::GetTextAlign() const {
  return static_cast<Align>(p_->sk_paint.getTextAlign());
}

void Paint::SetTextAlign(Align align) {
  p_->sk_paint.setTextAlign(static_cast<SkPaint::Align>(align));
}

float Paint::GetTextSize() const {
  return p_->sk_paint.getTextSize();
}

void Paint::SetTextSize(float size) {
  p_->sk_paint.setTextSize(size);
}

float Paint::GetTextScaleX() const {
  return p_->sk_paint.getTextScaleX();
}

void Paint::SetTextScaleX(float scale_x) {
  p_->sk_paint.setTextScaleX(scale_x);
}

float Paint::GetTextSkewX() const {
  return p_->sk_paint.getTextSkewX();
}

void Paint::SetTextSkewX(float skew_x) {
  p_->sk_paint.setTextSkewX(skew_x);
}

TextEncoding Paint::GetTextEncoding() const {
  return static_cast<TextEncoding>(p_->sk_paint.getTextEncoding());
}

void Paint::SetTextEncoding(TextEncoding encoding) {
  p_->sk_paint.setTextEncoding(static_cast<SkPaint::TextEncoding>(encoding));
}

int Paint::TextToGlyphs(const void *text, size_t byte_length, uint16_t *glyphs) const {
  return p_->sk_paint.textToGlyphs(text, byte_length, glyphs);
}

bool Paint::ContainsText(const void *text, size_t byte_length) const {
  return p_->sk_paint.containsText(text, byte_length);
}

void Paint::GlyphsToUnichars(const uint16_t glyphs[], int count, int32_t text[]) const {
  p_->sk_paint.glyphsToUnichars(glyphs, count, text);
}

int Paint::CountText(const void *text, size_t byte_length) const {
  return p_->sk_paint.countText(text, byte_length);
}

float Paint::MeasureText(const void *text, size_t length, RectF *boulds) const {
  return p_->sk_paint.measureText(text, length, reinterpret_cast<SkRect *>(boulds));
}

const SkPaint &Paint::GetSkPaint() const {
  return p_->sk_paint;
}

bool operator==(const Paint &paint1, const Paint &paint2) {
  return paint1.p_ == paint2.p_;
}

bool operator!=(const Paint &paint1, const Paint &paint2) {
  return paint1.p_ != paint2.p_;
}

} // namespace graphic
} // namespace skland
