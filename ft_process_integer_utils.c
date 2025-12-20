#include "ft_printf.h"

/**
 * @brief Applies precision to the numeric string representation.
 *
 * @param num_str   The original numeric string.
 * @param precision The precision value to apply.
 * @param is_negative Flag indicating if the number is negative.
 * @return A newly allocated string with applied precision.
 */
char *ft_apply_precision_to_number(char *num_str, int precision, int is_negative)
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
 * @param state     Pointer to t_printf_state structure holding parsing state and flags.
 */
void ft_print_formatted_number(char *str, int str_len, int padding, t_printf_state *state)
{
    char padding_char;

    if (state->flag_zero && !state->flag_minus && state->precision < 0)
        padding_char = '0';
    else
        padding_char = ' ';
    if (!state->flag_minus && padding_char == ' ')
        ft_print_padding(padding, ' ', state);
    if (padding_char == '0' && !state->flag_minus)
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
