#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

using namespace std;

TEST(SingletonTest, none) {
    EXPECT_EQ(nullptr, Sample::m_sample);
}

TEST(SingletonTest, get) {
    auto actual = Sample::getInstance();
    EXPECT_NE(nullptr,          actual);
    EXPECT_EQ(Sample::m_sample, actual);
}

TEST(SingletonTest, same) {
    auto s0 = Sample::getInstance();
    auto s1 = Sample::getInstance();
    EXPECT_EQ(s0, s1);
}

TEST(SingletonTest, destroy) {
    auto actual = Sample::getInstance();
    ASSERT_NE(nullptr,          actual);
    ASSERT_EQ(Sample::m_sample, actual);

    Sample::destroy();
    EXPECT_EQ(nullptr, Sample::m_sample);

    ASSERT_NE(nullptr, Sample::getInstance());
}
