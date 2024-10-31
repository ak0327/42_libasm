#include <iostream>
#include <string.h>
#include <gtest/gtest.h>

extern "C" char *ft_strdup(const char *s);

class FtStrdupTest : public ::testing::TestWithParam<const char *> {
};

TEST_P(FtStrdupTest, BasicTest) {
    auto s = GetParam();
    EXPECT_STREQ(ft_strdup(s), strdup(s)) << " Failed at s:[" << s << "]";
}

INSTANTIATE_TEST_SUITE_P(
        DifferentStringPairs,
        FtStrdupTest,
        ::testing::Values(
                "a",
                "",
                "\0",
                "~",
                "\r",
                "\n",
                "abc",
                "ABC",
                "123",
                "hello",
                "hello\nworld",
                "hello\0world",
                "😀"
        )
);
