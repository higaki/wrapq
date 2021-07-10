#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

using namespace std;

TEST(MaxSizeTest, max_size) {
    EXPECT_EQ(Sample::m_max_size, Sample::getInstance()->max_size());
}
