#include "ft_printf.h"

/**
 * @brief Applies the '#' flag prefix ('0x' or '0X') to the hexadecimal string if applicable.
 *
 * @param hex_str The hexadecimal string to which the prefix may be applied.
 * @param state   Pointer to t_printf_state structure holding parsing state and flags.
 * @param is_uppercase Flag indicating if the hexadecimal letters should be uppercase.
 * @return A newly allocated string with the prefix applied if needed; otherwise, returns the original string.
 */
char *ft_apply_prefix(char *hex_str, t_printf_state *state, int is_uppercase)
{
    char *prefix;
    char *result;

    if (!state->flag_hash || !hex_str || (ft_strlen(hex_str) == 1 && hex_str[0] == '0'))
        return hex_str;
    if (is_uppercase)
        prefix = "0X";
    else
        prefix = "0x";
    result = ft_strjoin(prefix, hex_str);
    if (!result)
        state->has_error = TRUE;
    free(hex_str);
    return result;
}

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
    char *precision_str;
    char *prefix_str;
    long padding;

    if (format[state->format_pos] != 'x' && format[state->format_pos] != 'X')
        return;
    str = ft_ull_to_hex(va_arg(arg, unsigned long long), state, format[state->format_pos] == 'X');
    if (!str)
        return;
    precision_str = ft_apply_precision(str, state->precision, 0);
    free(str);
    if (!precision_str)
    {
        state->has_error = TRUE;
        return;
    }
    prefix_str = ft_apply_prefix(precision_str, state, format[state->format_pos] == 'X');
    if (!prefix_str)
        return;
    padding = 0;
    if (state->field_width > (long)ft_strlen(prefix_str))
        padding = state->field_width - (long)ft_strlen(prefix_str);
    ft_print_formatted_conversion(prefix_str, (int)ft_strlen(prefix_str), (int)padding, state);
    free(prefix_str);
}