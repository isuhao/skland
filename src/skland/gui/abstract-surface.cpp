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

#include <skland/gui/abstract-surface.hpp>
#include <skland/gui/display.hpp>
#include <skland/gui/buffer.hpp>

#include <skland/graphic/canvas.hpp>

namespace skland {

AbstractSurface::AbstractSurface(AbstractView *view, const Margin &margin)
    : view_(view), margin_(margin),
      buffer_transform_(WL_OUTPUT_TRANSFORM_NORMAL),
      buffer_scale_(1) {
  DBG_ASSERT(view_);
  wl_surface_.enter().Set(this, &AbstractSurface::OnEnter);
  wl_surface_.leave().Set(this, &AbstractSurface::OnLeave);
  wl_surface_.Setup(Display::wl_compositor());
  wl_surface_.SetUserData(this);
}

AbstractSurface::~AbstractSurface() {
  ClearChildren();

  // TODO: check if need to do sth for view_
}

void AbstractSurface::AddSubSurface(AbstractSurface *subsurface, int pos) {
  if ((nullptr == subsurface) || (subsurface->parent() == this)) return;

  InsertChild(subsurface, pos);
}

AbstractSurface *AbstractSurface::GetSubSurfaceAt(int index) const {
  return static_cast<AbstractSurface *>(GetChildAt(index));
}

AbstractSurface *AbstractSurface::RemoveSubSurface(AbstractSurface *subsurface) {
  if (RemoveChild(subsurface))
    return subsurface;

  return nullptr;
}

void AbstractSurface::Attach(Buffer *buffer, int32_t x, int32_t y) {
  if (nullptr == buffer || buffer->wl_buffer().IsNull()) {
    wl_surface_.Attach(NULL, x, y);
  } else {
    buffer->position_.x = x;
    buffer->position_.y = y;
    wl_surface_.Attach(buffer->wl_buffer(), x, y);
  }

  OnAttach(buffer);
}

void AbstractSurface::Commit() const {
  wl_surface_.Commit();
  if (parent()) {
    static_cast<AbstractSurface *>(parent())->Commit();
  }
}

void AbstractSurface::SetCanvas(Canvas *canvas) {
  canvas_.reset(canvas);
}

void AbstractSurface::OnEnter(struct wl_output *wl_output) {

}

void AbstractSurface::OnLeave(struct wl_output *wl_output) {

}

}
