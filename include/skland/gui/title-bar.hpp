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

#ifndef SKLAND_GUI_TITLE_BAR_HPP_
#define SKLAND_GUI_TITLE_BAR_HPP_

#include "abstract-button.hpp"

#include "skland/core/color.hpp"
#include "skland/graphic/font.hpp"

namespace skland {
namespace gui {

/**
 * @ingroup gui
 * @brief The default title bar on the top of window
 */
class TitleBar final : public AbstractView {

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(TitleBar);

  enum ButtonType {
    kButtonClose,
    kButtonMaximize,
    kButtonMinimize,
    kButtonFullscreen,
    kButtonMenu
  };

  /**
   * @brief Default constructor
   */
  TitleBar();

  /**
   * @brief Set the title text
   * @param title
   */
  void SetTitle(const std::string &title);

  /**
   * @brief Get a window action button
   * @param button_type
   * @return
   */
  AbstractButton *GetButton(ButtonType button_type) const;

  /**
   * @brief The height of this title bar
   *
   * This value is the height when placed on top or width when placed on left/right side.
   */
  static const int kHeight = 22;

 protected:

  /**
   * @brief Destructor
   */
  virtual ~TitleBar();

  void OnConfigureGeometry(const RectF &old_geometry,
                           const RectF &new_geometry) override;

  void OnSaveGeometry(const RectF &old_geometry,
                      const RectF &new_geometry) override;

  void OnMouseEnter(MouseEvent *event) override;

  void OnMouseLeave() override;

  void OnMouseMove(MouseEvent *event) override;

  void OnMouseDown(MouseEvent *event) override;

  void OnMouseUp(MouseEvent *event) override;

  void OnKeyDown(KeyEvent *event) override;

  void OnKeyUp(KeyEvent *event) override;

  void OnDraw(const Context &context) override;

 private:

  class Button;
  class CloseButton;
  class MaximizeButton;
  class MinimizeButton;
  class FullscreenButton;

  static const int kButtonSpace = 5;

  CloseButton *close_button_;
  MaximizeButton *maximize_button_;
  MinimizeButton *minimize_button_;
  FullscreenButton *fullscreen_button_;

  graphic::Font font_;

  std::string title_;
};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_TITLE_BAR_HPP_
