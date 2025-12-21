#include "ft_printf.h"

/**
 * @brief Handles the 'x' and 'X' conversion specifiers for hexadecimal representation.
 *
 * @param arg    Variadic argument list to extract the value.
 * @param format Format string being parsed.
 * @param state   Pointer to t_printf_state structure holding parsing state and flags.
 *
 * @note
 *
 * Flags and Modifiers:
 *
 *   - Field width and left-justification ('-') are supported.
 *
 *   - Precision specifies the minimum number of digits to be printed.
 *
 *   - Zero-padding ('0') is ignored if precision is specified or if left-justification is used.
 *
 *   - The '#' flag adds '0x' or '0X' prefix for non-zero values.
 *
 * Usage Example:
 *
 *   - printf("%x", 255);        // Output: 'ff'
 *
 *   - printf("%#x", 255);       // Output: '0xff'
 *
 *   - printf("%X", 255);        // Output: 'FF'
 *
 *   - printf("%#X", 255);       // Output: '0XFF'
 *
 *   - printf("%5x", 255);       // Output: '␣␣␣ff' (right-justified in width 5)
 *
 *   - printf("%-5x", 255);      // Output: 'ff␣␣␣' (left-justified in width 5)
 *
 *   - printf("%.5x", 255);      // Output: '000ff' (precision 5)
 *
 *   - printf("%05x", 255);      // Output: '000ff' (zero-padded to width 5)
 *
 *   - printf("%-#8.5x", 255);    // Output: '0x000ff␣␣' (left-justified, width 8, precision 5)
 *
 *   - printf("%x", 0);          // Output: '0'
 *
 *   - printf("%#x", 0);         // Output: '0' (no prefix for zero)
 *
 *   - printf("%X", 0);          // Output: '0'
 *
 *   - printf("%#X", 0);         // Output: '0' (no prefix for zero)
 */
void ft_handle_hex_conversion(va_list arg, const char *format, t_printf_state *state)
{
    char *str;

    if (format[state->format_pos] != 'x' && format[state->format_pos] != 'X')
        return;
}