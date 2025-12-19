#include "ft_printf.h"

/**
 * @brief Processes the input string according to the precision specified in the t_printf_state structure.
 *
 * @param str  The input string to be processed.
 * @param state Pointer to a t_printf_state structure that holds parsing state and flags.
 * @return A newly allocated string that has been processed according to
 *         the precision specified in the t_printf_state structure.
 *
 * @note If the input string is NULL, it is replaced with "(null)".
 */
static char *ft_process_string(char *str, t_printf_state *state)
{
	char *result;
	long i;
	long max_len;

	if (!str)
		str = "(null)";
	max_len = ft_strlen(str);
	result = (char *)malloc(sizeof(char) * (max_len + 1));
	if (!result)
	{
		state->has_error = TRUE;
		return (NULL);
	}
	i = 0;
	if (state->precision > -1 && max_len > state->precision)
		max_len = state->precision;
	while (i < max_len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/**
 * @brief Handles the '%s' conversion specifier for printing strings.
 *
 * @param arg    Variadic argument list to extract the string value.
 * @param format Format string being parsed.
 * @param state   Pointer to t_printf_state structure holding parsing state and flags.
 *
 * @note
 *
 * Flags and Modifiers:
 *
 *   - Field width and left-justification ('-') are supported.
 *
 *   - Precision limits the maximum number of characters printed from the string.
 *
 *   - Zero-padding ('0') is ignored; spaces are used for padding.
 *
 *   - If the string is shorter than the specified width, it is padded with spaces.
 *
 *   - If the string is longer than the specified precision, it is truncated.
 *
 *   - If the input string is NULL, it is replaced with "(null)".
 *
 * Usage Example:
 *
 *   - printf("%s", "abc");          // Output: the string 'abc'
 *
 *   - printf("%10s", "abc");        // Output: '       abc' (right-justified in width 10)
 *
 *   - printf("%-10s", "abc");       // Output: 'abc       ' (left-justified in width 10)
 *
 *   - printf("%.3s", "abcdef");     // Output: "abc"
 *
 *   - printf("%-10.4s", "abcdef");  // Output: "abcd      "
 */
void ft_handle_string_conversion(va_list arg, const char *format, t_printf_state *state)
{
	char *str;
	long spaces_count;
	int str_len;

	if (format[state->format_pos] == 's')
	{
		str = ft_process_string(va_arg(arg, char *), state);
		if (!str)
			return;
		str_len = (int)ft_strlen(str);
		spaces_count = 0;
		if (state->field_width > str_len)
			spaces_count = state->field_width - str_len;
		if (!state->flag_minus)
		{
			while (spaces_count--)
				state->printed_chars += write(1, " ", 1);
		}
		state->printed_chars += write(1, str, str_len);
		if (state->flag_minus)
		{
			while (spaces_count--)
				state->printed_chars += write(1, " ", 1);
		}
		free(str);
	}
}
