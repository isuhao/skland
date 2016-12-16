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

#ifndef SKLAND_GRAPHIC_FONT_HPP_
#define SKLAND_GRAPHIC_FONT_HPP_

namespace skland {

// Foreward declaration
class Paint;
namespace graphic {
class MetaFont;
}

class Font {

  friend class Paint;

 public:

  enum Weight {
    kWeightInvisible = 0,
    kWeightThin = 100,
    kWeightExtraLight = 200,
    kWeightLight = 300,
    kWeightNormal = 400,
    kWeightMedium = 500,
    kWeightSemiBold = 600,
    kWeightBold = 700,
    kWeightExtraBold = 800,
    kWeightBlack = 900,
    kWeightExtraBlack = 1000,
  };

  enum Width {
    kWidthUltraCondensed = 1,
    kWidthExtraCondensed = 2,
    kWidthCondensed = 3,
    kWidthSemiCondensed = 4,
    kWidthNormal = 5,
    kWidthSemiExpanded = 6,
    kWidthExpanded = 7,
    kWidthExtraExpanded = 8,
    kWidthUltraExpanded = 9,
  };

  enum Slant {
    kSlantUpright,
    kSlantItalic,
    kSlantOblique
  };

  Font(const char *name = "Arial",
       Weight weight = kWeightNormal,
       Width width = kWidthNormal,
       Slant slant = kSlantUpright);

  Font(const Font &other);

  ~Font();

  Font &operator=(const Font &other);

  void LoadName(const char *name,
                Weight weight = kWeightNormal,
                Width width = kWidthNormal,
                Slant slant = kSlantUpright);

  void SetBold(bool bold);

  bool IsBold() const;

  void SetItalic(bool italic);

  bool IsItalic() const;

 private:

  graphic::MetaFont *metadata_;

};

}

#endif // SKLAND_GRAPHIC_FONT_HPP_