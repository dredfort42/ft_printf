#include "ft_printf.h"

/**
 * @brief Handles the '%%' conversion specifier for printing a percent sign.
 *
 * @param format Format string being parsed.
 * @param state   Pointer to t_printf_state structure holding parsing state and flags.
 *
 * @note
 *
 * Flags and Modifiers:
 *
 *   - Field width and left-justification ('-') are supported.
 *
 *   - Zero-padding ('0') is ignored if left-justification is set; spaces are used for padding.
 *
 *   - Precision is ignored.
 *
 *   - If the width is greater than 1, the output is padded with spaces to the specified width.
 *
 * Usage Example:
 *
 *   - printf("%%");        // Output: '%'
 *
 *   - printf("%5%%");      // Output: '    %'
 *
 *   - printf("%-5%%");     // Output: '%    '
 */
void ft_handle_percent_conversion(const char *format, t_printf_state *state)
{
	if (format[state->format_pos] == '%')
	{
		state->precision = -1;
		if (state->field_width < 0)
		{
			state->flag_minus = TRUE;
			state->field_width *= -1;
		}
		if (state->flag_minus)
			state->flag_zero = FALSE;
		if (!state->flag_minus)
			while (state->field_width-- - 1 > 0)
				state->printed_chars += write(1, " ", 1);
		state->printed_chars += write(1, "%", 1);
		if (state->flag_minus)
			while (state->field_width-- - 1 > 0)
				state->printed_chars += write(1, " ", 1);
	}
}