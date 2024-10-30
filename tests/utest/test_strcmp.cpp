#include <iostream>
#include <string.h>
#include <gtest/gtest.h>

extern "C" int ft_strcmp(const char *s1, const char *s2);

class FtStrcmpTest : public ::testing::TestWithParam<std::pair<const char*, const char*>> {
};

TEST_P(FtStrcmpTest, BasicTest) {
    auto [s1, s2] = GetParam();
    EXPECT_EQ(ft_strcmp(s1, s2), strcmp(s1, s2)) << " Failed at s1:[" << s1 << "], s2:[" << s2 <<"]";
}

INSTANTIATE_TEST_SUITE_P(
        DifferentStringPairs,
        FtStrcmpTest,
        ::testing::Values(
                std::make_pair("a"      , "a"),
                std::make_pair("a"      , "b"),
                std::make_pair(""       , ""),
                std::make_pair("\0"     , "\0"),
                std::make_pair("a"      , ""),
                std::make_pair(""       , "a"),
                std::make_pair(""       , "~"),
                std::make_pair("~"      , ""),
                std::make_pair("\r"     , "a"),
                std::make_pair("\n"     , ""),
                std::make_pair("abc"    , "abcd"),
                std::make_pair("abcd"   , "abc"),
                std::make_pair("abc"    , "ABC"),
                std::make_pair("ABC"    , "abc"),
                std::make_pair("123"    , "123"),
                std::make_pair("hello"  , "hello"),
                std::make_pair("hello"  , "world"),
                std::make_pair("HELLO"  , "hello"),
                std::make_pair("longer string"  , "longer"),
                std::make_pair("hello\0world"   , "hello"),
                std::make_pair("hello"          , "hello\0world"),
                std::make_pair("hello "         , "hello"),
                std::make_pair("!@#$%^&*"       , "!@#$%^&*"),
                std::make_pair("long\0string"   , "long\0test"),
                std::make_pair("test\n"         , "test"),
                std::make_pair("😀", "😀"),
                std::make_pair("😀", "😃")
        )
);


// TEST(FtStrcmp, NullPtr) {
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wnonnull"
//     testing::FLAGS_gtest_death_test_style = "threadsafe";
//
//     char *null_ptr = NULL;
//     EXPECT_DEATH({ (void)strcmp(null_ptr, null_ptr); }, ".*");
//     EXPECT_DEATH({ (void)ft_strcmp(null_ptr, null_ptr); }, ".*");
//
//     EXPECT_DEATH({ (void)strcmp(null_ptr, "a"); }, ".*");
//     EXPECT_DEATH({ (void)ft_strcmp(null_ptr, "a"); }, ".*");
//
//     EXPECT_DEATH({ (void)strcmp("a", null_ptr); }, ".*");
//     EXPECT_DEATH({ (void)ft_strcmp("a", null_ptr); }, ".*");
//
// #pragma GCC diagnostic pop
// }
