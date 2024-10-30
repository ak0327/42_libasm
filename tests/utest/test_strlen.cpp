#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <gtest/gtest.h>

extern "C" {
    #include "libasm.h"
}


TEST(FtStrlen, BasicTest) {
    EXPECT_EQ(ft_strlen("hello"), strlen("hello"));
    EXPECT_EQ(ft_strlen("a")    , strlen("a"));
    EXPECT_EQ(ft_strlen("")     , strlen(""));
    EXPECT_EQ(ft_strlen("\0")   , strlen("\0"));
    EXPECT_EQ(ft_strlen("\t")   , strlen("\t"));
    EXPECT_EQ(ft_strlen("12345"), strlen("12345"));
}


TEST(FtStrlen, MidSize) {
    const size_t MID_SIZE = 1024;
    char *mid_str = (char *)malloc(sizeof(char) * (MID_SIZE + 1));
    ASSERT_NE(mid_str, nullptr) << "Memory allocation failed";

    memset(mid_str, 'a', MID_SIZE);
    mid_str[MID_SIZE] = '\0';

    EXPECT_EQ(ft_strlen(mid_str), strlen(mid_str));
    free(mid_str);
}


TEST(FtStrlen, LargeSize) {
    const size_t LARGE_SIZE = 1024 * 1024;
    char *large_str = (char *)malloc(sizeof(char) * (LARGE_SIZE + 1));
    ASSERT_NE(large_str, nullptr) << "Memory allocation failed";

    memset(large_str, 'a', LARGE_SIZE);
    large_str[LARGE_SIZE] = '\0';

    EXPECT_EQ(ft_strlen(large_str), strlen(large_str));
    free(large_str);
}


// TEST(FtStrlen, BigSize) {
// #ifdef SIZE_MAX
//     const size_t VERY_LARGE_SIZE = INT_MAX / 2;
//
//     char *very_large_str = (char *)malloc(sizeof(char) * (VERY_LARGE_SIZE + 1));
//     ASSERT_NE(very_large_str, nullptr) << "Memory allocation failed";
//
//     memset(very_large_str, 'a', VERY_LARGE_SIZE);
//     very_large_str[VERY_LARGE_SIZE] = '\0';
//
//     size_t ft_len = ft_strlen(very_large_str);
//     size_t std_len = strlen(very_large_str);
//     EXPECT_EQ(ft_len, std_len);
//
//     free(very_large_str);
// #endif
// }


// TEST(FtStrlen, Unterminated) {
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wnonnull"
// #pragma GCC diagnostic ignored "-Wunused-variable"
//
//     char unterminated[] = {'a', 'b', 'c'};
//     // char *unterminated = NULL;
//
//     bool str_success = false;
//     bool ft_success = false;
//     size_t str_len = 0;
//     size_t ft_len = 0;
//
//     {
//         testing::FLAGS_gtest_death_test_style = "threadsafe";
//         EXPECT_EXIT({
//             str_len = strlen(unterminated);
//             str_success = true;
//             exit(0);
//         }, testing::KilledBySignal(SIGSEGV), "");
//     }
//
//     {
//         testing::FLAGS_gtest_death_test_style = "threadsafe";
//         EXPECT_EXIT({
//             ft_len = ft_strlen(unterminated);
//             ft_success = true;
//             exit(0);
//         }, testing::KilledBySignal(SIGSEGV), "");
//     }
//
//     if (str_success && ft_success) {
//         EXPECT_EQ(str_len, ft_len);
//     }
//
// #pragma GCC diagnostic pop
// }
