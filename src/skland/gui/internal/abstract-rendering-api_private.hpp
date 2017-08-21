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

#ifndef SKLAND_GUI_INTERNAL_ABSTRACT_RENDERING_API_PRIVATE_HPP_
#define SKLAND_GUI_INTERNAL_ABSTRACT_RENDERING_API_PRIVATE_HPP_

#include "skland/gui/abstract-rendering-api.hpp"

#include "surface_private.hpp"

namespace skland {
namespace gui {

/**
 * @ingroup gui_intern
 * @brief Structure for private data in AbstractGPUInterface
 */
struct AbstractRenderingAPI::Private {

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Private);

  Private() = default;

  ~Private() = default;

  Surface *surface = nullptr;

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_INTERNAL_ABSTRACT_GR_API_PRIVATE_HPP_
