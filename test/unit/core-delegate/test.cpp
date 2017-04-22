//
// Created by zhanggyb on 16-9-19.
//

#include "test.hpp"

#include <skland/core/delegate.hpp>

#include "SkColor.h"

using namespace skland;

class Mockup {

 public:

  Mockup() : count_(0) {}

  ~Mockup() {}

  int Foo(int param) {
    count_ = param;
    return count_;
  }

  int ConstFoo(int param) const {
    return count_;
  }

  int count() const { return count_; }

 private:

  int count_;

};

Test::Test()
    : testing::Test() {
}

Test::~Test() {

}

TEST_F(Test, constructor1) {
  Mockup obj;
  Delegate<int(int)> d(&obj, &Mockup::Foo);
  ASSERT_TRUE(1 == d(1));
}

TEST_F(Test, constructor2) {
  Mockup obj;
  Delegate<int(int)> d = Delegate<int(int)>::FromMethod(&obj, &Mockup::Foo);
  ASSERT_TRUE(1 == d(1));
}

TEST_F(Test, constructor3) {
  Mockup obj;
  Delegate<int(int)> d(&obj, &Mockup::ConstFoo);
  ASSERT_TRUE(0 == d(1));
}

TEST_F(Test, constructor4) {
  Mockup obj;
  Delegate<int(int)> d = Delegate<int(int)>::FromMethod(&obj, &Mockup::ConstFoo);
  ASSERT_TRUE(0 == d(1));
}

/*
 *
 */
TEST_F(Test, compare1) {
  Mockup obj;
  Delegate<int(int)> d = Delegate<int(int)>::FromMethod(&obj, &Mockup::Foo);
  // const not equal to non-const
  ASSERT_TRUE(d.Equal(&obj, &Mockup::Foo));
}

TEST_F(Test, compare2) {
  Mockup obj;
  Delegate<int(int)> d = Delegate<int(int)>::FromMethod(&obj, &Mockup::Foo);
  // const not equal to non-const
  ASSERT_TRUE(!d.Equal(&obj, &Mockup::ConstFoo));
}

TEST_F(Test, compare3) {
  Mockup obj1;
  Delegate<int(int)> d1 = Delegate<int(int)>::FromMethod(&obj1, &Mockup::Foo);
  Delegate<int(int)> d2 = Delegate<int(int)>::FromMethod(&obj1, &Mockup::Foo);
  ASSERT_TRUE(d1 == d2);
}

TEST_F(Test, compare4) {
  Mockup obj1;
  Delegate<int(int)> d1 = Delegate<int(int)>::FromMethod(&obj1, &Mockup::ConstFoo);
  Delegate<int(int)> d2 = Delegate<int(int)>::FromMethod(&obj1, &Mockup::Foo);
  ASSERT_TRUE(d1 != d2);
}

TEST_F(Test, delegate_ref_1) {
  Mockup obj;

  Delegate<int(int)> d1(&obj, &Mockup::Foo);
  Delegate<int(int)> d2(&obj, &Mockup::ConstFoo);

  DelegateRef<int(int)> r1(d1);
  DelegateRef<int(int)> r2(d2);

  r1.Set(&obj, &Mockup::Foo);
  r2.Set(&obj, &Mockup::ConstFoo);

  ASSERT_TRUE(r1 && r2);

  bool result1 = r1.IsAssignedTo(&obj, &Mockup::Foo);
  bool result2 = r2.IsAssignedTo(&obj, &Mockup::ConstFoo);

  ASSERT_TRUE(result1 && result2);

  r1.Reset();
  r2.Reset();

  ASSERT_TRUE((!r1) && (!r2));
}
