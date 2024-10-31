#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <string>
#include <filesystem>

extern "C" ssize_t ft_read(int test_fd, const void *buf, size_t nbyte);

class FtReadTest : public ::testing::Test {
 protected:
    int test_fd;
    std::string tmp_file_path;

    static std::string create_temp_file(const std::string &content) {
        char template_path[] = "/tmp/ft_read_test_XXXXXX";
        int tmp_fd = mkstemp(template_path);
        if (tmp_fd == -1) {
            throw std::runtime_error("Failed to create temp file");
        }
        if (!content.empty()) {
            write(tmp_fd, content.c_str(), content.size());
            lseek(tmp_fd, 0, SEEK_SET);
        }
        close(tmp_fd);
        return std::string(template_path);
    }

    void setup_test_file(const std::string& content) {
        tmp_file_path = create_temp_file(content);
        test_fd = open(tmp_file_path.c_str(), O_RDWR);
        ASSERT_NE(test_fd, -1) << "Failed to open temp file";
    }

    void TearDown() override {
        if (test_fd != -1) {
            close(test_fd);
        }
        if (!tmp_file_path.empty()) {
            std::filesystem::remove(tmp_file_path);
        }
    }

    void expect_eq_read(int fd, size_t bufsize, size_t size) {
        off_t orig_pos = lseek(fd, 0, SEEK_CUR);

        ssize_t read_result, ft_read_result;
        int read_errno, ft_read_errno;

        char *buf1 = new char[bufsize]();  // バッファサイズに応じて確保
        char *buf2 = new char[bufsize]();

        errno = 0;
        read_result = read(fd, buf1, size);
        read_errno = errno;

        lseek(fd, orig_pos, SEEK_SET);

        errno = 0;
        ft_read_result = ft_read(fd, buf2, size);
        ft_read_errno = errno;

        EXPECT_EQ(read_result, ft_read_result);
        EXPECT_EQ(read_errno, ft_read_errno);

        if (read_result > 0) {
            EXPECT_EQ(memcmp(buf1, buf2, read_result), 0);
        }

        delete[] buf1;
        delete[] buf2;
    }
};

TEST_F(FtReadTest, BasicRead) {
    const std::string content = "Hello World";
    setup_test_file(content);
    expect_eq_read(test_fd, 1024, 5);  // "Hello"
}

TEST_F(FtReadTest, BasicRead2) {
    const std::string content = "Hello\nWorld\n";
    setup_test_file(content);
    expect_eq_read(test_fd, 1024, content.size());  // "Hello\nWorld\n"
}

TEST_F(FtReadTest, ReadEntireFile) {
    std::string content = "The quick brown fox jumps over the lazy dog";
    setup_test_file(content);
    expect_eq_read(test_fd, 1024, content.size());
}

TEST_F(FtReadTest, ReadEmpty) {
    setup_test_file("");
    expect_eq_read(test_fd, 1024, 10);
}

TEST_F(FtReadTest, ReadAfterEOF) {
    setup_test_file("Short text");
    lseek(test_fd, 0, SEEK_END);
    expect_eq_read(test_fd, 1024, 10);
}

TEST_F(FtReadTest, ReadInvalidFd) {
    expect_eq_read(-1, 1024, 10);
}

TEST_F(FtReadTest, ReadWithOffset) {
    setup_test_file("0123456789ABCDEF");
    lseek(test_fd, 5, SEEK_SET);
    expect_eq_read(test_fd, 1024, 5);  // "56789"
}

TEST_F(FtReadTest, ReadLargeSize) {
    const size_t file_size = 2048;
    std::string content(file_size, 'X');  // 2kB

    setup_test_file(content);
    expect_eq_read(test_fd, file_size, file_size);  // 2kB
}

TEST_F(FtReadTest, ReadLargeSize2) {
    const size_t file_size = 2048;
    const size_t request_size = 4096;
    std::string content(file_size, 'X');  // 2kB

    setup_test_file(content);
    expect_eq_read(test_fd, file_size, request_size);  // 2kB
}

// TEST(FtReadDeathTest, NullPtr) {
//     int fd = open("/dev/null", O_RDONLY);
//     ASSERT_NE(fd, -1);
//
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wnonnull"
// #pragma GCC diagnostic ignored "-Wunused-variable"
//     testing::FLAGS_gtest_death_test_style = "threadsafe";
//
//     char *null_ptr = NULL;
//     EXPECT_DEATH({ (void)read(fd, null_ptr, 10); }, ".*");
//     EXPECT_DEATH({ (void)ft_read(fd, null_ptr, 10); }, ".*");
//
// #pragma GCC diagnostic pop
//
//     close(fd);
// }
