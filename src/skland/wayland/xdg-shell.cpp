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

#include <skland/wayland/xdg-shell.hpp>

#include "internal/xdg-shell-private.hpp"

namespace skland {
namespace wayland {

const struct wl_interface *XdgShell::GetInterface() {
  return &zxdg_shell_v6_interface;
}

XdgShell::XdgShell() {
  p_.reset(new Private);
}

XdgShell::~XdgShell() {
}

void XdgShell::Setup(const Registry &registry, uint32_t id, uint32_t version) {
  Destroy();

  p_->zxdg_shell =
      static_cast<struct zxdg_shell_v6 *>(registry.Bind(id, &zxdg_shell_v6_interface, version));
  zxdg_shell_v6_add_listener(p_->zxdg_shell, &XdgShell::Private::kListener, this);
}

void XdgShell::Destroy() {
  if (p_->zxdg_shell) {
    zxdg_shell_v6_destroy(p_->zxdg_shell);
    p_->zxdg_shell = nullptr;
  }
}

void XdgShell::Pong(uint32_t serial) const {
  zxdg_shell_v6_pong(p_->zxdg_shell, serial);
}

void XdgShell::SetUserData(void *user_data) {
  zxdg_shell_v6_set_user_data(p_->zxdg_shell, user_data);
}

void *XdgShell::GetUserData() const {
  return zxdg_shell_v6_get_user_data(p_->zxdg_shell);
}

uint32_t XdgShell::GetVersion() const {
  return zxdg_shell_v6_get_version(p_->zxdg_shell);
}

bool XdgShell::IsValid() const {
  return nullptr != p_->zxdg_shell;
}

bool XdgShell::Equal(const void *object) const {
  return p_->zxdg_shell == object;
}

}
}

