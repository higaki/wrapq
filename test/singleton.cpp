#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

#include "hook.h"

typedef Sample<Stub*, overflow_hook> SAMPLE;

template<> SAMPLE* SAMPLE::m_sample   = nullptr;
template<> size_t  SAMPLE::m_max_size = 3;

using namespace std;

ostream& operator<<(ostream& out, const Stub& s) {
    s.print(out);
    return out;
}

class SingletonTest: public ::testing::Test {
protected:
    virtual void SetUp() {
	SAMPLE::destroy();
    }
};

TEST_F(SingletonTest, none) {
    EXPECT_EQ(nullptr, SAMPLE::m_sample);
}

TEST_F(SingletonTest, get) {
    auto actual = SAMPLE::getInstance();
    EXPECT_NE(nullptr,          actual);
    EXPECT_EQ(SAMPLE::m_sample, actual);
}

TEST_F(SingletonTest, same) {
    auto s0 = SAMPLE::getInstance();
    auto s1 = SAMPLE::getInstance();
    EXPECT_EQ(s0, s1);
}

TEST_F(SingletonTest, destroy) {
    auto actual = SAMPLE::getInstance();
    ASSERT_NE(nullptr,          actual);
    ASSERT_EQ(SAMPLE::m_sample, actual);

    SAMPLE::destroy();
    EXPECT_EQ(nullptr, SAMPLE::m_sample);

    ASSERT_NE(nullptr, SAMPLE::getInstance());
}
