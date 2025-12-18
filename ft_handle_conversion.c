#include "ft_printf.h"

/**
 * @brief Handles the '%%' conversion specifier for printing a percent sign.
 *
 * The '%%' format specifier prints a literal percent character ('%').
 *
 * @param format Format string being parsed.
 * @param data   Pointer to t_data structure holding parsing state and flags.
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
 *   - printf("%%");         // Output: '%'
 *
 *   - printf("%5%%");      // Output: '    %'`
 *
 *   - printf("%-5%%");     // Output: '%    '
 */
static void ft_conversion_percent(const char *format, t_data *data)
{
	if (format[data->index] == '%')
	{
		data->precision = -1;
		if (data->len < 0)
		{
			data->minus = 1;
			data->len *= -1;
		}
		if (data->minus)
			data->zero = 0;
		if (!data->minus)
			while (data->len-- - 1 > 0)
				data->counter += write(1, ft_c_space_str(data), 1);
		data->counter += write(1, "%", 1);
		if (data->minus)
			while (data->len-- - 1 > 0)
				data->counter += write(1, ft_c_space_str(data), 1);
	}
}

/**
 * @brief Handles the conversion specifiers in the format string.
 *
 * @param arg    The variadic argument list to extract values from.
 * @param format The format string being parsed.
 * @param data   Pointer to a t_data struct holding parsing state and results.
 *
 * @note This function calls the appropriate conversion function based on the
 *       conversion specifier found in the format string.
 */
void ft_handle_conversion(va_list arg, char *format, t_data *data)
{
	ft_conversion_percent(format, data);
	ft_conversion_c(arg, format, data);
	ft_conversion_s(arg, format, data);
	ft_conversion_p(arg, format, data);
	ft_conversion_diu(arg, format, data);
	ft_conversion_x(arg, format, data);
	ft_conversion_X(arg, format, data);
	ft_conversion_n(arg, format, data);
	ft_conversion_f(arg, format, data);
	ft_conversion_e(arg, format, data);
	ft_conversion_g(arg, format, data);
}
