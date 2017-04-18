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

#include "theme-light.hpp"

#include <skland/stock/theme.hpp>

namespace skland {

/**
 * @brief The default light theme
 */
class ThemeLight : public Theme {

 public:

  ThemeLight()
      : Theme() {
    data().window.background.color = 0xEFF0F0F0;
    data().window.background_active.color = 0xEFF0F0F0;
    data().window.foreground.color = 0xEFE0E0E0;
    data().window.foreground_active.color = 0xEFE7E7E7;

    data().title_bar.background.color = 0xEFF0F0F0;

    data().title_bar.background_active.shaded = true;
    data().title_bar.background_active.shaded_count = 2;
    data().title_bar.background_active.shaded_colors.resize(2);
    data().title_bar.background_active.shaded_colors[0] = 0xFFDDDDDD;
    data().title_bar.background_active.shaded_colors[1] = 0xFFCCCCCC;
    data().title_bar.background_active.shaded_positions.resize(2);
    data().title_bar.background_active.shaded_positions[0] = 0.f;
    data().title_bar.background_active.shaded_positions[1] = 1.f;


    data().title_bar.background_highlight.color = data().title_bar.background_active.color + 55;
    data().title_bar.foreground.color = 0xFF444444;
    data().title_bar.foreground_active.color = 0xFF444444;
    data().title_bar.foreground_highlight.color = data().title_bar.foreground_active.color + 55;
  }

  ~ThemeLight() {}

};

}

void *ThemeLightCreate() {
  return new skland::ThemeLight;
}

void ThemeLightDestroy(void *p) {
  skland::ThemeLight *theme = static_cast<skland::ThemeLight *>(p);
  delete theme;
}

