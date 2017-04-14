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

#ifndef SKLAND_CORE_TRACE_HPP_
#define SKLAND_CORE_TRACE_HPP_

#include <string>

#ifdef TRACE

#define TRACE(fmt, args...) \
  do { \
    Trace trace(__PRETTY_FUNCTION__, fmt, args); \
  } while(0)

#else // NOT TRACE

#define TRACE(fmt, args...) ((void)0)

#endif  // TRACE

namespace skland {

class Trace {

  Trace(const Trace &) = delete;
  Trace &operator=(const Trace &) = delete;

 public:

  Trace() {
    ++kDepth;
  }

  Trace(const char *func_name, const char *format, ...);

  ~Trace();

  void Log(const char *func_name, const char *format, ...);

  static void SetFileName(const std::string &filename);

 private:

  void LogMessage(int depth, int align, const char *format, va_list args);

  static std::string kFileName;

  static const int kBufferSize = 256;

  static int kDepth;

  static const char *kNestString;

  static time_t kLastTime;

};

}

#endif // SKLAND_CORE_TRACE_HPP_
