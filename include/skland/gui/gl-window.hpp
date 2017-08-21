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

#ifndef SKLAND_GUI_EGL_WINDOW_HPP_
#define SKLAND_GUI_EGL_WINDOW_HPP_

#include "abstract-shell-view.hpp"

namespace skland {

namespace graphic {
class Canvas;
}

namespace gui {

class Surface;

/**
 * @ingroup gui
 * @brief A window renders content with different graphic interfaces
 *
 * @example simple-egl.cpp
 */
class GLWindow : public AbstractShellView {

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(GLWindow);

  explicit GLWindow(const char *title);

  GLWindow(int width, int height, const char *title);

  virtual ~GLWindow();

 protected:

  void OnShown() final;

  void OnConfigureSize(const Size &old_size, const Size &new_size) final;

  void OnSaveSize(const Size &old_size, const Size &new_size) final;

  void OnRenderSurface(Surface *surface) final;

  void OnMouseMove(MouseEvent *event) override;

  void OnMouseDown(MouseEvent *event) override;

  void OnMouseUp(MouseEvent *event) override;

  void OnKeyDown(KeyEvent *event) override;

  void OnFocus(bool);

  virtual void OnInitialize();

  virtual void OnResize(int width, int height);

  virtual void OnRender();

  bool MakeCurrent();

  void SwapBuffers();

 private:

  struct Private;

  std::unique_ptr<Private> p_;

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_EGL_WINDOW_HPP_
