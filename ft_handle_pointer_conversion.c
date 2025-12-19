#include "ft_printf.h"

/**
 * @brief Calculates the number of digits needed to represent the pointer value.
 *
 * @param p     The pointer value.
 * @return The number of digits required for the pointer representation.
 */
static short ft_pointer_digits_count(unsigned long long p)
{
	short digits_count;

	digits_count = 0;
	while (p)
	{
		p /= 16;
		digits_count++;
	}
	return (digits_count);
}

/**
 * @brief Processes the pointer value into a hexadecimal string representation.
 *
 * @param p     The pointer value to be processed.
 * @param state Pointer to a t_printf_state structure that holds parsing state and flags.
 * @return A newly allocated string representing the pointer in hexadecimal format.
 */
static char *ft_process_pointer(unsigned long long p, t_printf_state *state)
{
	char *result;
	short digits_count;
	char *hex;

	hex = "0123456789abcdef";
	digits_count = ft_pointer_digits_count(p) + 2;
	result = (char *)malloc(sizeof(char) * (digits_count + 1));
	if (!result)
	{
		state->has_error = TRUE;
		return (NULL);
	}
	result[digits_count--] = '\0';
	while (p)
	{
		result[digits_count] = hex[(p % 16)];
		p /= 16;
		digits_count--;
	}
	result[digits_count--] = 'x';
	result[digits_count] = '0';
	return (result);
}

/**
 * @brief Handles the '%p' conversion specifier for printing pointer (memory address) values in an
 *        implementation-defined hexadecimal format, typically prefixed with '0x'.
 *
 * @param arg    Variadic argument list to extract the pointer value.
 * @param format Format string being parsed.
 * @param state  Pointer to t_printf_state structure holding parsing state and flags.
 *
 * @note
 *
 * Flags and Modifiers:
 *
 *   - Field width and left-justification ('-') are supported.
 *
 *   - Standard flags '+', '#', '0', space and precision are ignored for '%p'.
 *
 *   - Output format (e.g., '0x' prefix, lowercase hex) is implementation-defined.
 *
 * Usage Example:
 *
 *   - printf("%p", ptr);     // Output: '0x7ffee4bff618' (address of 'ptr')
 *
 *   - printf("%20p", ptr);   // Output: '         0x7ffee4bff618' (right-justified in width 20)
 *
 *   - printf("%-20p", ptr);  // Output: '0x7ffee4bff618         ' (left-justified in width 20)
 */
void ft_handle_pointer_conversion(va_list arg, const char *format, t_printf_state *state)
{
	char *str;
	long spaces_count;
	int str_len;

	if (format[state->format_pos] == 'p')
	{
		str = ft_process_pointer(va_arg(arg, unsigned long long), state);
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
