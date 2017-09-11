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

#include "skland/gui/window.hpp"

#include "skland/core/defines.hpp"
#include "skland/core/memory.hpp"
#include "skland/core/property.hpp"

#include "skland/gui/application.hpp"
#include "skland/gui/mouse-event.hpp"
#include "skland/gui/key-event.hpp"
#include "skland/gui/title-bar.hpp"

#include "skland/gui/shared-memory-pool.hpp"
#include "skland/gui/buffer.hpp"
#include "skland/gui/region.hpp"
#include "skland/gui/output.hpp"

#include "skland/gui/theme.hpp"

#include "skland/graphic/canvas.hpp"
#include "skland/graphic/paint.hpp"
#include "skland/graphic/path.hpp"
#include "skland/graphic/gradient-shader.hpp"

namespace skland {
namespace gui {

using core::PointF;
using core::RectF;
using core::RectI;
using core::Margin;
using core::CompoundDeque;

using graphic::Canvas;
using graphic::Paint;
using graphic::Path;
using graphic::Shader;
using graphic::GradientShader;
using graphic::ClipOperation;

/**
 * @ingroup gui_intern
 * @brief The private structure for Window
 */
struct Window::Private : public core::Property<Window> {

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Private);

  explicit Private(Window *owner)
      : core::Property<Window>(owner),
        minimal_size(160, 120),
        preferred_size(640, 480),
        maximal_size(65536, 65536) {}

  ~Private() final = default;

  SharedMemoryPool pool;

  Buffer buffer;

  /** The default title bar */
  TitleBar *title_bar = nullptr;

  AbstractView *content_view = nullptr;

  Size minimal_size;

  Size preferred_size;

  Size maximal_size;

  const Output *output = nullptr;

  bool redraw_all = true;

  bool clear = false;

  bool inhibit_update = true;

  void DrawInner(const Context &context);

  void DrawOutline(const Context &context);

  void DrawShadow(const Context &context);

  void RecursiveDraw(AbstractView *view, const Context &context);

  void SetContentViewGeometry();

