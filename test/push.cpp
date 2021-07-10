#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

#include "stub.h"

using namespace std;

class PushTest: public ::testing::Test {
protected:
    Sample* target;

    virtual void SetUp() {
	target = Sample::getInstance();
    }

    virtual void TearDown() {
	Sample::destroy();
	target = nullptr;
    }
};

TEST_F(PushTest, once) {
    Stub s;
    EXPECT_EQ(target, target->push(&s));
    EXPECT_EQ(1,      target->size());
}

TEST_F(PushTest, twice) {
    Stub s, t;
    EXPECT_EQ(target, target->push(&s)->push(&t));
    EXPECT_EQ(2,      target->size());
}

TEST_F(PushTest, thrice) {
    Stub s, t, u;
    EXPECT_EQ(target, target->push(&s)->push(&t)->push(&u));
    EXPECT_EQ(3,      target->size());
}

TEST_F(PushTest, over) {
    Stub s, t, u, v;
    EXPECT_EQ(target, target->push(&s)->push(&t)->push(&u)->push(&v));
    EXPECT_EQ(3,      target->size());
    EXPECT_EQ(&t,     target->pop());
    EXPECT_EQ(&u,     target->pop());
    EXPECT_EQ(&v,     target->pop());
}

TEST_F(PushTest, same) {
    Stub s, t, u;
    EXPECT_EQ(target, target->push(&s)->push(&t));
    EXPECT_EQ(2,      target->size());
    EXPECT_EQ(target, target->push(&t)->push(&s));
    EXPECT_EQ(2,      target->size()) << "already push";
    EXPECT_EQ(target, target->push(&u)->push(&s));
    EXPECT_EQ(3,      target->size()) << "push u";
    EXPECT_EQ(&s,     target->pop());
    EXPECT_EQ(&t,     target->pop());
    EXPECT_EQ(&u,     target->pop());
}
