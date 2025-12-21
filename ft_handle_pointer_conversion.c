#include "ft_printf.h"

/**
 * @brief Processes the pointer value to create its string representation in hexadecimal format
 *        prefixed with '0x'.
 *
 * @param ptr   The pointer value to be processed.
 * @param state Pointer to t_printf_state structure holding parsing state and flags.
 * @return A newly allocated string representing the pointer in hexadecimal format.
 */
static char *ft_porocess_pointer(unsigned long long ptr, t_printf_state *state)
{
	char *hex_str;
	char *result;

	hex_str = ft_ull_to_hex(ptr, state, 0);
	if (!hex_str)
		return NULL;
	result = ft_strjoin("0x", hex_str);
	free(hex_str);
	if (!result)
		return NULL;
	return result;
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
	str = ft_porocess_pointer(va_arg(arg, unsigned long long), state);
	if (!str)
		return;
	str_len = (int)ft_strlen(str);
	spaces_count = 0;
	if (state->field_width > str_len)
		spaces_count = state->field_width - str_len;
	if (!state->flag_minus)
		while (spaces_count--)
			state->printed_chars += write(1, " ", 1);
	state->printed_chars += write(1, str, str_len);
	if (state->flag_minus)
		while (spaces_count--)
			state->printed_chars += write(1, " ", 1);
	free(str);
}
