#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

#include "stub.h"
#include "hook.h"

using namespace std;

class PopTest: public ::testing::Test {
protected:
    Sample<overflow_hook>* target;

    virtual void SetUp() {
	target = Sample<overflow_hook>::getInstance();
    }

    virtual void TearDown() {
	Sample<overflow_hook>::destroy();
	target = nullptr;
    }
};

TEST_F(PopTest, empty) {
    ASSERT_TRUE(target->empty());
    EXPECT_EQ(nullptr, target->pop());
}

TEST_F(PopTest, once) {
    Stub s(1);
    target->push(&s);
    ASSERT_EQ(1, target->size());

    EXPECT_EQ(&s, target->pop());
    EXPECT_TRUE(  target->empty());
}

TEST_F(PopTest, twice) {
    Stub s(1), t(2);
    target->push(&s)->push(&t);
    ASSERT_EQ(2, target->size());

    EXPECT_EQ(&s, target->pop());
    EXPECT_EQ(1,  target->size());

    EXPECT_EQ(&t, target->pop());
    EXPECT_TRUE(  target->empty());
}
