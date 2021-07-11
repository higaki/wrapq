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

class EmptyTest: public ::testing::Test {
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

TEST_F(EmptyTest, empty) {
    EXPECT_TRUE(target->empty());
}

TEST_F(EmptyTest, once) {
    Stub s(1);
    target->push(&s);

    EXPECT_FALSE(target->empty());
}

TEST_F(EmptyTest, twice) {
    Stub s(1), t(2);
    target->push(&s)->push(&t);

    EXPECT_FALSE(target->empty());
}
