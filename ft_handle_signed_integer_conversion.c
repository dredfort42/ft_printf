#include "ft_printf.h"

/**
 * @brief Applies precision to the numeric string representation.
 *
 * @param num_str   The original numeric string.
 * @param precision The precision value to apply.
 * @param is_negative Flag indicating if the number is negative.
 * @return A newly allocated string with applied precision.
 */
static char *ft_apply_precision_to_number(char *num_str, int precision, int is_negative)
{
    char *result;
    char *digits;
    int digits_len;
    int zeros_needed;
    int i;

    if (is_negative)
        is_negative = 1;
    digits = num_str + is_negative;
    digits_len = ft_strlen(digits);
    if (precision <= digits_len)
        return (ft_strdup(num_str));
    zeros_needed = precision - digits_len;
    result = (char *)malloc(1 + is_negative + zeros_needed + digits_len + 1);
    if (!result)
        return (NULL);
    i = 0;
    if (is_negative)
        result[i++] = '-';
    while (zeros_needed--)
        result[i++] = '0';
    ft_strlcpy(result + i, digits, digits_len + 1);
    return (result);
}

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
    {
        state->has_error = TRUE;
        return (NULL);
    }
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
 * @brief Prints padding characters.
 *
 * @param count     The number of padding characters to print.
 * @param pad_char  The character to use for padding (' ' or '0').
 * @param state     Pointer to t_printf_state structure holding parsing state and flags.
 */
static void ft_print_padding(int count, char pad_char, t_printf_state *state)
{
    while (count-- > 0)
        state->printed_chars += write(1, &pad_char, 1);
}

/**
 * @brief Prints the formatted number string with padding and alignment.
 *
 * @param str       The numeric string to print.
 * @param str_len   The length of the numeric string.
 * @param padding   The amount of padding needed.
 * @param pad_char  The character to use for padding (' ' or '0').
 * @param state     Pointer to t_printf_state structure holding parsing state and flags.
 */
static void ft_print_formatted_number(char *str, int str_len, int padding,
                                      char pad_char, t_printf_state *state)
{
    if (!state->flag_minus && pad_char == ' ')
        ft_print_padding(padding, ' ', state);
    if (pad_char == '0' && !state->flag_minus)
    {
        if (str[0] == '+' || str[0] == '-' || str[0] == ' ')
            state->printed_chars += write(1, str, 1);
        ft_print_padding(padding, '0', state);
        state->printed_chars += write(1, str + 1, str_len - 1);
    }
    else
        state->printed_chars += write(1, str, str_len);
    if (state->flag_minus)
        ft_print_padding(padding, ' ', state);
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
    char pad_char;
    int num;

    if (format[state->format_pos] != 'd' && format[state->format_pos] != 'i')
        return;
    num = va_arg(arg, int);
    str = ft_process_signed_integer(num, state);
    if (!str)
        return;
    precision_str = ft_apply_precision_to_number(str, state->precision, num < 0);
    free(str);
    if (!precision_str)
    {
        state->has_error = TRUE;
        return;
    }
    str_len = ft_strlen(precision_str);
    padding = (state->field_width > str_len) ? state->field_width - str_len : 0;
    pad_char = (state->flag_zero && !state->flag_minus && state->precision < 0) ? '0' : ' ';
    ft_print_formatted_number(precision_str, str_len, padding, pad_char, state);
    free(precision_str);
}