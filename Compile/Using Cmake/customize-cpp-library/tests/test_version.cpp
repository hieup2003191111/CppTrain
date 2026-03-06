#include <gtest/gtest.h>
#include "my_library/version.h"

TEST(VersionTest, ReturnsCorrectVersion) {
    std::string version = my_library::getVersion();
    EXPECT_EQ(version, "1.0.0"); // Keep in sync with implementation
}