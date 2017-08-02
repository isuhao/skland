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

#ifndef SKLAND_GUI_SURFACE_HPP_
#define SKLAND_GUI_SURFACE_HPP_

#include "skland/core/sigcxx.hpp"
#include "skland/core/margin.hpp"
#include "skland/core/point.hpp"

#include "skland/gui/abstract-view.hpp"

#include "task.hpp"

#include <wayland-egl.h>
#include <memory>

namespace skland {
namespace gui {

class Buffer;
class Output;
class InputEvent;
class Region;
class AbstractGraphicsInterface;

/**
 * @ingroup gui
 * @brief Surface for views
 *
 * Surface represents a native wayland surface to display views.
 *
 * A surface can have parent or arbitrary sub surfaces and acts as different
 * roles.
 *
 * According to wayland protocol, a surface without a parent must be a shell
 * surface, a shell surface is created and managed in a AbstractShellView
 * object to display window, popup menu or tooltip etc.
 *
 * A surface which has a parent is called a sub surface, it's usually used in
 * special widgets (e.g. video widget, or EGL widget) as such widgets need their
 * own surface to display something.
 *
 * Each shell surface or sub surface can also be a EGL surface to display 3D
 * scene, otherwise, it displays 2D contents through wayland shared memory
 * buffer.
 *
 * All surfaces in an SkLand application are stacked by the order defined in
 * wayland protocol. [TODO: use an image to show the surface stack.]
 *
 * This class has several nested classes to identify and control the surface
 * role. You cannot create or delete a surface object directly. Instead, you
 * need to use the nested class. For example:
 *
 *   - Create a toplevel shell surface with Surface::Shell::Toplevel::Create()
 *   - Create a sub surface with Surface::Sub::Create()
 *
 * You can also use Surface::EGL::Get() to transform a 2D surface to 3D surface,
 * and delete the Surface::EGL object will transform back to 2D.
 */
class Surface {

  using Point = core::PointI;
  using Margin = core::Margin;

  friend class Application;
  friend class Display;
  friend class Callback;
  friend class AbstractGraphicsInterface;

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Surface);
  Surface() = delete;

  class Shell;
  class Sub;
  class EGL;

  enum Transform {
    kTransformNormal = 0, // WL_OUTPUT_TRANSFORM_NORMAL
    kTransform90 = 1, // WL_OUTPUT_TRANSFORM_90
    kTransform180 = 2,  // WL_OUTPUT_TRANSFORM_180
    kTransform270 = 3,  // WL_OUTPUT_TRANSFORM_270
    kTransformFlipped = 4,  // WL_OUTPUT_TRANSFORM_FLIPPED
    kTransformFlipped90 = 5,  // WL_OUTPUT_TRANSFORM_FLIPPED_90
    kTransformFlipped180 = 6, // WL_OUTPUT_TRANSFORM_FLIPPED_180
    kTransformFlipped270 = 7  // WL_OUTPUT_TRANSFORM_FLIPPED_270
  };

  /**
    * @brief Commit behaviour of the sub-surface
    */
  enum CommitMode {
    kSynchronized,
    kDesynchronized
  };

  virtual ~Surface();

  static int GetShellSurfaceCount() { return kShellSurfaceCount; }

  /**
   * @brief Attach a shared memory buffer
   */
  void Attach(Buffer *buffer, int32_t x = 0, int32_t y = 0);

  /**
   * @brief Add this surface in the commit task list
   *
   * This method add this surface in the commit task list and will
   * commit the native wayland surface in the event loop.
   *
   * If this surface is a sub surface and commit behaviour is
   * synchronized, this method will commit the shell surface (main
   * surface) too.
   */
  void Commit();

  /**
   * @brief Mark the damaged region of the surface
   */
  void Damage(int surface_x, int surface_y, int width, int height);

  void SetInputRegion(const Region &region);

  void SetOpaqueRegion(const Region &region);

  void SetTransform(Transform transform);

