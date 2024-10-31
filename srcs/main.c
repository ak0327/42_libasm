#include <stdio.h>
#include <string.h>
#include "libasm.h"

void test_strlen(const char *s) {
    printf("[%s]:\n", s);
    printf(" ft_strlen: %zu\n", ft_strlen(s));
    printf(" strlen   : %zu\n\n", strlen(s));
}

int main(void) {
    test_strlen("hello");
    test_strlen("");

    return 0;
}
