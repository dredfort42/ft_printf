#include "ft_printf.h"

/**
 * @brief Processes the signed integer according to flags and returns its string representation.
 *
 * @param num   The signed integer to be processed.
 * @param state Pointer to t_printf_state structure holding parsing state and flags.
 * @return A newly allocated string representing the signed integer with applied flags.
 */
static char *ft_process_signed_integer(int num, t_printf_state *state)
{
    char *result;
    char *temp;

    result = ft_itoa(num);
    if (!result)
        return (NULL);
    if (num >= 0)
    {
        temp = NULL;
        if (state->flag_plus)
            temp = ft_strjoin("+", result);
        else if (state->flag_space)
            temp = ft_strjoin(" ", result);
        if (temp)
        {
            free(result);
            result = temp;
        }
    }
    return (result);
}

/**
 * @brief Handles the '%d' and '%i' conversion specifiers for signed integers.
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
 *   - The '+' flag forces a sign (+ or -) to be used for the number.
 *
 *   - The ' ' (space) flag inserts a space before positive numbers if no sign is going to be written.
 *
 * Usage Example:
 *
 *  - printf("%d", 42);        // Output: '42'
 *
 *   - printf("%+d", 42);       // Output: '+42'
 *
 *   - printf("% d", 42);       // Output: '␣42'
 *
 *   - printf("%5d", 42);       // Output: '␣␣␣42' (right-justified in width 5)
 *
 *   - printf("%-5d", 42);      // Output: '42␣␣␣' (left-justified in width 5)
 *
 *   - printf("%.5d", 42);      // Output: '00042' (precision 5)
 *
 *   - printf("%05d", 42);      // Output: '00042' (zero-padded to width 5)
 *
 *   - printf("%-+8.5d", 42);    // Output: '+00042␣␣' (left-justified, width 8, precision 5)
 *
 *   - printf("%i", -42);       // Output: '-42'
 *
 *   - printf("%+i", -42);      // Output: '-42'
 *
 *   - printf("% d", -42);      // Output: '-42'
 *
 *   - printf("%5i", -42);      // Output: '␣␣-42' (right-justified in width 5)
 *
 *   - printf("%-5i", -42);     // Output: '-42␣␣' (left-justified in width 5)
 *
 *   - printf("%.5i", -42);     // Output: '-00042' (precision 5)
 *
 *   - printf("%05i", -42);     // Output: '-0042' (zero-padded to width 5)
 *
 *   - printf("%-+8.5i", -42);   // Output: '-00042␣␣' (left-justified, width 8, precision 5)
 */
void ft_handle_signed_integer_conversion(va_list arg, const char *format, t_printf_state *state)
{
    char *str;
    char *precision_str;
    int str_len;
    int padding;
    int num;

    if (format[state->format_pos] != 'd' && format[state->format_pos] != 'i')
        return;
    num = va_arg(arg, int);
    str = ft_process_signed_integer(num, state);
    if (!str)
        return ((void)(state->has_error = TRUE));
    precision_str = ft_apply_precision(str, state->precision, num < 0);
    free(str);
    if (!precision_str)
        return ((void)(state->has_error = TRUE));
    str_len = (int)ft_strlen(precision_str);
    if (state->field_width > str_len)
        padding = state->field_width - str_len;
    else
        padding = 0;
    ft_print_formatted_conversion(precision_str, str_len, padding, state);
    free(precision_str);
}
