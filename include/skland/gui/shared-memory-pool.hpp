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

#ifndef SKLAND_GUI_SHARED_MEMORY_POOL_HPP_
#define SKLAND_GUI_SHARED_MEMORY_POOL_HPP_

#include <wayland-client.h>
#include <sys/types.h>

namespace skland {

/**
 * @brief Shared memory pool
 */
class SharedMemoryPool {

  friend class Buffer;

  SharedMemoryPool &operator=(const SharedMemoryPool &) = delete;
  SharedMemoryPool(const SharedMemoryPool &) = delete;

 public:

  SharedMemoryPool()
      : wl_shm_pool_(nullptr), size_(0), data_(nullptr) {}

  /**
   * @brief Destructor
   *
   * Destroy the pool, this does not unmap the memory though.
   */
  ~SharedMemoryPool() {
    if (wl_shm_pool_)
      wl_shm_pool_destroy(wl_shm_pool_);
  }

  void Setup(int32_t size);

  void Destroy();

  int32_t size() const {
    return size_;
  }

  void *data() const { return data_; };

 private:

  static int CreateAnonymousFile(off_t size);

  static int CreateTempFile(char *tmpname);

  struct wl_shm_pool* wl_shm_pool_;

  int32_t size_;

  void *data_;

};

}

#endif // SKLAND_GUI_SHARED_MEMORY_POOL_HPP_
