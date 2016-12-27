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

#include <skland/graphic/gradient-shader.hpp>
#include <skland/graphic/matrix.hpp>

#include "internal/shader-meta.hpp"

#include "SkGradientShader.h"

namespace skland {

Shader GradientShader::MakeLinear(const Point2F *points,
                                  const uint32_t *colors,
                                  const float *pos,
                                  int count,
                                  Shader::TileMode mode,
                                  uint32_t flags,
                                  const Matrix *local_matrix) {
  sk_sp<SkShader> sk_shader =
      SkGradientShader::MakeLinear(reinterpret_cast<const SkPoint *>(points),
                                   colors,
                                   pos,
                                   count,
                                   (SkShader::TileMode) mode,
                                   flags,
                                   nullptr == local_matrix ? nullptr : local_matrix->sk_matrix());

  return Shader(new ShaderMeta(sk_shader));
}

Shader GradientShader::MakeLinear(const Point2F points[],
                                  const Color colors[],
                                  const float pos[],
                                  int count,
                                  Shader::TileMode mode,
                                  uint32_t flags,
                                  const Matrix *local_matrix) {
  sk_sp<SkShader> sk_shader =
      SkGradientShader::MakeLinear(reinterpret_cast<const SkPoint *>(points),
                                   reinterpret_cast<const SkColor4f *>(colors),
                                   nullptr, // TODO: use ColorSpace
                                   pos,
                                   count,
                                   (SkShader::TileMode) mode,
                                   flags,
                                   nullptr == local_matrix ? nullptr : local_matrix->sk_matrix());

  return Shader(new ShaderMeta(sk_shader));
}

Shader GradientShader::MakeRadial(const Point2F &center,
                                  float radius,
                                  const uint32_t colors[],
                                  const float pos[],
                                  int count,
                                  Shader::TileMode mode,
                                  uint32_t flags,
                                  const Matrix *local_matrix) {
  sk_sp<SkShader> sk_shader =
      SkGradientShader::MakeRadial(reinterpret_cast<const SkPoint &>(center),
                                   radius,
                                   colors,
                                   pos,
                                   count,
                                   (SkShader::TileMode) mode,
                                   flags,
                                   nullptr == local_matrix ? nullptr : local_matrix->sk_matrix());
  return Shader(new ShaderMeta(sk_shader));
}

Shader GradientShader::MakeRadial(const Point2F &center,
                                  float radius,
                                  const Color colors[],
                                  const float pos[],
                                  int count,
                                  Shader::TileMode mode,
                                  uint32_t flags,
                                  const Matrix *local_matrix) {
  sk_sp<SkShader> sk_shader =
      SkGradientShader::MakeRadial(reinterpret_cast<const SkPoint &>(center),
                                   radius,
                                   reinterpret_cast<const SkColor4f *>(colors),
                                   nullptr, // TODO: use ColorSpace
                                   pos,
                                   count,
                                   (SkShader::TileMode) mode,
                                   flags,
                                   nullptr == local_matrix ? nullptr : local_matrix->sk_matrix());

  return Shader(new ShaderMeta(sk_shader));
}

}
