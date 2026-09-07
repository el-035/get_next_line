# Get Next Line

Get Next Line is a C project from the 42 curriculum. It implements a function
that reads and returns one line at a time from a file descriptor, retaining any
unread data between calls.

The project focuses on static variables, dynamic memory management, file
descriptors, and buffered input.

## Usage

Add the source files and header to your project, then call:

```c
char *get_next_line(int fd);
```

Each successful call returns the next line, including its trailing newline when
one is present. The function returns `NULL` at end of file or when an error
occurs. The caller is responsible for freeing every returned line.

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int  fd;
    char *line;

    fd = open("example.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        write(1, line, ft_strchr(line, '\0') - line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Compilation

Compile the implementation with your program and choose a buffer size using
the `BUFFER_SIZE` macro:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c main.c -o gnl
```

If no value is provided, the header uses a default buffer size of `10`.
