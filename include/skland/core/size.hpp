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

#ifndef SKLAND_CORE_SIZE_HPP_
#define SKLAND_CORE_SIZE_HPP_

namespace skland {
namespace core {

/**
 * @ingroup core
 * @brief Template structure for size in 2 dimension
 */
template<typename T>
struct Size {

  inline Size()
      : width(T(0)), height(T(0)) {}

  inline Size(T width, T height)
      : width(width), height(height) {}

  inline Size(const Size &other)
      : width(other.width), height(other.height) {}

  inline Size &operator=(const Size &other) {
    width = other.width;
    height = other.height;
    return *this;
  }

  inline ~Size() {}

  inline bool IsValid() const {
    return width >= 0 && height >= 0;
  }

  inline bool Equal(const Size &other) const {
    return (width == other.width) && (height == other.height);
  }

  inline bool Equal(T width, T height) const {
    return (this->width == width && this->height == height);
  }

  inline void Add(int dw, int dh) const {
    width += dw;
    height += dh;
  }

  inline void Subtract(int dw, int dh) const {
    width -= dw;
    height -= dh;
  }

  union { T w, width; };
  union { T h, height; };
};

/**
 * @ingroup core
 */
template<typename T>
inline bool operator==(const Size<T> &size1, const Size<T> &size2) {
  return ((size1.width == size2.width)
      && (size1.height == size2.height));
}

/**
 * @ingroup core
 */
template<typename T>
inline bool operator!=(const Size<T> &size1, const Size<T> &size2) {
  return ((size1.width != size2.width) ||
      (size1.height != size2.height));
}

/**
 * @ingroup core
 */
template<typename T>
inline Size<T> operator+(const Size<T> &size1, const Size<T> &size2) {
  return Size<T>(size1.width + size2.width, size1.height + size2.height);
}

/**
 * @ingroup core
 */
template<typename T>
inline Size<T> operator-(const Size<T> &size1, const Size<T> &size2) {
  return Size<T>(size1.width - size2.width, size1.height - size2.height);
}

template<typename T>
inline Size<T> operator*(const Size<T> &src, int factor) {
  return Size<T>(src.width * factor, src.height * factor);
}

}  // namespace core

/**
 * @ingroup core
 */
typedef core::Size<int> Size;

/**
 * @ingroup core
 */
typedef core::Size<int> SizeI;

/**
 * @ingroup core
 */
typedef core::Size<float> SizeF;

/**
 * @ingroup core
 */
typedef core::Size<double> SizeD;

}

#endif // SKLAND_CORE_SIZE_HPP_