  Transform GetTransform() const;

  void SetScale(int32_t scale);

  int32_t GetScale() const;

  void DamageBuffer(int32_t x, int32_t y, int32_t width, int32_t height);

  void Update(bool validate = true);

  /**
   * @brief Get defferred redraw task deque
   * @return
   */
  core::Deque<AbstractView::RedrawTask> &GetRedrawTaskDeque() const;

  Surface *GetShellSurface();

  /**
   * @brief Get the position in window coordinates
   * @return Global position
   */
  Point GetWindowPosition() const;

  /**
   * @brief Get the parent surface
   * @return
   */
  Surface *GetParent() const;

  /**
   * @brief The sibling surface above this one
   * @return
   */
  Surface *GetSiblingAbove() const;

  /**
   * @brief The sibling surface below this one
   * @return
   */
  Surface *GetSiblingBelow() const;

  /**
   * @brief The shell surface placed over this one
   * @return
   */
  Surface *GetUpperShell() const;

  /**
   * @brief The shell surface placed under this one
   * @return
   */
  Surface *GetLowerShell() const;

  AbstractEventHandler *GetEventHandler() const;

  AbstractGraphicsInterface *GetGraphicsInterface() const;

  const Margin &GetMargin() const;

  const Point &GetRelativePosition() const;

 private:

  class RenderTask : public Task {

   public:

    SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(RenderTask);
    RenderTask() = delete;

    explicit RenderTask(Surface *surface)
        : surface_(surface) {}

    virtual ~RenderTask() = default;

    void Run() const final;

   private:

    Surface *surface_;

  };

  class CommitTask : public Task {

   public:

    SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(CommitTask);
    CommitTask() = delete;

    explicit CommitTask(Surface *surface)
        : Task(), surface_(surface) {}

    virtual ~CommitTask() = default;

    void Run() const final;

   private:

    Surface *surface_;

  };

  struct Private;

  explicit Surface(AbstractEventHandler *event_handler, const Margin &margin = Margin());

  // global surface stack:

  /**
   * @brief Delete all shell surfaces and clear the global stack
   */
  static void Clear();

  /**
   * @brief The top shell surface in the stack
   */
  static Surface *kTop;

  /**
   * @brief The bottom shell surface in the stack
   */
  static Surface *kBottom;

  /**
   * @brief The count of shell surface
   */
  static int kShellSurfaceCount;

  static core::Deque<RenderTask> kRenderTaskDeque;

  static core::Deque<CommitTask> kCommitTaskDeque;

  std::unique_ptr<Private> p_;

};

/**
 * @brief Shell surface role
 */
class Surface::Shell {

  friend class Surface;

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Shell);
  Shell() = delete;

  class Toplevel;
  class Popup;

  static Shell *Get(const Surface *surface);

  void ResizeWindow(int width, int height) const;

  void AckConfigure(uint32_t serial) const;

  Surface *surface() const { return surface_; }

 private:

  struct Private;

  static Surface *Create(AbstractEventHandler *event_handler,
                         const Margin &margin = Margin());

  explicit Shell(Surface *surface);

  ~Shell();

  void Push();

  void Remove();

  std::unique_ptr<Private> p_;

  Surface *surface_;

  Shell *parent_;

  union {
    void *placeholder;
    Toplevel *toplevel;
    Popup *popup;
  } role_;

};

/**
 * @brief Toplevel shell surface role
 */
class Surface::Shell::Toplevel {

