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

#ifndef SKLAND_GUI_INTERNAL_DISPLAY_REGISTRY_HPP_
#define SKLAND_GUI_INTERNAL_DISPLAY_REGISTRY_HPP_

#include <skland/gui/display.hpp>
#include "display_private.hpp"

namespace skland {
namespace gui {

/**
 * @ingroup gui_intern
 * @brief An nested class to get native platform objects from the private properties of Display
 */
SKLAND_NO_EXPORT struct Display::Proxy {

  Proxy() = delete;
  Proxy(const Proxy &) = delete;
  Proxy &operator=(const Proxy &) = delete;
  ~Proxy() = delete;

  /**
   * @brief Get the native wayland display object
   * @return
   */
  static struct wl_display *wl_display() {
    return Display::kDisplay->p_->wl_display;
  }

  /**
   * @brief Get the native wayland registry object
   * @return
   */
  static struct wl_registry *wl_registry() {
    return Display::kDisplay->p_->wl_registry;
  }

  /**
   * @brief Get the native wayland compositor object
   * @return
   */
  static struct wl_compositor *wl_compositor() {
    return Display::kDisplay->p_->wl_compositor;
  }

  /**
   * @brief Get the native wayland subcompositor object
   * @return
   */
  static struct wl_subcompositor *wl_subcompositor() {
    return Display::kDisplay->p_->wl_subcompositor;
  }

  /**
   * @brief Get the native wayland shm object
   * @return
   */
  static struct wl_shm *wl_shm() {
    return Display::kDisplay->p_->wl_shm;
  }

  /**
   * @brief Get the native xdg shell (in unstable protocol) object
   * @return
   */
  static struct zxdg_shell_v6 *xdg_shell() {
    return Display::kDisplay->p_->xdg_shell;
  }

  /**
   * @brief Get the native wayland shell object
   * @return
   */
  static struct wl_shell *wl_shell() {
    return Display::kDisplay->p_->wl_shell;
  }

  /**
   * @brief Get the native wayland data device manager
   * @return
   */
  static struct wl_data_device_manager *wl_data_device_manager() {
    return Display::kDisplay->p_->wl_data_device_manager;
  }

  /**
   * @brief Get the native EGL display
   * @return
   */
  static EGLDisplay egl_display() {
    return Display::kDisplay->p_->egl_display;
  }

  /**
   * @brief Get the native EGL config
   * @return
   */
  static EGLConfig egl_config() {
    return Display::kDisplay->p_->egl_config;
  }

  /**
   * @brief Get the native EGL context
   * @return
   */
  static EGLContext egl_context() {
    return Display::kDisplay->p_->egl_context;
  }

  /**
   * @brief Get the native C++ Vulkan instance
   * @return
   */
  static const vk::Instance vk_instance() {
    return Display::kDisplay->p_->vk_instance;
  }

  /**
   * @brief Get the native xkb context
   * @return The xkb_context object for keymap
   */
  static struct xkb_context *xkb_context() {
    return Display::kDisplay->p_->xkb_context;
  }

  static PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC kSwapBuffersWithDamageAPI;

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_INTERNAL_DISPLAY_PROXY_HPP_
