#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

#include "stub.h"
#include "hook.h"

typedef Sample<Stub*, overflow_hook> SAMPLE;

using namespace std;

class EraseTest: public ::testing::Test {
protected:
    SAMPLE* target;

    virtual void SetUp() {
	target = SAMPLE::getInstance();
    }

    virtual void TearDown() {
	SAMPLE::destroy();
	target = nullptr;
    }
};

TEST_F(EraseTest, empty) {
    ASSERT_TRUE(target->empty());

    Stub s(0);
    EXPECT_EQ(nullptr, target->erase(&s));

    EXPECT_TRUE(target->empty());
}

TEST_F(EraseTest, once) {
    Stub s(0);
    target->push(&s);

    ASSERT_EQ(1, target->size());

    EXPECT_EQ(&s, target->erase(&s));
    EXPECT_TRUE(  target->empty());
}

TEST_F(EraseTest, last) {
    Stub s(0), t(1);
    target->push(&s)->push(&t);

    EXPECT_EQ(&t, target->erase(&t));
    EXPECT_EQ(1,  target->size());
    EXPECT_EQ(&s, target->pop());
}

TEST_F(EraseTest, mid) {
    Stub s(0), t(1), u(2);
    target->push(&s)->push(&u)->push(&t);

    EXPECT_EQ(&u, target->erase(&u));
    EXPECT_EQ(2,  target->size());
    EXPECT_EQ(&s, target->pop());
    EXPECT_EQ(&t, target->pop());
}

TEST_F(EraseTest, not_found) {
    Stub s(0), t(1);
    target->push(&s);

    EXPECT_EQ(nullptr, target->erase(&t));
    EXPECT_EQ(1,       target->size());
    EXPECT_EQ(&s,      target->pop());
}
