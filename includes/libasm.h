#ifndef LIBASM_H
# define LIBASM_H

# include <errno.h>

size_t  ft_strlen(const char *s);

char    *ft_strcpy(char *dst, const char *src);
char    *ft_strdup(const char *s);

int     ft_strcmp(const char *s1, const char *s2);

ssize_t ft_write(int fd, const void *buf, size_t nbyte);
ssize_t ft_read(int fd, void *buf, size_t nbyte);

#endif
