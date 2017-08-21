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

#include "skland/gui/gl-view.hpp"

#include "skland/core/assert.hpp"
#include "skland/core/property.hpp"
#include "skland/core/memory.hpp"

#include "skland/gui/surface.hpp"
#include "skland/gui/mouse-event.hpp"
#include "skland/gui/key-event.hpp"
#include "skland/gui/context.hpp"
#include "skland/gui/abstract-rendering-api.hpp"
#include "skland/gui/region.hpp"
#include "skland/gui/callback.hpp"

namespace skland {
namespace gui {

struct GLView::Private : public core::Property<GLView> {

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Private);

  explicit Private(GLView *owner)
      : core::Property<GLView>(owner) {}

  ~Private() final = default;

  Surface *gl_surface = nullptr;

  AbstractRenderingAPI *rendering_api = nullptr;

  Callback callback;

  void OnFrame(uint32_t serial);

};

void GLView::Private::OnFrame(uint32_t serial) {
  callback.Setup(*gl_surface);
  owner()->OnRender();
  gl_surface->Commit();
}

// ------

GLView::GLView() {
  p_ = core::make_unique<Private>(this);

  p_->callback.done().Set(p_.get(), &GLView::Private::OnFrame);
}

GLView::~GLView() {
  // Note: delete interface_ before destroying gl_surface:
  delete p_->rendering_api;
  delete p_->gl_surface;
}

void GLView::SetRenderingAPI(AbstractRenderingAPI *api) {
  if (p_->rendering_api == api) return;

  p_->rendering_api = api;

  if (nullptr != p_->gl_surface) {
    p_->gl_surface->SetRenderingAPI(p_->rendering_api);
  }
}

void GLView::OnConfigureGeometry(const RectF &old_geometry, const RectF &new_geometry) {
  if (!RequestSaveGeometry(new_geometry)) return;

  if ((nullptr != p_->gl_surface) && (nullptr != p_->rendering_api)) {
    p_->rendering_api->SetViewportSize((int) new_geometry.width(), (int) new_geometry.height());
    OnResize((int) new_geometry.width(), (int) new_geometry.height());
  }
}

void GLView::OnSaveGeometry(const RectF &old_geometry, const RectF &new_geometry) {
  Update();
}

void GLView::OnMouseEnter(MouseEvent *event) {
  event->Accept();
}

void GLView::OnMouseLeave() {

}

void GLView::OnMouseMove(MouseEvent *event) {
  event->Accept();
}

void GLView::OnMouseDown(MouseEvent *event) {
  event->Accept();
}

void GLView::OnMouseUp(MouseEvent *event) {
  event->Accept();
}

void GLView::OnKeyDown(KeyEvent *event) {
  event->Accept();
}

void GLView::OnKeyUp(KeyEvent *event) {
  event->Accept();
}

void GLView::OnDraw(const Context &context) {
  if (nullptr == p_->rendering_api) return;

  if (nullptr == p_->gl_surface) {
    p_->gl_surface = Surface::Sub::Create(context.surface(), this);
    p_->gl_surface->SetRenderingAPI(p_->rendering_api);
//    gl_surface->SetCommitMode(Surface::kDesynchronized);

    Region region;
    p_->gl_surface->SetInputRegion(region);

    p_->rendering_api->SetViewportSize(GetWidth(), GetHeight());
    Surface::Sub::Get(p_->gl_surface)->SetWindowPosition(GetX(), GetY());

    p_->callback.Setup(*p_->gl_surface);
    OnInitialize();
    p_->gl_surface->Commit();
  }
}

void GLView::OnRenderSurface(Surface *surface) {

}

void GLView::SwapBuffers() {
  if (nullptr != p_->rendering_api) p_->rendering_api->SwapBuffers();
}

void GLView::MakeCurrent() {
  if (nullptr != p_->rendering_api) p_->rendering_api->MakeCurrent();
}

} // namespace gui
} // namespace skland
