#include <stdlib.h>
#include <string.h>
#include <gtest/gtest.h>

extern "C" char* ft_strcpy(char* dst, const char* src);

class FtStrcpyTest: public ::testing::TestWithParam<const char *> {
 protected:
    std::size_t len = 10;
    char *dst_expected = nullptr;
    char *dst_actual = nullptr;

    void SetUp() override {
        dst_expected = (char *)malloc(sizeof(char) * len);
        dst_actual = (char *)malloc(sizeof(char) * len);

        memset(dst_expected, 'a', len - 1);
        memset(dst_actual, 'a', len - 1);

        dst_expected[len - 1] = '\0';
        dst_actual[len - 1] = '\0';
    }

    void TearDown() override {
        free(dst_expected);
        free(dst_actual);
    }
};

TEST_P(FtStrcpyTest, BasicTest) {
    const char* src = GetParam();

    dst_expected = strcpy(dst_expected, src);
    dst_actual = ft_strcpy(dst_actual, src);

    EXPECT_STREQ(dst_expected, dst_actual);
}

INSTANTIATE_TEST_SUITE_P(
        DifferentSrcCases,
        FtStrcpyTest,
        ::testing::Values(
                "",
                " ",
                "\t",
                "\n",
                "a",
                "abc",
                "123",
                "123\0abc",
                "longer_test_case")
);
