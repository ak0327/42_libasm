#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

extern "C" ssize_t ft_write(int test_fd, const void *buf, size_t nbyte);

class FtWriteTest : public ::testing::Test {
 protected:
    int test_fd;
    const char *test_file_path = "/tmp/test_ft_write.txt";
    char read_buf[40];

    void SetUp() override {
        this->test_fd = open(this->test_file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
        ASSERT_NE(this->test_fd, -1) << "Failed to create test file: " << strerror(errno);
    }

    void TearDown() override {
        if (this->test_fd != -1) { close(this->test_fd); }
        remove(this->test_file_path);
    }

    void expect_eq_write(int write_fd, const char *write_buf, size_t size) {
        ssize_t write_result, ft_write_result;
        int write_errno, ft_write_errno;

        errno = 0;
        write_result = write(write_fd, write_buf, size);
        write_errno = errno;

        errno = 0;
        ft_write_result = ft_write(write_fd, write_buf, size);
        ft_write_errno = errno;

        EXPECT_EQ(write_result, ft_write_result);
        EXPECT_EQ(write_errno, ft_write_errno);

        if (write_fd == this->test_fd && write_buf != nullptr && size > 0) {
            lseek(this->test_fd, 0, SEEK_SET);
            ssize_t bytes_read = read(this->test_fd, this->read_buf, size * 2);
            ASSERT_EQ(bytes_read, size * 2)
                << "Failed to read the expected number of bytes";

            EXPECT_EQ(std::memcmp(this->read_buf, write_buf, size), 0)
                << "write content does not match.";
            EXPECT_EQ(std::memcmp(this->read_buf + size, write_buf, size), 0)
                << "ft_write content does not match.";
        }
    }
};

TEST_F(FtWriteTest, WriteSuccessDefault) {
    const char write_buf[] = "Hello World";
    expect_eq_write(this->test_fd, write_buf, strlen(write_buf));
}

TEST_F(FtWriteTest, WriteSuccessEmptyBuf) {
    expect_eq_write(this->test_fd, "", 0);
}

TEST_F(FtWriteTest, WriteFailureInvalidFd) {
    const char write_buf[] = "Invalid FD Test";
    int invalid_fd = -1;
    expect_eq_write(invalid_fd, write_buf, strlen(write_buf));
}

TEST_F(FtWriteTest, WriteFailureBufNullptr) {
    expect_eq_write(this->test_fd, nullptr, 10);
}
