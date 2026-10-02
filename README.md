*This activity has been created as part of the 42 curriculum by omajarad.*

get_next_line
# Description

get_next_line is a project from the 42 curriculum whose goal is to implement a function capable of reading a file descriptor one line at a time.

The main function provided by this project is:

char *get_next_line(int fd);


Each call to get_next_line() returns the next line available from the given file descriptor. The returned line includes the newline character (\n) when one is present.

The project focuses on understanding and implementing:

File descriptor management.

The read() system call.

Static variables.

Dynamic memory allocation.

String manipulation.

Buffer management.

Managing data that remains between multiple function calls.

Handling end-of-file and read errors.

The implementation uses a static stash to preserve data that has been read but does not yet belong to the line returned to the caller.

# Instructions
Compilation

The project requires a C compiler and the standard C library.

Compile the source files together with your own test program. For example:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl


The value of BUFFER_SIZE can be changed during compilation:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
get_next_line.c get_next_line_utils.c main.c -o gnl


or:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=1000 \
get_next_line.c get_next_line_utils.c main.c -o gnl

Execution

A simple test program can open a file and repeatedly call get_next_line():

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);

    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }

    close(fd);
    return (0);
}


Compile and execute:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl

./gnl

Testing

The implementation should be tested with different types of input:

An empty file.

A file containing one line.

Multiple lines.

Lines with different lengths.

A file ending with \n.

A file not ending with \n.

Very small BUFFER_SIZE values such as 1.

Large BUFFER_SIZE values.

Consecutive empty lines.

A file containing only newline characters.

Invalid file descriptors.

Multiple calls after reaching EOF.

Algorithm

The implementation uses a persistent stash and incremental reading algorithm.

The main idea is to read data from the file descriptor in chunks and store the data in a static string called stash. The stash remains available between calls to get_next_line().

1. Maintain a static stash

get_next_line() declares:

static char *stash;


Because stash is static, its value persists after the function returns.

This is necessary because one read() operation can retrieve more than one line.

For example, if the file contains:

Hello
World
42


and the buffer is large enough, one call to read() could retrieve all three lines.

After returning:

Hello


the remaining data:

World
42


must be preserved for the next call.

The stash provides this persistent storage.

2. Read until a newline is available

The function read_stash() repeatedly calls read() while the stash does not contain a newline:

while (!*stash || !ft_strchr(*stash, '\n'))


Each read stores up to BUFFER_SIZE bytes in a temporary buffer.

The data is then appended to the stash using update_stash().

Conceptually:

stash + newly_read_data
        ↓
   new stash


A new dynamically allocated string is created large enough to contain both the previous stash and the newly read data.

3. Extract the next line

Once the stash contains a newline, ft_extract_fill_line() searches for the first newline character.

For example:

stash:
Hello\nWorld\n42


The function extracts:

Hello\n


and returns it to the caller.

If the stash contains data without a newline because EOF has been reached, that remaining data is returned as the final line.

4. Preserve the remaining data

After extracting the line, saves_update() removes the returned portion from the stash.

For example:

Before:
Hello\nWorld\n42


After extracting Hello\n:

World\n42


The remaining content becomes the new stash.

The next call to get_next_line() can therefore continue from exactly where the previous call stopped.

5. Continue until EOF

The process repeats:

read data
   ↓
append to stash
   ↓
find newline
   ↓
extract one line
   ↓
save remaining data
   ↓
return line


Eventually, read() returns 0, indicating EOF.

If no data remains in the stash, get_next_line() returns:

NULL

Function Overview
get_next_line()

The main public function.

It:

Validates the file descriptor.

Reads enough data into the stash.

Extracts the next line.

Updates the stash with the remaining data.

Returns the extracted line.

read_buffer()

Reads up to BUFFER_SIZE bytes from the file descriptor.

It also adds a terminating \0 so that the buffer can be treated as a C string.

read_stash()

Keeps reading until either:

A newline is found in the stash.

EOF is reached.

A read or allocation error occurs.

update_stash()

Creates a new string containing:

old stash + newly read buffer


The old stash is freed after the new one has been successfully created.

ft_extract_fill_line()

Finds the first newline and allocates/copies the corresponding line.

saves_update()

Creates a new stash containing everything after the first newline.

ft_strlen()

Calculates the length of a string.

ft_strchr()

Searches for a specific character in a string.

ft_memcpy()

Copies a specified number of bytes from one memory area to another.

Memory Management

Dynamic memory allocation is used because the length of a line is not known in advance.

The implementation allocates memory for:

The temporary read buffer.

The expanded stash.

The returned line.

The updated stash.

Allocated memory is freed when it is no longer required.

In particular, the old stash is freed when it is replaced by a newly allocated stash.

Error paths also attempt to free allocated memory before returning.

Technical Choices
Static storage

A static variable is used to preserve unread data between calls.

This is the key mechanism that allows get_next_line() to return exactly one line per call.

Dynamic stash expansion

Instead of assuming that a line fits inside BUFFER_SIZE, the stash grows whenever more data needs to be stored.

This allows the function to handle lines significantly larger than the buffer size.

Incremental reading

The implementation does not attempt to read the entire file at once.

It reads only the amount necessary to obtain the next line, while preserving excess data for future calls.

This keeps the implementation compatible with the requirements of the project and with file descriptors where reading the entire content at once would not be appropriate.

Complexity

Let n be the amount of data currently stored in the stash.

Searching for a newline and calculating the stash length require linear scans, so individual operations are generally O(n).

Appending data creates a new allocation and copies the previous stash, which is also O(n) for the amount of existing stash data.

The memory usage is O(n) for the currently stored unread data, in addition to the returned line and temporary buffer.

The exact runtime behavior depends on the BUFFER_SIZE and the distribution of newline characters.

# Resources

The following resources are useful for understanding the concepts involved in this project:

man 2 read — documentation for the Unix read() system call.

man 2 open — documentation for opening files and obtaining file descriptors.

man 2 close — documentation for closing file descriptors.

man 3 malloc — documentation for dynamic memory allocation.

man 3 free — documentation for releasing allocated memory.

The 42 get_next_line project subject — the official project requirements and constraints.

C language documentation covering pointers, arrays, strings, dynamic memory, and static variables.

## AI Usage

AI was used during the development of this activity.

In particular, this README was written by AI based on the provided implementation and the requirements of the 42 get_next_line activity.

AI assistance was used for:

Structuring and writing this README.md.

Explaining the purpose of the stash.

Describing the reading and line-extraction algorithm.

Explaining the roles of the individual helper functions.

Documenting the memory-management strategy.

Explaining the general complexity of the implementation.

Providing a clear description of how the different functions work together.

The C implementation itself should be understood and verified by the student. AI-generated explanations are intended as documentation and learning support and do not replace understanding the code or the official 42 project requirements.

Project Structure

A typical project structure is:

get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── README.md
└── test files / main.c


The README.md file is located at the root of the repository as required.

Conclusion

The central idea of this implementation is to separate reading from line extraction.

Data is continuously read into a persistent stash until a complete line is available. One line is then extracted and returned, while all unread data remains in the stash for the next call.

This approach makes it possible to correctly handle lines of arbitrary length and files where a single read() call contains multiple lines.
