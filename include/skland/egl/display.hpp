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

#ifndef SKLAND_EGL_DISPLAY_HPP_
#define SKLAND_EGL_DISPLAY_HPP_

#include <EGL/egl.h>

namespace skland {

namespace wayland {
class Display;
}

namespace egl {

class Display {

  Display(const Display &) = delete;
  Display &operator=(const Display &) = delete;

 public:

  Display()
      : egl_display_(nullptr),
        egl_context_(nullptr),
        egl_config_(nullptr),
        major_(0),
        minor_(0) {}

  ~Display() {
    if (egl_display_) {
      eglTerminate(egl_display_);
      eglReleaseThread();
    }
  }

  void Setup(const wayland::Display &wl_display);

  void Destroy();

  EGLint major() const {
    return major_;
  }

  EGLint minor() const {
    return minor_;
  }

 private:

  static EGLDisplay GetEGLDisplay(EGLenum platform, void *native_display, const EGLint *attrib_list);

  static void *GetEGLProcAddress(const char *address);

  static bool CheckEGLExtension(const char *extensions, const char *extension);

  EGLDisplay egl_display_;
  EGLContext egl_context_;
  EGLConfig egl_config_;

  EGLint major_;  /**< The major version */
  EGLint minor_;  /**< The minor version */

};

}
}

#endif // SKLAND_EGL_DISPLAY_HPP_
