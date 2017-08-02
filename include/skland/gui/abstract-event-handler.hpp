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

#ifndef SKLAND_GUI_ABSTRACT_EVENT_HANDLER_HPP_
#define SKLAND_GUI_ABSTRACT_EVENT_HANDLER_HPP_

#include "skland/core/sigcxx.hpp"

#include "task.hpp"
#include <memory>

namespace skland {
namespace gui {

class MouseEvent;
class KeyEvent;

class Surface;
class AbstractView;
class Output;

/**
 * @ingroup gui
 * @brief The base class to handle events and interact with surface
 *
 * AbstractEventHandler is the base class for most classes in GUI
 * module, it handles input events from input manager and interact with
 * the surface it hold.
 *
 * There're 2 important sub class:
 * 
 * - AbstractShellView: this is the base class for windows/menus/popups, 
 *   which have own shell surface.
 * - AbstractView: this is the base class for views layouted and show in
 *   a shell view.
 *
 * @see Input
 * @see Surface
 */
SKLAND_EXPORT class AbstractEventHandler : public core::Trackable {

  friend class Input;
  friend class Display;
  friend class Surface;

  friend class AbstractView;
  friend class AbstractShellView;

 public:

  SKLAND_DECLARE_NONCOPYABLE(AbstractEventHandler);

  class EventTask : public Task {

   public:

    SKLAND_DECLARE_NONCOPYABLE(EventTask);
    EventTask() = delete;

    /**
     * @brief Constructor
     * @param event_handler An AbstractEventHandler object
     *
     * @note The parameter cannot be nullptr.
     */
    EventTask(AbstractEventHandler *event_handler)
        : Task(), event_handler_(event_handler) {}

    /**
     * @brief Destructor
     */
    virtual ~EventTask() {}

    AbstractEventHandler *event_handler() const { return event_handler_; }

    EventTask *GetPrevious() const {
      return static_cast<EventTask *>(core::BiNode::previous());
    }

    EventTask *GetNext() const {
      return static_cast<EventTask *>(core::BiNode::next());
    }

    static EventTask *GetMouseTask(const AbstractEventHandler *event_hander);

    static EventTask *GetMouseMotionTask(const AbstractEventHandler *event_handler);

   private:

    /**
     * @brief A pointer to an AbstractEventHandler object
     */
    AbstractEventHandler *event_handler_;

  };

  /**
   * @brief Default constructor
   */
  AbstractEventHandler();

  /**
   * @brief Destructor
   */
  virtual ~AbstractEventHandler();

 protected:

  /**
   * @brief Virtual callback when mouse device enter this object
   */
  virtual void OnMouseEnter(MouseEvent *event) = 0;

  /**
   * @brief Virtual callback when mouse device leave this object
   */
  virtual void OnMouseLeave() = 0;

  /**
   * @brief Virtual callback when mouse moving on this object
   */
  virtual void OnMouseMove(MouseEvent *event) = 0;

  /**
   * @brief Virtual callback when mouse button pressed on this object
   */
  virtual void OnMouseDown(MouseEvent *event) = 0;

  /**
   * @brief Virtual callback when mouse button released on this object
   * @param event
   */
  virtual void OnMouseUp(MouseEvent *event) = 0;

  /**
   * @brief Virtual callback when a keyboard key is prssed down on this object
   */
  virtual void OnKeyDown(KeyEvent *event) = 0;

  /**
   * @brief Virtual callback when a keyboard key is released on this object
   * @param event
   */
  virtual void OnKeyUp(KeyEvent *event) = 0;

  virtual void OnRequestSaveGeometry(AbstractView *view) = 0;

  /**
   * @brief A view request an update
   * @param view A view in hierarchy wants to update this object
   */
  virtual void OnRequestUpdate(AbstractView *view) = 0;

  /**
   * @brief Get surface for the given view
   * @param view A view in hierarchy or null to get shell surface for this object
   * @return A pointer to a surface or nullptr
   */
  virtual Surface *GetSurface(const AbstractView *view) const = 0;

  virtual void OnRenderSurface(Surface *surface) = 0;

  virtual void OnEnterOutput(const Surface *surface, const Output *output) = 0;

  virtual void OnLeaveOutput(const Surface *surface, const Output *output) = 0;

  /**
   * @brief Disable this virtual method
   * @param token
   */
  virtual void AuditDestroyingToken(core::details::Token */*token*/) final;

 private:

  struct Private;

  std::unique_ptr<Private> p_;

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_ABSTRACT_EVENT_HANDLER_HPP_
