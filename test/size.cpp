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

class SizeTest: public ::testing::Test {
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

TEST_F(SizeTest, empty) {
    EXPECT_EQ(0, target->size());
}

TEST_F(SizeTest, once) {
    Stub s(1);
    target->push(&s);

    EXPECT_EQ(1, target->size());
}

TEST_F(SizeTest, twice) {
    Stub s(1), t(2);
    target->push(&s)->push(&t);

    EXPECT_EQ(2, target->size());
}
