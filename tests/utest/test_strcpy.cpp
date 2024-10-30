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


// TEST(FtStrcpyTest, NullPtr) {
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wnonnull"
//     testing::FLAGS_gtest_death_test_style = "threadsafe";
//
//     char *null_ptr = NULL;
//     char *null_ptr2 = NULL;
//     EXPECT_DEATH({ (void)strcpy(null_ptr, null_ptr2); }, ".*");
//     EXPECT_DEATH({ (void)ft_strcpy(null_ptr, null_ptr2); }, ".*");
//
//     EXPECT_DEATH({ (void)strcpy(null_ptr, "a"); }, ".*");
//     EXPECT_DEATH({ (void)ft_strcpy(null_ptr, "a"); }, ".*");
//
//     char *dst = (char *)malloc(sizeof(char) * 10);
//     EXPECT_DEATH({ (void)strcpy(dst, null_ptr); }, ".*");
//     EXPECT_DEATH({ (void)ft_strcpy(dst, null_ptr); }, ".*");
//     free(dst);
//
// #pragma GCC diagnostic pop
// }
