#include "ft_printf.h"

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
 *   - printf("%20p", ptr);   // Output: '␣␣␣␣␣␣␣␣␣␣␣0x7ffee4bff618' (right-justified in width 20)
 *
 *   - printf("%-20p", ptr);  // Output: '0x7ffee4bff618␣␣␣␣␣␣␣␣␣␣␣' (left-justified in width 20)
 */
void ft_handle_pointer_conversion(va_list arg, const char *format, t_printf_state *state)
{
	char *str;
	long spaces_count;
	int str_len;

	if (format[state->format_pos] != 'p')
		return;
	str = ft_strjoin("0x", ft_ull_to_hex(va_arg(arg, unsigned long long), state));
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
