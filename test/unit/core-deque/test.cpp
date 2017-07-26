//
// Created by zhanggyb on 16-9-19.
//

#include "test.hpp"

#include <skland/core/deque.hpp>

using namespace skland;
using namespace skland::core;

class Item : public Deque::Element {

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(Item);

  explicit Item(int id)
      : id_(id) {}

  virtual ~Item() = default;

  int id() const { return id_; };

  Deque::Element *_previous() const {
    return previous();
  }

  Deque::Element *_next() const {
    return next();
  }

 private:

  int id_;

};

class TestDeque : public Deque {

 public:

  SKLAND_DECLARE_NONCOPYABLE_AND_NONMOVALE(TestDeque);

  TestDeque() = default;

  virtual ~TestDeque() = default;

  const Deque::Element *_first() const {
    return first();
  }

  const Deque::Element *_last() const {
    return last();
  }

};

Test::Test()
    : testing::Test() {
}

Test::~Test() {

}

TEST_F(Test, push_front_1) {
  auto item1 = new Item(1);
  auto item2 = new Item(2);
  auto item3 = new Item(3);

  TestDeque deque;
  deque.PushFront(item1);
  deque.PushFront(item2);
  deque.PushFront(item3);

  ASSERT_TRUE(deque.GetSize() == 3);

  Deque::ConstIterator it = deque.crbegin();
  ASSERT_TRUE(it == item1);

  it = deque.cend();
  ASSERT_TRUE(it != item1);

  ASSERT_TRUE(item1->_next() == deque._last());
  ASSERT_TRUE(item1->_previous() == item2);
  ASSERT_TRUE(item2->_previous() == item3);
  ASSERT_TRUE(item3->_previous() == deque._first());

  delete item1;
  delete item2;
  delete item3;

  ASSERT_TRUE(deque.IsEmpty());
}

TEST_F(Test, push_back_1) {
  auto item1 = new Item(1);
  auto item2 = new Item(2);
  auto item3 = new Item(3);

  TestDeque deque;
  deque.PushBack(item1);
  deque.PushBack(item2);
  deque.PushBack(item3);

  ASSERT_TRUE(item1->_previous() == deque._first());
  ASSERT_TRUE(item1->_next() == item2);
  ASSERT_TRUE(item2->_next() == item3);
  ASSERT_TRUE(item3->_next() == deque._last());

  delete item1;
  delete item2;
  delete item3;

  ASSERT_TRUE(deque.IsEmpty());
}

TEST_F(Test, insert_1) {
  auto item1 = new Item(1);
  auto item2 = new Item(2);
  auto item3 = new Item(3);

  TestDeque deque;
  deque.Insert(item1);
  deque.Insert(item2);
  deque.Insert(item3);

  ASSERT_TRUE(item1->_next() == deque._last());
  ASSERT_TRUE(item1->_previous() == item2);
  ASSERT_TRUE(item2->_previous() == item3);
  ASSERT_TRUE(item3->_previous() == deque._first());

  delete item1;
  delete item2;
  delete item3;

  ASSERT_TRUE(deque.IsEmpty());
}

TEST_F(Test, insert_2) {
  auto item1 = new Item(1);
  auto item2 = new Item(2);
  auto item3 = new Item(3);

  TestDeque deque;
  deque.Insert(item1);
  deque.Insert(item2);
  deque.Insert(item3);

  auto item4 = new Item(4);
  deque.Insert(item4);

  ASSERT_TRUE(item1->_previous() == item2);
  ASSERT_TRUE(item2->_previous() == item3);
  ASSERT_TRUE(item3->_previous() == item4);
  ASSERT_TRUE(item4->_previous() == deque._first());
}

TEST_F(Test, insert_3) {
  auto item1 = new Item(1);
  auto item2 = new Item(2);
  auto item3 = new Item(3);

  TestDeque deque;
  deque.Insert(item1);
  deque.Insert(item2);
  deque.Insert(item3);

  auto item4 = new Item(4);
  deque.Insert(item4, -1);

  ASSERT_TRUE(item1->_previous() == item2);
  ASSERT_TRUE(item2->_previous() == item3);
  ASSERT_TRUE(item3->_previous() == deque._first());
  ASSERT_TRUE(item1->_next() == item4);
  ASSERT_TRUE(item4->_next() == deque._last());

  delete item1;
  delete item2;
  delete item3;
  delete item4;

  ASSERT_TRUE(deque.IsEmpty());
}

TEST_F(Test, get_1) {
  auto item1 = new Item(1);
  auto item2 = new Item(2);
  auto item3 = new Item(3);

  TestDeque deque;
  deque.Insert(item3);
  deque.Insert(item2);
  deque.Insert(item1);

  Deque::Element* item = deque[0];
  ASSERT_TRUE(item = item1);

  item = deque[-1];
  ASSERT_TRUE(item = item3);

  delete item1;
  delete item2;
  delete item3;

  ASSERT_TRUE(deque.IsEmpty());
}

TEST_F(Test, iterator_1) {
  auto item1 = new Item(1);
  auto item2 = new Item(2);
  auto item3 = new Item(3);

  TestDeque deque;
  deque.Insert(item3);
  deque.Insert(item2);
  deque.Insert(item1);

  TestDeque::Iterator it = deque.begin();

  ASSERT_TRUE(it.element() == item1);
  ++it;
  ASSERT_TRUE(it.element() == item2);
  ++it;
  ASSERT_TRUE(it.element() == item3);
  ++it;
  ASSERT_TRUE(it == deque.end());

  it = deque.rbegin();
  ASSERT_TRUE(it.element() == item3);
  --it;
  ASSERT_TRUE(it.element() == item2);
  --it;
  ASSERT_TRUE(it.element() == item1);
  --it;
  ASSERT_TRUE(it == deque.rend());

  delete item1;
  delete item2;
  delete item3;

  ASSERT_TRUE(deque.IsEmpty());
}
