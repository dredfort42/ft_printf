#include "ft_printf.h"

/**
 * @brief Resets all formatting flags to their default state.
 *
 * @param state Pointer to a t_printf_state struct to reset flags.
 */
static void ft_reset_flags(t_printf_state *state)
{
	state->flag_minus = FALSE;
	state->flag_zero = FALSE;
	state->precision = -1;
	state->field_width = 0;
	state->flag_hash = FALSE;
	state->flag_space = FALSE;
	state->flag_plus = FALSE;
}

/**
 * @brief Processes the format string and handles conversion specifiers.
 *
 * @param format The format string being parsed.
 * @param arg    The variadic argument list to extract values from.
 * @param state  Pointer to a t_printf_state struct holding parsing state and results.
 * @return The total number of characters printed, or ERROR on failure.
 */
static int ft_process(const char *format, va_list arg,
					  t_printf_state *state)
{
	while (format[state->format_pos] && !state->has_error)
	{
		if (format[state->format_pos] == '%')
		{
			ft_reset_flags(state);
			state->format_pos++;
			ft_parsing(arg, format, state);
		}
		else
		{
			write(1, &format[state->format_pos], 1);
			state->printed_chars++;
		}
		state->format_pos++;
	}
	if (state->has_error)
		return (ERROR);
	else
		return (state->printed_chars);
}

/**
 * @brief The ft_printf function is a custom implementation of the standard printf function in C.
 * It formats and prints data to the standard output based on a format string and a variable number
 * of arguments.
 *
 * @param format A constant character pointer representing the format string that specifies how to format
 * the subsequent arguments.
 * @return The function returns the total number of characters printed to the standard output. If an error
 * occurs during processing, it returns -1.
 */
int ft_printf(const char *format, ...)
{
	va_list arg;
	t_printf_state *state;
	int printed_chars;

	if (!format)
		return (ERROR);
	state = (t_printf_state *)malloc(sizeof(t_printf_state));
	if (!state)
		return (ERROR);
	state->printed_chars = 0;
	state->format_pos = 0;
	state->has_error = FALSE;
	va_start(arg, format);
	printed_chars = ft_process(format, arg, state);
	va_end(arg);
	if (state->has_error)
		printed_chars = ERROR;
	free(state);
	return (printed_chars);
}