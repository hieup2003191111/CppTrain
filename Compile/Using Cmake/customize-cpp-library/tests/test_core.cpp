#include <gtest/gtest.h>
#include "my_library/core.h"

using my_library::Core;

class CoreTest : public ::testing::Test {
protected:
    Core core;

    void SetUp() override {
        core.initialize();
    }

    void TearDown() override {
        core.shutdown();
    }
};

TEST_F(CoreTest, ExecuteFunction) {
    EXPECT_NO_THROW(core.execute());
}