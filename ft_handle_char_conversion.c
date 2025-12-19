#include "ft_printf.h"

// /**
//  * @brief Writes a single character to the output and updates the counter.
//  *
//  * @param c    The character to write.
//  * @param data Pointer to a t_data structure that holds parsing state and flags.
//  */
// static void ft_processing_c(char c, t_data *data)
// {
// 	data->counter += write(1, &c, 1);
// }

// /**
//  * @brief Handles the 'c' and wide character conversion specifiers in the format string.
//  *
//  * This function processes the 'c' conversion specifier, applying any
//  * specified flags, width, and precision from the t_data structure.
//  * It updates the counter in the t_data structure to reflect the number
//  * of characters printed.
//  *
//  * @param arg    The variadic argument list to extract values from.
//  * @param data   Pointer to a t_data structure that holds parsing state and flags.
//  */
// static void ft_handle_char_conversion(va_list arg, t_data *data)
// {
// 	if (data->len < 0)
// 	{
// 		data->minus = 1;
// 		data->len *= -1;
// 	}
// 	if (!data->minus)
// 	{
// 		while (data->len-- > 1)
// 			data->counter += write(1, " ", 1);
// 	}
// 	if (!data->l)
// 		ft_processing_c(va_arg(arg, int), data);
// 	else
// 		ft_wchar_writer(va_arg(arg, wint_t), data);
// 	if (data->minus)
// 	{
// 		while (data->len-- > 1)
// 			data->counter += write(1, " ", 1);
// 	}
// }

/**
 * @brief Handles the '%c' conversion specifier for printing characters.
 *
 * The '%c' format specifier prints a single character. It can also print wide characters
 * when used with the 'l' length modifier (e.g., '%lc').
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
 *   - printf("%c", 'A');    // Output: A
 *
 *   - printf("%5c", 'A');   // Output: '    A' (right-justified in width 5)
 *
 *   - printf("%-5c", 'A');  // Output: 'A    ' (left-justified in width 5)
 */
void ft_handle_char_conversion(va_list arg, const char *format, t_printf_state *state)
{
	if (format[state->format_pos] == 'c')
	{
		char c;

		c = (char)va_arg(arg, int);
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
		state->printed_chars += write(1, &c, 1);
		if (state->flag_minus)
			while (state->field_width-- - 1 > 0)
				state->printed_chars += write(1, " ", 1);
	}
}