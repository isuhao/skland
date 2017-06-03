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

#include "surface_shell_private.hpp"

#include "surface_private.hpp"
#include <skland/gui/abstract-shell-view.hpp>

namespace skland {

const struct zxdg_surface_v6_listener Surface::Shell::Private::kListener = {
    OnConfigure
};

void Surface::Shell::Private::OnConfigure(void *data,
                                          struct zxdg_surface_v6 *zxdg_surface_v6,
                                          uint32_t serial) {
  Shell *_this = static_cast<Shell *>(data);
  AbstractShellView *shell_view = dynamic_cast<AbstractShellView *>(_this->surface_->p_->event_handler);
  if (shell_view)
    shell_view->OnXdgSurfaceConfigure(serial);
}

}
