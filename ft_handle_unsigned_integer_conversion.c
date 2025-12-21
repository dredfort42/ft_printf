#include "ft_printf.h"

/**
 * @brief Processes the unsigned integer according to flags and returns its string representation.
 *
 * @param n   The unsigned integer to be processed.
 * @param state Pointer to t_printf_state structure holding parsing state and flags.
 * @return A newly allocated string representing the unsigned integer with applied flags.
 */
static char *ft_process_unsigned_integer(unsigned int n, t_printf_state *state)
{
    char *result;
    unsigned int tmp;
    size_t digits;

    tmp = n;
    digits = 1;
    while (tmp >= 10)
    {
        tmp /= 10;
        digits++;
    }
    result = (char *)malloc(sizeof(char) * (digits + 1));
    if (!result)
    {
        state->has_error = TRUE;
        return (NULL);
    }
    result[digits] = '\0';
    tmp = n;
    while (digits--)
    {
        result[digits] = (char)('0' + (tmp % 10));
        tmp /= 10;
    }
    return (result);
}

/**
 * @brief Handles the '%u' conversion specifier for unsigned integers.
 *
 * @param arg    Variadic argument list to extract the integer value.
 * @param format Format string being parsed.
 * @param state  Pointer to t_printf_state structure holding parsing state and flags.
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
 * Usage Example:
 *
 *   - printf("%u", 42);        // Output: '42'
 *
 *   - printf("%5u", 42);       // Output: '␣␣␣42' (right-justified in width 5)
 *
 *   - printf("%-5u", 42);      // Output: '42␣␣␣' (left-justified in width 5)
 *
 *   - printf("%.5u", 42);      // Output: '00042' (precision 5)
 *
 *   - printf("%05u", 42);      // Output: '00042' (zero-padded to width 5)
 *
 *   - printf("%8.5u", 42);         // Output: '␣␣␣␣␣00042' (width 8, precision 5)
 *
 *   - printf("%-8.5u", 42);        // Output: '00042␣␣␣␣␣' (left-justified, width 8, precision 5)
 *
 *   - printf("%.0u", 0);       // Output: '' (empty string if precision is 0 and value is 0)
 *
 *   - printf("%08u", 123);     // Output: '00000123' (zero-padded to width 8)
 *
 *   - printf("%u", -1);        // Output: '4294967295' (if argument is -1 cast to unsigned)
 */
void ft_handle_unsigned_integer_conversion(va_list arg, const char *format, t_printf_state *state)
{
    char *str;
    char *precision_str;
    int str_len;
    int padding;
    unsigned int num;

    if (format[state->format_pos] != 'u')
        return;
    num = va_arg(arg, unsigned int);
    str = ft_process_unsigned_integer(num, state);
    if (!str)
        return;
    precision_str = ft_apply_precision(str, state->precision, 0);
    free(str);
    if (!precision_str)
    {
        state->has_error = TRUE;
        return;
    }
    str_len = ft_strlen(precision_str);
    if (state->field_width > str_len)
        padding = state->field_width - str_len;
    else
        padding = 0;
    ft_print_formatted_conversion(precision_str, str_len, padding, state);
    free(precision_str);
}