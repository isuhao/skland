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

#ifndef SKLAND_GUI_INTERNAL_DISPLAY_PRIVATE_HPP_
#define SKLAND_GUI_INTERNAL_DISPLAY_PRIVATE_HPP_

#include <skland/gui/display.hpp>

#include <skland/gui/task.hpp>
#include <skland/gui/abstract-epoll-task.hpp>

#include "xdg-shell-unstable-v6-client-protocol.h"

#include <EGL/eglext.h>

namespace skland {

/**
 * @ingroup gui_intern
 * @brief The private data structure in Display
 */
struct Display::Private {

  Private(const Private &) = delete;
  Private &operator=(const Private &) = delete;

  Private()
      : wl_display(nullptr),
        wl_registry(nullptr),
        wl_compositor(nullptr),
        wl_subcompositor(nullptr),
        wl_shm(nullptr),
        wl_shell(nullptr),
        xdg_shell(nullptr),
        wl_cursor_theme(nullptr),
        wl_data_device_manager(nullptr),
        egl_display_(nullptr),
        egl_context_(nullptr),
        egl_config_(nullptr),
        major_(0),
        minor_(0) {}

  ~Private() {}

  struct wl_display *wl_display;
  struct wl_registry *wl_registry;
  struct wl_compositor *wl_compositor;
  struct wl_subcompositor *wl_subcompositor;
  struct wl_shm *wl_shm;
  struct wl_shell *wl_shell;
  struct zxdg_shell_v6 *xdg_shell;
  struct wl_cursor_theme *wl_cursor_theme;
  struct wl_data_device_manager *wl_data_device_manager;

  EGLDisplay egl_display_;
  EGLContext egl_context_;
  EGLConfig egl_config_;

  EGLint major_;  /**< The major version */
  EGLint minor_;  /**< The minor version */

  struct xkb_context *xkb_context;

  static void OnFormat(void *data, struct wl_shm *shm, uint32_t format);

  static void OnError(void *data,
                      struct wl_display *wl_display,
                      void *object_id,
                      uint32_t code,
                      const char *message);

  static void OnDeleteId(void *data,
                         struct wl_display *wl_display,
                         uint32_t id);

  static void OnGlobal(void *data,
                       struct wl_registry *registry,
                       uint32_t id,
                       const char *interface,
                       uint32_t version);

  static void OnGlobalRemove(void *data,
                             struct wl_registry *registry,
                             uint32_t name);

  static void OnPing(void *data,
                     struct zxdg_shell_v6 *zxdg_shell_v6,
                     uint32_t serial);

  static const struct wl_display_listener kDisplayListener;

  static const struct wl_registry_listener kRegistryListener;

  static const struct wl_shm_listener kShmListener;

  static const struct zxdg_shell_v6_listener kXdgShellListener;

};

}

#endif // SKLAND_GUI_INTERNAL_DISPLAY_PRIVATE_HPP_
