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

#ifndef SKLAND_GUI_VULKAN_INTERFACE_HPP_
#define SKLAND_GUI_VULKAN_INTERFACE_HPP_

#include "abstract-graphics-interface.hpp"

#include <vulkan/vulkan.hpp>

namespace skland {
namespace gui {

class Surface;

/**
 * @ingroup gui
 * @brief Vulkan
 */
class VulkanInterface : public AbstractGraphicsInterface {

 public:

  VulkanInterface();

  virtual ~VulkanInterface();

  virtual void Setup(Surface *surface) final;

 private:

  vk::SurfaceKHR vk_surface_;

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_VULKAN_ENGINE_HPP_
