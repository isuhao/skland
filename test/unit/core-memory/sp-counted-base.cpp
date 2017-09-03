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

#include "sp-counted-base.hpp"

#include "skland/core/memory.hpp"

#include "SkRefCnt.h"

using namespace skland;
using namespace skland::core;

SPCountedBaseTest::SPCountedBaseTest()
    : testing::Test() {
}

SPCountedBaseTest::~SPCountedBaseTest() {

}

/**
 * @brief Make sure have the same memory size
 */
TEST_F(SPCountedBaseTest, memory_size_1) {
  SkRefCntBase sk_base;
  SPCountedBase base;

  std::cout << sizeof(std::atomic_ulong) << std::endl;
  std::cout << sizeof(size_t) << std::endl;

  ASSERT_TRUE(sizeof(sk_base) == sizeof(base));
}
