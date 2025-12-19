# Libft — Reimplementation of common C library functions for 42 school

This repository contains my Libft: a small, hand-written C library that reimplements essential libc functions (strings, memory, conversions) and provides utility functions and linked-list helpers. It is intended as a reusable foundation for 42 school projects and exercises.

## Quick start

Build the static library (requires `make` and `gcc`):

```sh
make        # builds libft.a
make clean  # remove object files
make fclean # remove object files and libft.a
make re     # rebuild from scratch
```

To use the library in another project, either copy the source files into your project or link against `libft.a` when compiling:

```sh
gcc -I. -L. -lft your_program.c -o your_program
```

### Linking and compiler flags — quick reference

-   `gcc` — the GNU C compiler (used here as the driver that invokes the compiler, assembler and linker).
-   `-I.` — add the current directory to the header search path so `#include "libft.h"` is found.
-   `-L.` — add the current directory to the library search path so `-l<name>` can find `lib<name>.a` or `lib<name>.so`. You can pass multiple `-L` flags to search additional directories.
-   `-l<name>` — link with the library named `<name>`. The linker looks for `lib<name>.a` (static) or `lib<name>.so` (shared) in the `-L` paths.
-   Naming rule — to link `libfoo.a` or `libfoo.so` use `-lfoo`. If the file has a nonstandard name or path, pass it directly (for example: `gcc ... path/to/libcustom.a ...`).
-   Order matters — the linker resolves symbols left-to-right in a single pass. Put source/object files before libraries so the linker can resolve symbols from those objects using the libraries that follow. For circular dependencies, repeat libraries or use `--start-group`/`--end-group`.
-   Static vs shared:
    -   By default the linker chooses static or shared based on availability and flags.
    -   To force static for specific libraries: `-Wl,-Bstatic -lfoo -Wl,-Bdynamic`.
    -   For shared libraries, ensure the runtime loader can find them (set `LD_LIBRARY_PATH` or embed an rpath with `-Wl,-rpath,/path/to/libs`).
-   Dependency order — keep libraries in dependency order (if A depends on B, use `-lA -lB`). For complex external libraries prefer `pkg-config` to get the correct `-I`, `-L`, and `-l` flags automatically.
-   `-o your_program` — write the resulting executable to the named file.

Examples:

-   Link by name (uses `-lft` to find `libft` in `-L` paths):
    -   `gcc -I. example.c -L. -lft -o example`
-   Link the archive directly (order not sensitive for that archive):
    -   `gcc -I. example.c libft.a -o example`

Notes:

-   If you have libraries with circular references, either repeat them on the command line or wrap them with `-Wl,--start-group ... -Wl,--end-group`.
-   Use `pkg-config --cflags --libs name` when available to avoid manual ordering and flags.
-   The linker does a single pass left-to-right; placing libraries after objects that need them is the simplest, most reliable approach.

## Examples

Quick example showing how to compile and link a small program against `libft.a`.

Create `example.c`:

```c
#include "libft.h"
#include <stdio.h>

int main(void)
{
    const char *s = "Hello, Libft!";
    size_t len = ft_strlen(s);
    printf("%s -> %zu\n", s, len);
    ft_putstr_fd("Printed with ft_putstr_fd\n", 1);
    return 0;
}
```

Build options (either link the archive directly or use -lft when libft.a is in the current directory):

```sh
# compile and link with the archive file directly
gcc -I. example.c libft.a -o example

# or use -L. -lft (note: -lft must come after the source/objects)
gcc -I. -L. -lft example.c -o example
```

Run:

```sh
./example
```

## Implemented functions

-   Character classification & conversion
-   Memory management
-   String handling
-   Conversion
    -   `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower`
    -   `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`, `ft_calloc`
    -   `ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_strdup`, `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`, `ft_strmapi`
    -   `ft_atoi`
    -   `ft_lstnew`, `ft_lstadd_front`, `ft_lstsize`, `ft_lstlast`, `ft_lstadd_back`, `ft_lstdelone`, `ft_lstclear`, `ft_lstiter`, `ft_lstmap`

## Contributing

This repo follows the 42 project rules: all files must compile with `-Wall -Wextra -Werror`, no global variables, and `libft.a` must be created at the repository root using `ar`. If you open PRs, keep changes focused and include tests when possible.

Feel free to open issues or submit PRs for fixes, improvements, or additional functions.
