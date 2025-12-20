#include "ft_printf.h"

/**
 * @brief Handles the '%c' conversion specifier for printing characters.
 *
 * @param arg    Variadic argument list to extract the character value.
 * @param format Format string being parsed.
 * @param state   Pointer to t_printf_state structure holding parsing state and flags.
 *
 * @note
 *
 * Flags and Modifiers:
 *
 *   - Field width and left-justification ('-') are supported.
 *
 *   - Standard flags '+', '#', '0', space and precision are ignored for '%c'.
 *
 * Usage Example:
 *
 *   - printf("%c", 'A');    // Output: 'A'
 *
 *   - printf("%5c", 'A');   // Output: '␣␣␣␣A' (right-justified in width 5)
 *
 *   - printf("%-5c", 'A');  // Output: 'A␣␣␣␣' (left-justified in width 5)
 */
void ft_handle_char_conversion(va_list arg, const char *format, t_printf_state *state)
{
	char c;

	if (format[state->format_pos] != 'c')
		return;
	c = (char)va_arg(arg, int);
	if (state->flag_minus)
		state->flag_zero = FALSE;
	if (!state->flag_minus)
		while (state->field_width-- - 1 > 0)
			state->printed_chars += write(1, " ", 1);
	state->printed_chars += write(1, &c, 1);
	if (state->flag_minus)
		while (state->field_width-- - 1 > 0)
			state->printed_chars += write(1, " ", 1);
}