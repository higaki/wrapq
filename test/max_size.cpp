#include <gtest/gtest.h>

#define private   public
#define protected public
#include "../src/sample.h"
#undef  protected
#undef  private

#include "hook.h"

typedef Sample<Stub*, overflow_hook> SAMPLE;

using namespace std;

TEST(MaxSizeTest, max_size) {
    EXPECT_EQ(SAMPLE::m_max_size, SAMPLE::getInstance()->max_size());
}
