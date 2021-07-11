#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

#include "hook.h"

template<> Sample<overflow_hook>* Sample<overflow_hook>::m_sample = nullptr;
template<> size_t                 Sample<overflow_hook>::m_max_size = 3;

using namespace std;

ostream& operator<<(ostream& out, const Stub& s) {
    s.print(out);
    return out;
}

TEST(SingletonTest, none) {
    EXPECT_EQ(nullptr, Sample<overflow_hook>::m_sample);
}

TEST(SingletonTest, get) {
    auto actual = Sample<overflow_hook>::getInstance();
    EXPECT_NE(nullptr,                         actual);
    EXPECT_EQ(Sample<overflow_hook>::m_sample, actual);
}

TEST(SingletonTest, same) {
    auto s0 = Sample<overflow_hook>::getInstance();
    auto s1 = Sample<overflow_hook>::getInstance();
    EXPECT_EQ(s0, s1);
}

TEST(SingletonTest, destroy) {
    auto actual = Sample<overflow_hook>::getInstance();
    ASSERT_NE(nullptr,                         actual);
    ASSERT_EQ(Sample<overflow_hook>::m_sample, actual);

    Sample<overflow_hook>::destroy();
    EXPECT_EQ(nullptr, Sample<overflow_hook>::m_sample);

    ASSERT_NE(nullptr, Sample<overflow_hook>::getInstance());
}
