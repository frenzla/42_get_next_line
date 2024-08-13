![42banner](https://github.com/user-attachments/assets/842eb8b3-406b-4eb2-b257-1133cdb59218)

# 42_get_next_line

The aim of this project is to code a function that returns a line read from a file descriptor.
Repeated calls to this function should enable to read the whole text file pointed to by the file descriptor, one line at a time.

This exercise has been instrumental in learning an interesting new concept in C: static variables.

Part of my coding mastering journey 🥷


## 42

[42 is a world class computer programming school](https://42.fr/en/homepage/) that proposes a new way of learning computer science:
- No teachers
- No classrooms
- Open 24/7, 365 days/year
- Students are trained through peer-to-peer pedagogy, and project-based learning.
- Methodology that develops both tech & life skills.
- The 42 cursus is free for whoever is approved in its selection process.


## How to Use

**1. Using it in your code**

To use the function in your code, simply include its header:

```C
#include "get_next_line.h"
```

and, when compiling your code, add the source files and the required flag:

```shell
get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=<size>
```

If you're on Linux, you may as well need the following flags:

```shell
-D ARG_MAX="sysconf(_SC_ARG_MAX)" -D OPEN_MAX=1024
```

A bonus part is also present. To compile with that, add `_bonus` to each `.c` file and to the `.h` file.

## Testing

The repo includes a third-party testers to test the function:

- [Tripouille/gnlTester](https://github.com/Tripouille/gnlTester)

Go to the directory of the tester and:

make m = launch mandatory tests

make b = launch bonus tests

make a = launch mandatory tests + bonus tests
