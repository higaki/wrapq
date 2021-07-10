#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

#include "stub.h"

using namespace std;

class SizeTest: public ::testing::Test {
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

TEST_F(SizeTest, empty) {
    EXPECT_EQ(0, target->size());
}

TEST_F(SizeTest, once) {
    Stub s;
    target->push(&s);

    EXPECT_EQ(1, target->size());
}

TEST_F(SizeTest, twice) {
    Stub s, t;
    target->push(&s)->push(&t);

    EXPECT_EQ(2, target->size());
}
