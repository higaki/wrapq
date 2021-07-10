#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

#include "stub.h"

using namespace std;

class EmptyTest: public ::testing::Test {
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

TEST_F(EmptyTest, empty) {
    EXPECT_TRUE(target->empty());
}

TEST_F(EmptyTest, once) {
    Stub s;
    target->push(&s);

    EXPECT_FALSE(target->empty());
}

TEST_F(EmptyTest, twice) {
    Stub s, t;
    target->push(&s)->push(&t);

    EXPECT_FALSE(target->empty());
}
