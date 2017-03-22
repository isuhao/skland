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

#ifndef SKLAND_CORE_VECTORS_HPP_
#define SKLAND_CORE_VECTORS_HPP_

namespace skland {

namespace core {

/**
 * @ingroup core
 * @brief 2 dimension vector
 * @tparam T
 */
template<typename T>
struct Vector2 {

  inline Vector2()
      : x(T(0)), y(T(0)) {}

  inline Vector2(T x, T y)
      : x(x), y(y) {}

  inline Vector2(const Vector2 &other)
      : x(other.x), y(other.y) {}

  template<typename U>
  inline Vector2(const Vector2<U> &other)
      : x(T(other.x)), y(T(other.y))
  {}

  inline ~Vector2() {}

  inline Vector2 &operator=(const Vector2 &other) {
    x = other.x;
    y = other.y;
    return *this;
  }

  template<typename U>
  inline Vector2 &operator=(const Vector2<U> &other) {
    x = static_cast<T>(other.x);
    y = static_cast<T>(other.y);
    return *this;
  }

  inline Vector2 &operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  inline Vector2 &operator-=(const Vector2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  inline bool Equal(T x, T y) const {
    return this->x == x && this->y == y;
  }

  inline bool IsZero() const {
    return T(0) == x && T(0) == y;
  }

  template<typename U>
  inline Vector2 Dot(const Vector2<U> &other) const {
    return Vector2(x * other.x, y * other.y);
  }

  union { T x, r, s; };
  union { T y, g, t; };
};

/**
 * @ingroup core
 */
template<typename T>
inline bool operator==(const Vector2<T> &v1, const Vector2<T> &v2) {
  return memcmp(&v1, &v2, sizeof(Vector2<T>)) == 0;
}

/**
 * @ingroup core
 */
template<typename T>
inline bool operator!=(const Vector2<T> &v1, const Vector2<T> &v2) {
  return memcmp(&v1, &v2, sizeof(Vector2<T>)) != 0;
}

/**
 * @ingroup core
 */
template<typename T>
inline Vector2<T> operator+(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(v1.x + v2.x, v1.y + v2.y);
}

/**
 * @ingroup core
 */
template<typename T>
inline Vector2<T> operator-(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(v1.x - v2.x, v1.y - v2.y);
}

/**
 * @ingroup core
 * @brief 3 dimension vector
 * @tparam T
 */
template<typename T>
struct Vector3 {

  inline Vector3()
      : x(T(0)), y(T(0)), z(T(0)) {}

  inline Vector3(T x, T y, T z)
      : x(x), y(y), z(z) {}

  inline Vector3(const Vector3 &other)
      : x(other.x), y(other.y), z(other.z) {}

  template<typename U>
  inline Vector3(const Vector3<U> &other)
      : x(T(other.x)), y(T(other.y)), z(T(other.z))
  {}
  
  inline Vector3 &operator=(const Vector3 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  template<typename U>
  inline Vector3 &operator=(const Vector3<U> &other) {
    x = static_cast<T>(other.x);
    y = static_cast<T>(other.y);
    z = static_cast<T>(other.z);
    return *this;
  }
  
  inline ~Vector3() {}

  union { T x, r, s; };
  union { T y, g, t; };
  union { T z, b, p; };
};

/**
 * @ingroup core
 */
template<typename T>
inline bool operator==(const Vector3<T> &vector1, const Vector3<T> &vector2) {
  return memcmp(&vector1, &vector2, sizeof(Vector3<T>)) == 0;
}

/**
 * @ingroup core
 */
template<typename T>
inline bool operator!=(const Vector3<T> &vector1, const Vector3<T> &vector2) {
  return memcmp(&vector1, &vector2, sizeof(Vector3<T>)) != 0;
}

/**
 * @ingroup core
 * @brief 4 dimension vector
 * @tparam T
 */
template<typename T>
struct Vector4 {

  inline Vector4()
      : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}

  inline Vector4(T x, T y, T z, T w)
      : x(x), y(y), z(z), w(w) {}

  inline Vector4(const Vector4 &other)
      : x(other.x), y(other.y), z(other.z), w(other.w) {}

  template<typename U>
  inline Vector4(const Vector4<U> &other)
      : x(T(other.x)), y(T(other.y)), z(T(other.z)), w(T(other.w))
  {}

  inline Vector4 &operator=(const Vector4 &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  template<typename U>
  inline Vector4 &operator=(const Vector4<U> &other) {
    x = static_cast<T>(other.x);
    y = static_cast<T>(other.y);
    z = static_cast<T>(other.z);
    w = static_cast<T>(other.w);
    return *this;
  }

  inline ~Vector4() {}

  union { T x, r, s; };
  union { T y, g, t; };
  union { T z, b, p; };
  union { T w, a, q; };
};

template<typename T>
inline bool operator==(const Vector4<T> &vector1, const Vector4<T> &vector2) {
  return memcmp(&vector1, &vector2, sizeof(Vector4<T>)) == 0;
}

template<typename T>
inline bool operator!=(const Vector4<T> &vector1, const Vector4<T> &vector2) {
  return memcmp(&vector1, &vector2, sizeof(Vector4<T>)) != 0;
}

} // namespace core

} // namespace skland

#endif // SKLAND_CORE_VECTORS_HPP_
