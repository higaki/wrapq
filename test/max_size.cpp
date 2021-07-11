#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

#include "hook.h"

using namespace std;

TEST(MaxSizeTest, max_size) {
    EXPECT_EQ(
	Sample<overflow_hook>::m_max_size,
	Sample<overflow_hook>::getInstance()->max_size());
}
