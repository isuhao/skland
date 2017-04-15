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

#ifndef SKLAND_GUI_ABSTRACT_SHELL_VIEW_HPP_
#define SKLAND_GUI_ABSTRACT_SHELL_VIEW_HPP_

#include "abstract-event-handler.hpp"

#include "../core/rect.hpp"
#include "../core/margin.hpp"

#include <cstdint>
#include <string>

namespace skland {

class Context;

/**
 * @ingroup gui
 * @brief Abstract class to hold and manage a shell surface
 */
SKLAND_EXPORT class AbstractShellView : public AbstractEventHandler {

  friend class AbstractView;
  friend class AbstractShellFrame;

  AbstractShellView() = delete;
  AbstractShellView(const AbstractShellView &) = delete;
  AbstractShellView &operator=(const AbstractShellView &) = delete;

 public:

  class Iterator;
  class ConstIterator;

  struct RedrawTask;

  /**
   * @brief Enumeration values to indicate where the mouse
   * cursor/title view/client view is located
   *
   * TODO: use a diagram
   */
  enum Location {
    kInterior = 0,
    kResizeTop = 1,
    kResizeBottom = 2,
    kResizeLeft = 4,
    kResizeTopLeft = 5,
    kResizeBottomLeft = 6,
    kResizeRight = 8,
    kResizeTopRight = 9,
    kResizeBottomRight = 10,
    kResizeMask = 15,
    kExterior = 16,
    kTitleBar = 17,
    kClientArea = 18
  };

  /**
   * @brief Constructor
   * @param title A string of window title
   * @param parent Parent shell view
   * @param frame The frame used to show the background and title bar
   */
  AbstractShellView(const char *title,
                    AbstractShellView *parent = nullptr);

  /**
   * @brief Constructor
   * @param width Width of this shell view
   * @param height Height of this shell view
   * @param title A string of window title
   * @param parent Parent shell view
   * @param frame The frame used to show the background and title bar
   */
  AbstractShellView(int width,
                    int height,
                    const char *title,
                    AbstractShellView *parent = nullptr);

  /**
   * @brief Destructor
   *
   * This destructor will destroy the content view attached and the shell frame.
   */
  virtual ~AbstractShellView();

  /**
   * @brief Set the title of this shell view
   * @param title A string of the window title
   */
  void SetTitle(const char *title);

  /**
   * @brief Set the App ID
   * @param app_id
   */
  void SetAppId(const char *app_id);

  void Show();

  void Close(__SLOT__);

  void Minimize(__SLOT__);

  void ToggleMaximize(__SLOT__);

  void ToggleFullscreen(__SLOT__);

  const std::string &GetTitle() const;

  virtual Size GetMinimalSize() const;

  virtual Size GetPreferredSize() const;

  virtual Size GetMaximalSize() const;

  bool IsFullscreen() const;

  bool IsMaximized() const;

  bool IsMinimized() const;

  bool IsFocused() const;

  bool IsResizing() const;

  bool IsShown() const;

  int GetWidth() const;

  int GetHeight() const;

  static const Margin kResizingMargin;

 protected:

  /**
 * @brief Attach a given view to this shell view
 * @param view
 */
  void AttachView(AbstractView *view);

  /**
   * @brief Detach the view from this shell view
   * @param view
   */
  void DetachView(AbstractView *view);

  virtual void OnShown() = 0;

  virtual void OnSizeChange(const Size &old_size, const Size &new_size) = 0;

  virtual void OnMouseEnter(MouseEvent *event) override;

  virtual void OnMouseLeave() override;

  virtual void OnMouseMove(MouseEvent *event) override;

  virtual void OnMouseButton(MouseEvent *event) override;

  virtual void OnKeyboardKey(KeyEvent *event) override;

  virtual void OnUpdate(AbstractView *view) override;

  virtual Surface *GetSurface(const AbstractView *view) const override;

  virtual void OnEnterOutput(const Output *output) override;

  virtual void OnLeaveOutput(const Output *output) override;

  virtual void OnDraw(const Context *context);

  virtual void OnMaximized(bool);

  virtual void OnFullscreen(bool);

  virtual void OnFocus(bool);

  virtual void OnViewAttached(AbstractView *view);

  virtual void OnViewDetached(AbstractView *view);

  void MoveWithMouse(MouseEvent *event) const;

  void ResizeWithMouse(MouseEvent *event, uint32_t edges) const;

  Surface *GetShellSurface() const;

  void DispatchMouseEnterEvent(AbstractView *view, MouseEvent *event);

  void DispatchMouseLeaveEvent();

  void DispatchMouseButtonEvent(MouseEvent *event);

  void DropShadow(const Context *context);

  /**
   * @brief Mark damage area of the given object
   *
   * 'Damange an area in the surface' is a wayland concept.
   */
  static void Damage(AbstractShellView *shell_view, int surface_x, int surface_y, int width, int height);

  /**
   * @brief Mark damage area of the given object
   *
   * 'Damange an area in the surface' is a wayland concept.
   */
  static void Damage(AbstractView *view, int surface_x, int surface_y, int width, int height);

  static void RecursiveUpdate(AbstractView *view);

 private:

  struct Private;

  void OnXdgSurfaceConfigure(uint32_t serial);

  void OnXdgToplevelConfigure(int width, int height, int states);

  void OnXdgToplevelClose();

  void DispatchMouseEnterEvent(AbstractView *parent, MouseEvent *event, MouseTaskIterator &tail);

  /**
   * @brief The private data
   */
  std::unique_ptr<Private> p_;

};

}

#endif // SKLAND_GUI_ABSTRACT_SHELL_VIEW_HPP_
