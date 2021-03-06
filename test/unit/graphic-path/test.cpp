//
// Created by zhanggyb on 16-9-19.
//

#include "test.hpp"

#include <skland/graphic/path.hpp>
#include "SkPath.h"

using namespace skland::graphic;

Test::Test()
    : testing::Test() {
}

Test::~Test() {

}

TEST_F(Test, enums_check_1) {

  // Direction
  ASSERT_TRUE((int) Path::Direction::kClockwise == (int) SkPath::Direction::kCW_Direction);
  ASSERT_TRUE((int) Path::Direction::kCounterClockwise == (int) SkPath::Direction::kCCW_Direction);

  // FillType
  ASSERT_TRUE((int) Path::FillType::kFillTypeWinding == (int) SkPath::FillType::kWinding_FillType);
  ASSERT_TRUE((int) Path::FillType::kFillTypeEvenOdd == (int) SkPath::FillType::kEvenOdd_FillType);
  ASSERT_TRUE((int) Path::FillType::kFillTypeInverseWinding == (int) SkPath::FillType::kInverseWinding_FillType);
  ASSERT_TRUE((int) Path::FillType::kFillTypeInverseEvenOdd == (int) SkPath::FillType::kInverseEvenOdd_FillType);

  // Convexity
  ASSERT_TRUE((int) Path::Convexity::kConvexityUnknown == (int) SkPath::kUnknown_Convexity);
  ASSERT_TRUE((int) Path::Convexity::kConvexityConvex == (int) SkPath::kConvex_Convexity);
  ASSERT_TRUE((int) Path::Convexity::kConvexityConcave == (int) SkPath::kConcave_Convexity);

}