  friend class Shell;

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Toplevel);
  Toplevel() = delete;

  enum StatesMask {
    kStateMaskMaximized = 0x1, /**< 1: the surface is maximized */
    kStateMaskFullscreen = 0x1 << 1,      /**< 2: the surface is fullscreen */
    kStateMaskResizing = 0x1 << 2, /**< 4: the surface is being resized */
    kStateMaskActivated = 0x1 << 3, /**< 8: the surface is now activated */
  };

  /**
   * @brief Create a toplevel shell surface
   */
  static Surface *Create(AbstractEventHandler *event_handler,
                         const Margin &margin = Margin());

  static Toplevel *Get(const Surface *surface);

  void SetTitle(const char *title) const;

  void SetAppId(const char *id) const;

  void Move(const InputEvent &input_event, uint32_t serial) const;

  void Resize(const InputEvent &input_event, uint32_t serial, uint32_t edges) const;

  void SetMaximized() const;

  void UnsetMaximized() const;

  void SetFullscreen(const Output *output) const;

  void UnsetFullscreen() const;

  void SetMinimized() const;

 private:

  struct Private;

  explicit Toplevel(Shell *shell_surface);

  ~Toplevel();

  std::unique_ptr<Private> p_;

};

/**
 * @brief Popup shell surface role
 */
class Surface::Shell::Popup {

  friend class Shell;

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Popup);
  Popup() = delete;

  /**
   * @brief Create a popup shell surface
   */
  static Surface *Create(Shell *parent,
                         AbstractEventHandler *view,
                         const Margin &margin = Margin());

 private:

  struct Private;

  explicit Popup(Shell *shell);

  ~Popup();

  std::unique_ptr<Private> p_;

};

/**
 * @brief Sub surface role
 */
class Surface::Sub {

  friend class Surface;

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Sub);
  Sub() = delete;

  /**
   * @brief Create a sub surface
   */
  static Surface *Create(Surface *parent,
                         AbstractEventHandler *event_handler,
                         const Margin &margin = Margin());

  static Sub *Get(const Surface *surface);

  void PlaceAbove(Surface *sibling);

  void PlaceBelow(Surface *sibling);

  void SetRelativePosition(int x, int y);

  void SetWindowPosition(int x, int y);

  Surface *surface() const { return surface_; }

 private:

  Sub(Surface *surface, Surface *parent);

  ~Sub();

  void SetParent(Surface *parent);

  /**
 * @brief Move the local surface list and insert above target dst surface
 * @param dst
 */
  void MoveAbove(Surface *dst);

  /**
   * @brief Move the local surface list and insert below target dst surface
   * @param dst
   */
  void MoveBelow(Surface *dst);

  void InsertAbove(Surface *sibling);

  void InsertBelow(Surface *sibling);

  Surface *surface_;

  struct wl_subsurface *wl_sub_surface_;

};

/**
 * @brief EGL surface role
 */
class Surface::EGL {

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(EGL);
  EGL() = delete;

  enum Profile {
    kProfileOpenGLES2,  // OpenGL ES 2
    kProfileOpenGLES3,  // OpenGL ES 3
    kProfileOpenGL1_4,  // OpenGL 1.4
    kProfileOpenGL2_1,  // OpenGL 2.1
    kProfileOpenGL3_3,  // OpenGL 3.3
    kProfileOpenGL4_4,  // OpenGL 4.4
    kProfileVulkan      // Vulkan
  };

  /**
   * @brief Get the EGL surface
   * @param[in] surface The surface object
   * @param[in] create
   *            - true: create and turn the surface role to 3D surface
   *            - false: just get the existing EGL surface, return null if not exists
   *
   * If the surface is not an EGL surface, this method will create one and
   * change the surface behavior. Delete the EGL object returned by this
   * method will turn this surface back to 2D.
   */
  static EGL *Get(Surface *surface, Profile profile = kProfileOpenGLES2, bool create = true);

  virtual ~EGL();

  bool MakeCurrent();

  bool SwapBuffers();

  bool SwapBuffersWithDamage(int x, int y, int width, int height);

  bool SwapInterval(int interval = 0);

  void Resize(int width, int height, int dx = 0, int dy = 0);

  Surface *GetSurface() const;

 private:

  struct Private;

  explicit EGL(Surface *surface);

  std::unique_ptr<Private> p_;

};

} // namespace gui
} // namespace skland

#endif // SKLAND_GUI_VIEW_SURFACE_HPP_