  static std::vector<float> kOutlineRadii;

};

std::vector<float> Window::Private::kOutlineRadii = {
    7.f, 7.f, // top-left
    7.f, 7.f, // top-right
    4.f, 4.f, // bottom-right
    4.f, 4.f  // bottom-left
};

void Window::Private::DrawInner(const Context &context) {
  int scale = context.surface()->GetScale();
  int pixel_width = owner()->GetWidth() * scale;
  int pixel_height = owner()->GetHeight() * scale;
  RectF geometry = RectF::MakeFromXYWH(0.f, 0.f, pixel_width, pixel_height);
  std::vector<float> radii = {
      kOutlineRadii[0] * scale, kOutlineRadii[1] * scale, // top-left
      kOutlineRadii[2] * scale, kOutlineRadii[3] * scale, // top-right
      kOutlineRadii[4] * scale, kOutlineRadii[5] * scale, // bottom-right
      kOutlineRadii[6] * scale, kOutlineRadii[7] * scale  // bottom-left
  };
  Path path;
  if (owner()->IsMaximized() || owner()->IsFullscreen()) {
    path.AddRect(geometry);
  } else {
    path.AddRoundRect(geometry, radii.data());
  }

  const Theme::Schema &window_schema = Theme::GetData().window;

  // Fill color:
  Paint paint;
  paint.SetAntiAlias(true);
  paint.SetColor(window_schema.active.background.colors[0]);

  Canvas::LockGuard guard(context.canvas(), path, ClipOperation::kClipIntersect, true);
  context.canvas()->DrawPath(path, paint);
}

void Window::Private::DrawOutline(const Context &context) {
  if (owner()->IsMaximized() || owner()->IsFullscreen()) return;

  int scale = context.surface()->GetScale();
  int pixel_width = owner()->GetWidth() * scale;
  int pixel_height = owner()->GetHeight() * scale;
  RectF geometry = RectF::MakeFromXYWH(0.5f, 0.5f, pixel_width - 1.f, pixel_height - 1.f);
  std::vector<float> radii = {
      kOutlineRadii[0] * scale, kOutlineRadii[1] * scale, // top-left
      kOutlineRadii[2] * scale, kOutlineRadii[3] * scale, // top-right
      kOutlineRadii[4] * scale, kOutlineRadii[5] * scale, // bottom-right
      kOutlineRadii[6] * scale, kOutlineRadii[7] * scale  // bottom-left
  };
  Path path;
  if (owner()->IsMaximized() || owner()->IsFullscreen()) {
    path.AddRect(geometry);
  } else {
    path.AddRoundRect(geometry, radii.data());
  }

  const Theme::Schema &window_schema = Theme::GetData().window;
  Paint paint;
  paint.SetAntiAlias(true);
  paint.SetColor(window_schema.inactive.outline.colors[0]);
  paint.SetStyle(Paint::Style::kStyleStroke);
  paint.SetStrokeWidth(.2f);

  // FIXME: this function draws a white circle at bottom corners.
  context.canvas()->DrawPath(path, paint);
}

void Window::Private::DrawShadow(const Context &context) {
  if (owner()->IsMaximized() || owner()->IsFullscreen()) return;

  int scale = context.surface()->GetScale();
  int pixel_width = owner()->GetWidth() * scale;
  int pixel_height = owner()->GetHeight() * scale;
  RectF geometry = RectF::MakeFromXYWH(0.f, 0.f, pixel_width, pixel_height);
  std::vector<float> radii = {
      kOutlineRadii[0] * scale, kOutlineRadii[1] * scale, // top-left
      kOutlineRadii[2] * scale, kOutlineRadii[3] * scale, // top-right
      kOutlineRadii[4] * scale, kOutlineRadii[5] * scale, // bottom-right
      kOutlineRadii[6] * scale, kOutlineRadii[7] * scale  // bottom-left
  };
  Path path;
  path.AddRoundRect(geometry, radii.data());

  Canvas::LockGuard guard(context.canvas(), path, ClipOperation::kClipDifference, true);
  context.canvas()->Clear();
  owner()->DropShadow(context);
}

void Window::Private::RecursiveDraw(AbstractView *view, const Context &context) {
  Canvas::LockGuard guard(context.canvas(), view->GetGeometry());

  AbstractView *parent = view->GetParent();
  if (nullptr != parent) {
    RecursiveDraw(parent, context);
  } else {
    context.canvas()->Clear();
    DrawInner(context);
  }

  Draw(view, context);
}

void Window::Private::SetContentViewGeometry() {
  const RectI geometry = owner()->GetContentGeometry();
  content_view->MoveTo(geometry.x(), geometry.y());
  content_view->Resize(geometry.width(), geometry.height());
}

// --------------

Window::Window(const char *title)
    : Window(640, 480, title) {
}

Window::Window(int width, int height, const char *title)
    : AbstractShellView(width, height, title, nullptr) {
  p_ = core::MakeUnique<Private>(this);

  // Create the default title bar:
  auto *titlebar = new TitleBar;
  p_->title_bar = titlebar;
  AttachView(p_->title_bar);

  titlebar->SetTitle(title);
  titlebar->Resize(GetWidth(), TitleBar::kHeight);

  AbstractButton *button = titlebar->GetButton(TitleBar::kButtonClose);
  button->clicked().Connect(this, static_cast<void (Window::*)(core::SLOT)>(&AbstractShellView::Close));

  button = titlebar->GetButton(TitleBar::kButtonMaximize);
  button->clicked().Connect(this, static_cast<void (Window::*)(core::SLOT)>(&AbstractShellView::ToggleMaximize));

  button = titlebar->GetButton(TitleBar::kButtonMinimize);
  button->clicked().Connect(this, static_cast<void (Window::*)(core::SLOT)>(&AbstractShellView::Minimize));

  button = titlebar->GetButton(TitleBar::kButtonFullscreen);
  //button->clicked().Connect(this, static_cast<void (Window::*)(SLOT)>(&AbstractShellView::SetFullscreen));
  button->clicked().Connect(this, &Window::OnFullscreenButtonClicked);
}

Window::~Window() {
  if (nullptr != p_->content_view) p_->content_view->Destroy();
  if (nullptr != p_->title_bar) p_->title_bar->Destroy();
}

AbstractView *Window::GetTitleBar() const {
  return p_->title_bar;
}

AbstractView *Window::GetContentView() const {
  return p_->content_view;
}

void Window::SetContentView(AbstractView *view) {
  if (p_->content_view == view) return;

  if (nullptr != p_->content_view) p_->content_view->Destroy();
  // p_->content_view will be set to nullptr in OnViewDetached()

  p_->content_view = view;
  if (nullptr == p_->content_view) return;

  AttachView(p_->content_view);
  p_->SetContentViewGeometry();
}

const core::SizeI &Window::GetMinimalSize() const {
  return p_->minimal_size;
}

const core::SizeI &Window::GetPreferredSize() const {
  return p_->preferred_size;
}

const core::SizeI &Window::GetMaximalSize() const {
  return p_->maximal_size;
}

void Window::OnShown() {
  Surface *shell_surface = GetShellSurface();
  const Margin &margin = shell_surface->GetMargin();

  // Set surface's scale
  int scale = 1;
  if (nullptr == p_->output) {
    const CompoundDeque &outputs = Display::GetOutputs();
    if (outputs.count() > 0) {
      p_->output = static_cast<const Output *>(outputs[0]);
    }
  }
  if (nullptr != p_->output) scale = p_->output->GetScale();
  shell_surface->SetScale(scale);

  // Create buffer:
  int width = GetWidth() * scale;
  int height = GetHeight() * scale;
  width += margin.lr() * scale;
  height += margin.tb() * scale;

  p_->pool.Setup(width * 4 * height);

  p_->buffer.Setup(p_->pool, width, height,
                   width * 4, WL_SHM_FORMAT_ARGB8888);
  shell_surface->Attach(&p_->buffer);
  shell_surface->Update();

  p_->redraw_all = true;
  p_->inhibit_update = false;

  if (nullptr != p_->title_bar) {
    DispatchUpdate(p_->title_bar);
    p_->title_bar->Resize(GetWidth(), TitleBar::kHeight);
  }
  if (nullptr != p_->content_view) {
    DispatchUpdate(p_->content_view);
    p_->SetContentViewGeometry();
  }
}

void Window::OnRequestUpdate(AbstractView *view) {
  if (p_->inhibit_update) return;

  Surface *surface = GetShellSurface();
  surface->GetRedrawNodeDeque().PushBack(AbstractView::RedrawNode::Get(view));
  surface->Update();
}

void Window::OnConfigureSize(const Size &old_size, const Size &new_size) {
  Size size = new_size;

  if (size.width < p_->minimal_size.width) size.width = p_->minimal_size.width;
  if (size.height < p_->minimal_size.height) size.height = p_->minimal_size.height;
  if (size.width > p_->maximal_size.width) size.width = p_->maximal_size.width;
  if (size.height > p_->maximal_size.height) size.height = p_->maximal_size.height;

  if (!RequestSaveSize(size)) return;

  if (nullptr != p_->title_bar) {
    p_->title_bar->Resize(size.width, TitleBar::kHeight);
  }
  if (nullptr != p_->content_view) {
    p_->SetContentViewGeometry();
  }
}

void Window::OnSaveSize(const Size &old_size, const Size &new_size) {
  Surface *shell_surface = this->GetShellSurface();

  int scale = 1;
  const CompoundDeque &outputs = Display::GetOutputs();
  if (outputs.count() > 0) {
    p_->output = static_cast<const Output *>(outputs[0]);
    scale = p_->output->GetScale();
  }
  shell_surface->SetScale(scale);

  int width = new_size.width;
  int height = new_size.height;
  const core::Margin &margin = shell_surface->GetMargin();

  Rect input_rect(width, height);

  input_rect.left = margin.left - kResizingMargin.left;
  input_rect.top = margin.top - kResizingMargin.top;
  input_rect.Resize(width + kResizingMargin.lr(),
                    height + kResizingMargin.tb());

  Region input_region;
  input_region.Add(input_rect.x(), input_rect.y(),
                   input_rect.width(), input_rect.height());
  shell_surface->SetInputRegion(input_region);

  // Reset buffer:
  width *= scale;
  height *= scale;
  width += margin.lr() * scale;
  height += margin.tb() * scale;

  p_->pool.Setup(width * 4 * height);

  p_->buffer.Setup(p_->pool, width, height, width * 4, WL_SHM_FORMAT_ARGB8888);
  shell_surface->Attach(&p_->buffer);
  shell_surface->Update();

  p_->redraw_all = true;

  // surface size is changed, reset the pointer position and enter/leave widgets
  DispatchMouseLeaveEvent();

  if (nullptr != p_->title_bar) {
    DispatchUpdate(p_->title_bar);
//    p_->title_bar->Resize(new_size.width, TitleBar::kHeight);
  }
  if (nullptr != p_->content_view) {
    DispatchUpdate(p_->content_view);
//    p_->SetContentViewGeometry();
  }
}

void Window::OnRenderSurface(Surface *surface) {
  const Margin &margin = surface->GetMargin();

  int scale = surface->GetScale();
  int pixel_width = GetWidth() * scale;
  int pixel_height = GetHeight() * scale;
  RectF geometry = RectF::MakeFromXYWH(0.f, 0.f, pixel_width, pixel_height);

  Canvas canvas((unsigned char *) p_->buffer.GetData(),
                p_->buffer.GetSize().width,
                p_->buffer.GetSize().height);
  canvas.SetOrigin(margin.left, margin.top);
  if (p_->clear) {
    canvas.Clear();
    p_->clear = false;
  }
  Context context(surface, &canvas);

  std::vector<float> radii = {
      Private::kOutlineRadii[0] * scale, Private::kOutlineRadii[1] * scale, // top-left
      Private::kOutlineRadii[2] * scale, Private::kOutlineRadii[3] * scale, // top-right
      Private::kOutlineRadii[4] * scale, Private::kOutlineRadii[5] * scale, // bottom-right
      Private::kOutlineRadii[6] * scale, Private::kOutlineRadii[7] * scale  // bottom-left
  };

  Path path;
  if (!(IsMaximized() || IsFullscreen())) {
    path.AddRoundRect(geometry, radii.data());
  } else {
    path.AddRect(geometry);
  }

  if (p_->redraw_all) {
    p_->redraw_all = false;

    p_->DrawShadow(context);
    p_->DrawInner(context);
    p_->DrawOutline(context);

    core::Deque<AbstractView::RedrawNode> &deque = surface->GetRedrawNodeDeque();
    core::Deque<AbstractView::RedrawNode>::Iterator it = deque.begin();
    AbstractView *view = nullptr;

    Canvas::LockGuard guard(&canvas, path, ClipOperation::kClipIntersect, true);

    while (it != deque.end()) {
      view = it.element()->view();
      it.Remove();
      Draw(view, context);
      it = deque.begin();
    }

    canvas.Flush();

    surface->Damage(0, 0, GetWidth() + margin.lr(), GetHeight() + margin.tb());
    surface->Commit();
  } else {
    core::Deque<AbstractView::RedrawNode> &deque = surface->GetRedrawNodeDeque();
    core::Deque<AbstractView::RedrawNode>::Iterator it = deque.begin();
    AbstractView *view = nullptr;

    Canvas::LockGuard guard(&canvas, path, ClipOperation::kClipIntersect, true);

    while (it != deque.end()) {
      view = it.element()->view();
      it.Remove();
      p_->RecursiveDraw(view, context);
      surface->Damage(view->GetX() + margin.l,
                      view->GetY() + margin.t,
                      view->GetWidth(),
                      view->GetHeight());
      it = deque.begin();
    }

    canvas.Flush();

    surface->Commit();
  }
}

void Window::OnMouseEnter(MouseEvent *event) {
  AbstractView *view = nullptr;
  int location = GetMouseLocation(event);
  switch (location) {
    case kResizeTop: {
      event->SetCursor(Display::GetCursor(kCursorTop));
      break;
    }
    case kResizeBottom: {
      event->SetCursor(Display::GetCursor(kCursorBottom));
      break;
    }
    case kResizeLeft: {
      event->SetCursor(Display::GetCursor(kCursorLeft));
      break;
    }
    case kResizeRight: {
      event->SetCursor(Display::GetCursor(kCursorRight));
      break;
    }
    case kResizeTopLeft: {
      event->SetCursor(Display::GetCursor(kCursorTopLeft));
      break;
    }
    case kResizeTopRight: {
      event->SetCursor(Display::GetCursor(kCursorTopRight));
      break;
    }
    case kResizeBottomLeft: {
      event->SetCursor(Display::GetCursor(kCursorBottomLeft));
      break;
    }
    case kResizeBottomRight: {
      event->SetCursor(Display::GetCursor(kCursorBottomRight));
      break;
    }
    case kTitleBar: {
      view = p_->title_bar;
      break;
    }
    case kClientArea: {
      view = p_->content_view;
      break;
    }
    default: {
      event->SetCursor(Display::GetCursor(kCursorLeftPtr));
      break;
    }
  }

  if (nullptr != view) DispatchMouseEnterEvent(view, event);
}

void Window::OnMouseLeave() {
  DispatchMouseLeaveEvent();
}

void Window::OnMouseMove(MouseEvent *event) {
  AbstractView *view = nullptr;
  switch (GetMouseLocation(event)) {
    case kResizeTop: {
      DispatchMouseLeaveEvent();
      event->SetCursor(Display::GetCursor(kCursorTop));
      break;
    }
    case kResizeBottom: {
      DispatchMouseLeaveEvent();
      event->SetCursor(Display::GetCursor(kCursorBottom));
      break;
    }
    case kResizeLeft: {
      DispatchMouseLeaveEvent();
      event->SetCursor(Display::GetCursor(kCursorLeft));
      break;
    }
    case kResizeRight: {
      DispatchMouseLeaveEvent();
      event->SetCursor(Display::GetCursor(kCursorRight));
      break;
    }
    case kResizeTopLeft: {
      DispatchMouseLeaveEvent();
      event->SetCursor(Display::GetCursor(kCursorTopLeft));
      break;
    }
    case kResizeTopRight: {
      DispatchMouseLeaveEvent();
      event->SetCursor(Display::GetCursor(kCursorTopRight));
      break;
    }
    case kResizeBottomLeft: {
      DispatchMouseLeaveEvent();
      event->SetCursor(Display::GetCursor(kCursorBottomLeft));
      break;
    }
    case kResizeBottomRight: {
      DispatchMouseLeaveEvent();
      event->SetCursor(Display::GetCursor(kCursorBottomRight));
      break;
    }
    case kTitleBar: {
      event->SetCursor(Display::GetCursor(kCursorLeftPtr));
      view = p_->title_bar;
      break;
    }
    case kClientArea: {
      event->SetCursor(Display::GetCursor(kCursorLeftPtr));
      view = p_->content_view;
      break;
    }
    default: {
      event->SetCursor(Display::GetCursor(kCursorLeftPtr));
      break;
    }
  }

  if (nullptr != view) DispatchMouseEnterEvent(view, event);

  // Now dispatch mouse move event:
//      task = static_cast<ViewTask *>(handler->p_->mouse_motion_task.next());
//      p_->mouse_event->response_ = InputEvent::kUnknown;
//      while (task) {
//        task->view->OnMouseMove(p_->mouse_event);
//        if (!p_->mouse_event->IsAccepted()) break;
//        task = static_cast<ViewTask *>(task->next());
//      }
}

void Window::OnMouseDown(MouseEvent *event) {
  if (event->GetButton() == MouseButton::kMouseButtonLeft) {

    int location = GetMouseLocation(event);

    if (location == kTitleBar && (nullptr == EventTask::GetMouseTask(this)->GetNext())) {
      MoveWithMouse(event);
      event->Ignore();
      return;
    }

    if (location < kResizeMask) {
      ResizeWithMouse(event, (uint32_t) location);
      event->Ignore();
      return;
    }
  }

  DispatchMouseDownEvent(event);
}

void Window::OnMouseUp(MouseEvent *event) {
  DispatchMouseUpEvent(event);
}

void Window::OnKeyDown(KeyEvent *event) {
  if (event->key() == kKey_ESC) {
    Application::Exit();
  }
  event->Accept();
}

void Window::OnFocus(bool focus) {
  GetShellSurface()->Update();
  p_->redraw_all = true;
  p_->clear = true;

  if (nullptr != p_->title_bar) {
    DispatchUpdate(p_->title_bar);
  }
  if (nullptr != p_->content_view) {
    DispatchUpdate(p_->content_view);
  }
}

void Window::OnViewAttached(AbstractView */*view*/) {
  // Finalize this virtual method
}

void Window::OnViewDetached(AbstractView *view) {
  if (view == p_->title_bar) {
    p_->title_bar = nullptr;
    return;
  }

  if (view == p_->content_view) {
    p_->content_view = nullptr;
    return;
  }
}

void Window::OnEnterOutput(const Surface *surface, const Output *output) {
  if (p_->output == output) return;

  p_->output = output;
  Surface *shell_surface = GetShellSurface();
  shell_surface->SetScale(output->GetScale());
}

void Window::OnLeaveOutput(const Surface *surface, const Output *output) {
  if (p_->output != output) return;

  p_->output = nullptr;

  int scale = 1;
  const CompoundDeque &outputs = Display::GetOutputs();
  if (outputs.count() > 0) {
    p_->output = static_cast<const Output *>(outputs[0]);
    scale = p_->output->GetScale();
  }

  GetShellSurface()->SetScale(scale);
}

int Window::GetMouseLocation(const MouseEvent *event) const {
  int vlocation, hlocation, location;
  auto x = static_cast<int>(event->GetSurfaceXY().x);
  auto y = static_cast<int>(event->GetSurfaceXY().y);
  const Margin &shadow_margin = Theme::GetShadowMargin();

  // TODO: maximized or fullscreen

  if (x < (shadow_margin.left - kResizingMargin.left))
    hlocation = kExterior;
  else if (x < shadow_margin.left + kResizingMargin.left)
    hlocation = kResizeLeft;
  else if (x < shadow_margin.left + GetWidth() - kResizingMargin.right)
    hlocation = kInterior;
  else if (x < shadow_margin.left + GetWidth() + kResizingMargin.right)
    hlocation = kResizeRight;
  else
    hlocation = kExterior;

  if (y < (shadow_margin.top - kResizingMargin.top))
    vlocation = kExterior;
  else if (y < shadow_margin.top + kResizingMargin.top)
    vlocation = kResizeTop;
  else if (y < shadow_margin.top + GetHeight() - kResizingMargin.bottom)
    vlocation = kInterior;
  else if (y < shadow_margin.top + GetHeight() + kResizingMargin.bottom)
    vlocation = kResizeBottom;
  else
    vlocation = kExterior;

  location = vlocation | hlocation;
  if (location & kExterior)
    location = kExterior;

  if (location == kInterior &&
      y < shadow_margin.top + TitleBar::kHeight)
    location = kTitleBar;
  else if (location == kInterior)
    location = kClientArea;

  return location;
}

RectI Window::GetContentGeometry() const {
  int x = 0;
  int y = 0;
  int w = GetWidth();
  int h = GetHeight();
  if (nullptr != p_->title_bar) {
    y += p_->title_bar->GetHeight();
    h -= p_->title_bar->GetHeight();
  }
  return Rect::MakeFromXYWH(x, y, w, h);
}

void Window::OnFullscreenButtonClicked(core::SLOT slot) {
  if (IsFullscreen()) {
    ToggleFullscreen(nullptr);
  } else {
    if (nullptr != p_->output)
      p_->owner()->ToggleFullscreen(p_->output);
    else {
      const CompoundDeque &outputs = Display::GetOutputs();
      if (outputs.count() > 0) {
        p_->output = static_cast<const Output *>(outputs[0]);
        ToggleFullscreen(p_->output);
      }
    }
  }
}

} // namespace gui
} // namespace skland
