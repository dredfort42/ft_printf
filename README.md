# ft_printf

_This project has been created as part of the 42 curriculum by dnovikov._

## Description

**ft_printf** is a custom implementation of the C standard library function `printf()`. This project recreates the variadic function's behavior, including format string parsing, conversion specifiers, and formatting flags. The goal is to deeply understand how formatted output works at a low level by implementing a simplified yet functional version of this fundamental I/O function.

The project handles multiple conversion specifiers (`%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, `%%`) and supports various formatting flags (`-`, `0`, `.`, `#`, ` ` (space), `+`) along with field width and precision modifiers. The implementation is built on top of a custom C library (`libft`) developed in a previous 42 project, demonstrating modular code design and reusability.

## Instructions

### Compilation

To compile the library, use the provided Makefile:

```bash
make
```

This command will:

1. Compile the `libft` dependency
2. Compile all `ft_printf` source files
3. Create the static library `libftprintf.a`

### Clean Build Files

```bash
make clean    # Remove object files
make fclean   # Remove object files and library
make re       # Recompile everything from scratch
```

### Usage in Your Project

1. Include the header in your source file:

```c
#include "ft_printf.h"
```

2. Compile your program with the library:

```bash
gcc your_program.c -L. -lftprintf -o your_program
```

3. Run your program:

```bash
./your_program
```

### Basic Example

```c
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("Hello, %s!\n", "World");
    ft_printf("Characters printed: %d\n", count);
    return (0);
}
```

## Testing

The project can be tested with **printfTester**, a comprehensive testing suite that validates `ft_printf` against the standard library's `printf`.

### Running Tests

```bash
git clone {{actual_printf_tester_repo_link}} printfTester
cd printfTester
make a
```

This will compile and run tests for all conversion specifiers and flag combinations, comparing your output against the expected standard library behavior.

## Conversion Specifiers and Formatting Flags

### Supported Conversion Specifiers

| Specifier | Description                      | Type           |
| --------- | -------------------------------- | -------------- |
| `%c`      | Single character                 | `char`         |
| `%s`      | String of characters             | `char *`       |
| `%p`      | Pointer address                  | `void *`       |
| `%d`      | Signed decimal integer           | `int`          |
| `%i`      | Signed decimal integer           | `int`          |
| `%u`      | Unsigned decimal integer         | `unsigned int` |
| `%x`      | Unsigned hexadecimal (lowercase) | `unsigned int` |
| `%X`      | Unsigned hexadecimal (uppercase) | `unsigned int` |
| `%%`      | Literal percent sign             | N/A            |

### Supported Flags

| Flag        | Description                                      | Applicable To                |
| ----------- | ------------------------------------------------ | ---------------------------- |
| `-`         | Left-justify within field width                  | All conversions              |
| `0`         | Zero-pad numbers (ignored with `-` or precision) | `d`, `i`, `u`, `x`, `X`      |
| `.`         | Precision modifier                               | `d`, `i`, `u`, `x`, `X`, `s` |
| `#`         | Alternate form (add `0x`/`0X` prefix)            | `x`, `X`                     |
| ` ` (space) | Insert space before positive numbers             | `d`, `i`                     |
| `+`         | Always show sign (overrides space flag)          | `d`, `i`                     |

### Field Width and Precision

-   **Field Width**: Minimum number of characters to output. Pad with spaces (or zeros with `0` flag).

    -   Example: `%5d` - right-justified in 5 characters
    -   Can use `*` to pass width as argument: `%*d`

-   **Precision**:
    -   For integers (`d`, `i`, `u`, `x`, `X`): minimum number of digits
    -   For strings (`s`): maximum number of characters to print
    -   Example: `%.5d` - at least 5 digits (zero-padded)
    -   Can use `.*` to pass precision as argument: `%.*s`

## Detailed Usage Examples

### Character Conversion (`%c`)

```c
ft_printf("[%c]", 'A');           // Output: [A]
ft_printf("[%5c]", 'A');          // Output: [    A] (right-justified)
ft_printf("[%-5c]", 'A');         // Output: [A    ] (left-justified)
```

**Explanation**: The `%c` specifier prints a single character. Field width adds padding (spaces only, `0` flag is ignored).

---

### String Conversion (`%s`)

```c
ft_printf("[%s]", "Hello");           // Output: [Hello]
ft_printf("[%10s]", "Hello");         // Output: [     Hello] (right-justified)
ft_printf("[%-10s]", "Hello");        // Output: [Hello     ] (left-justified)
ft_printf("[%.3s]", "Hello");         // Output: [Hel] (truncated to 3 chars)
ft_printf("[%10.3s]", "Hello");       // Output: [       Hel] (width 10, precision 3)
ft_printf("[%-10.3s]", "Hello");      // Output: [Hel       ] (left-justified)
ft_printf("[%s]", NULL);              // Output: [(null)]
```

**Explanation**:

-   Precision limits maximum characters printed
-   Field width adds padding
-   NULL strings are handled as `"(null)"`
-   Zero flag is ignored for strings

---

### Pointer Conversion (`%p`)

```c
int x = 42;
void *ptr = &x;

ft_printf("[%p]", ptr);               // Output: [0x7ffee4bff618]
ft_printf("[%20p]", ptr);             // Output: [        0x7ffee4bff618] (right-justified)
ft_printf("[%-20p]", ptr);            // Output: [0x7ffee4bff618        ] (left-justified)
ft_printf("Addr: [%p]\n", (void *)0); // Output: Addr: [0x0]
```

**Explanation**:

-   Prints memory addresses in hexadecimal with `0x` prefix
-   Always lowercase hexadecimal digits
-   Only field width and `-` flag are supported
-   Other flags (`#`, `0`, `+`, space, precision) are ignored

---

### Signed Integer Conversion (`%d`, `%i`)

#### Basic Usage

```c
ft_printf("[%d]", 42);                // Output: [42]
ft_printf("[%i]", -42);               // Output: [-42]
ft_printf("[%d]", 0);                 // Output: [0]
```

#### Field Width

```c
ft_printf("[%5d]", 42);               // Output: [   42] (space-padded)
ft_printf("[%5d]", -42);              // Output: [  -42]
ft_printf("[%-5d]", 42);              // Output: [42   ] (left-justified)
ft_printf("[%-5d]", -42);             // Output: [-42  ]
```

#### Zero Padding

```c
ft_printf("[%05d]", 42);              // Output: [00042]
ft_printf("[%05d]", -42);             // Output: [-0042] (sign outside padding)
```

#### Precision

```c
ft_printf("[%.5d]", 42);              // Output: [00042]
ft_printf("[%.5d]", -42);             // Output: [-00042]
ft_printf("[%.0d]", 0);               // Output: (empty) - special case
```

#### Sign Flags

```c
ft_printf("[%+d]", 42);               // Output: [+42]
ft_printf("[%+d]", -42);              // Output: [-42]
ft_printf("[% d]", 42);               // Output: [ 42] (space before positive)
ft_printf("[% d]", -42);              // Output: [-42] (space ignored for negative)
ft_printf("[%+d]", 0);                // Output: [+0]
```

#### Combined Flags

```c
ft_printf("[%-+8d]", 42);             // Output: [+42      ] (left-justified, always sign)
ft_printf("[%+08d]", 42);             // Output: [+0000042] (zero-padded with sign)
ft_printf("[%-+8.5d]", 42);           // Output: [+00042   ] (left, sign, precision)
ft_printf("[%10.5d]", -42);           // Output: [     -00042] (width 10, precision 5)
```

**Explanation**:

-   `%d` and `%i` are identical
-   Precision specifies minimum digits (zero-padded)
-   `0` flag is ignored when precision is set or `-` is used
-   `+` flag always shows sign, overrides space flag
-   Space flag adds space before positive numbers only

---

### Unsigned Integer Conversion (`%u`)

```c
ft_printf("[%u]", 42);                // Output: [42]
ft_printf("[%u]", 0);                 // Output: [0]
ft_printf("[%u]", -1);                // Output: [4294967295] (wraps around)
ft_printf("[%5u]", 42);               // Output: [   42]
ft_printf("[%-5u]", 42);              // Output: [42   ]
ft_printf("[%.5u]", 42);              // Output: [00042]
ft_printf("[%05u]", 42);              // Output: [00042]
ft_printf("[%10.5u]", 42);            // Output: [     00042]
```

**Explanation**:

-   Prints unsigned decimal numbers
-   Negative values wrap around (unsigned behavior)
-   Supports field width, precision, `0` and `-` flags
-   Sign flags (`+`, space) and `#` flag are ignored

---

### Hexadecimal Conversion (`%x`, `%X`)

#### Basic Usage

```c
ft_printf("[%x]", 255);               // Output: [ff]
ft_printf("[%X]", 255);               // Output: [FF]
ft_printf("[%x]", 0);                 // Output: [0]
```

#### Field Width and Padding

```c
ft_printf("[%5x]", 255);              // Output: [   ff] (space-padded)
ft_printf("[%-5x]", 255);             // Output: [ff   ] (left-justified)
ft_printf("[%05x]", 255);             // Output: [000ff] (zero-padded)
```

#### Precision

```c
ft_printf("[%.5x]", 255);             // Output: [000ff]
ft_printf("[%.5X]", 255);             // Output: [000FF]
ft_printf("[%.2x]", 255);             // Output: [ff] (precision less than needed)
```

#### Alternate Form (`#` flag)

```c
ft_printf("[%#x]", 255);              // Output: [0xff]
ft_printf("[%#X]", 255);              // Output: [0XFF]
ft_printf("[%#x]", 0);                // Output: [0] (no prefix for zero)
ft_printf("[%#5x]", 255);             // Output: [ 0xff]
ft_printf("[%#05x]", 255);            // Output: [0x0ff] (prefix counts in width)
```

#### Combined Flags

```c
ft_printf("[%-#8x]", 255);            // Output: [0xff    ] (left-justified with prefix)
ft_printf("[%#8.5x]", 255);           // Output: [ 0x000ff] (width 8, precision 5, prefix)
ft_printf("[%-#8.5X]", 255);          // Output: [0X000FF ] (all flags combined)
```

**Explanation**:

-   `%x` uses lowercase (`a-f`), `%X` uses uppercase (`A-F`)
-   `#` flag adds `0x` or `0X` prefix for non-zero values
-   Prefix is NOT added for zero
-   Precision specifies minimum digits (not counting prefix)
-   `0` flag is ignored when precision is specified or `-` is used

---

### Percent Sign (`%%`)

```c
ft_printf("[%%]");                    // Output: [%]
ft_printf("[100%%]");                 // Output: [100%]
ft_printf("[%%d]", 42);               // Output: [%d] (literal, not conversion)
```

**Explanation**: Use `%%` to print a literal `%` character. No flags or modifiers apply.

## Resources

### Classic References

#### Official Documentation

-   [`printf` man page](https://man7.org/linux/man-pages/man3/printf.3.html) - POSIX standard specification

#### Tutorials and Articles

-   [Variadic Functions in C](https://en.cppreference.com/w/c/variadic) - Understanding `va_list`, `va_start`, `va_arg`, `va_end`
-   [printf Format Specifiers](https://cplusplus.com/reference/cstdio/printf/) - Comprehensive format string reference

## Algorithm and Data Structure

### Core Algorithm

The ft_printf implementation uses a **state machine pattern** with a centralized state structure to parse and process format strings.

#### Main Processing Flow

1. **Initialization**: Create a `t_printf_state` structure to track:

    - Total characters printed
    - Current position in format string
    - Error flag
    - Formatting flags (`-`, `0`, `#`, ` `, `+`)
    - Field width and precision

2. **Format String Traversal**: Iterate through the format string character by character:

    - Regular characters → write directly to output
    - `%` character → trigger format specifier parsing

3. **Format Specifier Parsing** (upon encountering `%`):

    ```
    % [flags] [width] [.precision] conversion
    ```

    - Parse flags in order: `-`, `0`, `#`, ` `, `+`
    - Parse field width (digits or `*`)
    - Parse precision (`.` followed by digits or `*`)
    - Identify conversion specifier (`c`, `s`, `p`, `d`, `i`, `u`, `x`, `X`, `%`)

4. **Conversion Handling**: Dispatch to appropriate handler function:

    - Extract argument from `va_list`
    - Convert value to string representation
    - Apply precision (for numbers: minimum digits; for strings: maximum length)
    - Add prefixes (signs for `d`/`i`, `0x` for `x`/`X`)
    - Calculate and apply padding
    - Write formatted output

5. **Return**: Return total characters printed or -1 on error

### Data Structure: `t_printf_state`

```c
typedef struct s_printf_state
{
    int printed_chars;    // Running total of output characters
    long format_pos;      // Current index in format string
    short has_error;      // Error flag (memory allocation, write failure)
    int precision;        // Precision value (-1 if not specified)
    int field_width;      // Field width (0 if not specified)
    short flag_minus;     // Left-justify flag
    short flag_zero;      // Zero-padding flag
    short flag_hash;      // Alternate form flag
    short flag_space;     // Space before positive numbers
    short flag_plus;      // Always show sign
} t_printf_state;
```

**Design Rationale**:

-   Single structure passed by pointer reduces function parameters
-   State persists across recursive parsing calls
-   Flags stored as separate fields for O(1) access and clear logic
-   `short` type used for flags to minimize memory footprint
-   Negative precision (-1) indicates "not specified" vs "zero precision"

### Key Algorithms

#### 1. Number to String Conversion

-   **Signed integers** (`%d`, `%i`): Use `ft_itoa()` from libft
-   **Unsigned integers** (`%u`): Custom digit-counting algorithm to allocate exact buffer, then fill from right to left
-   **Hexadecimal** (`%x`, `%X`): Iterative division by 16, map remainders to hex digits

```
Algorithm for unsigned int to string:
1. Count digits by repeatedly dividing by 10
2. Allocate buffer (digit_count + 1)
3. Fill buffer from right to left using modulo and division
4. Null-terminate
```

#### 2. Precision Application

For integers:

```
1. If precision > current_length: prepend zeros
2. If negative: handle sign separately
3. Allocate new buffer, copy with padding
```

For strings:

```
1. If precision < string_length: truncate
2. Copy only precision characters to new buffer
```

#### 3. Padding Strategy

Two-phase padding based on justification:

**Right-justified** (default):

```
1. Calculate padding = field_width - content_length
2. Write padding (spaces or zeros)
3. Write content
```

**Left-justified** (`-` flag):

```
1. Write content
2. Calculate padding = field_width - content_length
3. Write padding (always spaces)
```

#### 4. Flag Priority Logic

-   `-` flag disables `0` flag (left-justification uses space padding)
-   `+` flag overrides space flag (both affect sign display)
-   Precision overrides `0` flag for integers
-   `#` flag only applies to non-zero hex values

### Edge Cases Handled

1. **NULL string pointer**: Replaced with `"(null)"`
2. **Zero with precision zero**: Prints empty string (e.g., `%.0d` with 0)
3. **Zero with `#` flag in hex**: No prefix added
4. **Negative field width from `*`**: Treated as `-` flag with positive width
5. **Memory allocation failure**: Set error flag, return -1
6. **Write system call failure**: Caught in state structure
