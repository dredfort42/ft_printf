#include "ft_printf.h"

/**
 * @brief Parses prefix flags in the format string.
 *
 * @param format The format string being parsed.
 * @param state  Pointer to a t_printf_state struct holding parsing state and results.
 */
static void ft_parse_prefix(const char *format, t_printf_state *state)
{
	char *flag;

	flag = "-0# +";
	while (ft_strchr(flag, format[state->format_pos]))
	{
		if (format[state->format_pos] == '-')
			state->flag_minus = TRUE;
		else if (format[state->format_pos] == '0')
			state->flag_zero = TRUE;
		else if (format[state->format_pos] == '#')
			state->flag_hash = TRUE;
		else if (format[state->format_pos] == ' ')
			state->flag_space = TRUE;
		else if (format[state->format_pos] == '+')
			state->flag_plus = TRUE;
		state->format_pos++;
	}
}

/**
 * @brief Parses field width from the format string.
 *
 * @param arg    The variadic argument list to extract values from.
 * @param format The format string being parsed.
 * @param state  Pointer to a t_printf_state struct holding parsing state and results.
 *
 * @note If the field width is specified as '*', it retrieves the value from the argument list.
 *       If the retrieved field width is negative, it sets the left-justify flag (-) and makes
 *       the field width positive.
 */
static void ft_parse_field_width(va_list arg, const char *format, t_printf_state *state)
{
	if (format[state->format_pos] == '*')
	{
		state->field_width = va_arg(arg, int);
		if (state->field_width < 0)
		{
			state->flag_minus = TRUE;
			state->field_width *= -1;
		}
		state->format_pos++;
	}
	else if (format[state->format_pos] >= '0' && format[state->format_pos] <= '9')
		state->field_width = ft_atoi(&format[state->format_pos]);
}

/**
 * @brief Parses precision from the format string.
 *
 * @param arg    The variadic argument list to extract values from.
 * @param format The format string being parsed.
 * @param state  Pointer to a t_printf_state struct holding parsing state and results.
 *
 * @note If the precision is specified as '*', it retrieves the value from the argument list.
 *       If the retrieved precision is negative, it sets precision to -1 (indicating no precision).
 */
static void ft_parse_precision(va_list arg, const char *format, t_printf_state *state)
{
	if (format[state->format_pos] == '.')
	{
		state->precision = 0;
		state->format_pos++;
		if (format[state->format_pos] == '*')
		{
			state->precision = va_arg(arg, int);
			state->format_pos++;
		}
		else
		{
			state->precision = ft_atoi(&format[state->format_pos]);
			if (state->precision < 0)
				state->precision = -1;
		}
	}
}

/**
 * @brief Handles the conversion specifiers in the format string.
 *
 * @param arg    The variadic argument list to extract values from.
 * @param format The format string being parsed.
 * @param state   Pointer to a t_printf_state struct holding parsing state and results.
 */
static void ft_handle_conversions(va_list arg, const char *format, t_printf_state *state)
{
	ft_handle_percent_conversion(format, state);
	ft_handle_char_conversion(arg, format, state);
	ft_handle_string_conversion(arg, format, state);
	ft_handle_pointer_conversion(arg, format, state);
	ft_handle_signed_integer_conversion(arg, format, state);
	ft_handle_unsigned_integer_conversion(arg, format, state);
	// ft_handle_hex_conversion(arg, format, state);

	// ft_conversion_diu(arg, format, data);
	// ft_conversion_x(arg, format, data);
	// ft_conversion_X(arg, format, data);
	// ft_conversion_n(arg, format, data);
	// ft_conversion_f(arg, format, data);
	// ft_conversion_e(arg, format, data);
	// ft_conversion_g(arg, format, data);
}

/**
 * @brief Parses the format string to extract flags, precision, and conversion specifiers.
 *
 * @param arg A va_list containing the variable arguments to be formatted.
 * @param format A character pointer representing the format string.
 * @param state A pointer to the t_printf_state structure containing formatting state.
 * @param flags A pointer to the t_printf_flags structure containing formatting flags.
 */
void ft_parsing(va_list arg, const char *format, t_printf_state *state)
{
	char *conversions;

	conversions = "cspdiuxX%";
	ft_parse_prefix(format, state);
	while (format[state->format_pos] && !ft_strchr(conversions, format[state->format_pos]))
	{
		ft_parse_field_width(arg, format, state);
		ft_parse_precision(arg, format, state);
		if (format[state->format_pos] == 'l')
		{
			state->format_pos++;
			if (format[state->format_pos] == 'l')
				state->format_pos++;
		}
		else if (format[state->format_pos] == 'h')
		{
			state->format_pos++;
			if (format[state->format_pos] == 'h')
				state->format_pos++;
		}
		state->format_pos++;
	}

	ft_handle_conversions(arg, format, state);
}
