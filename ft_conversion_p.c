#include "ft_printf.h"

/**
 * @brief Calculates the number of digits needed to represent the pointer value.
 *
 * @param p    The pointer value.
 * @param data Pointer to a t_data structure that holds parsing state and flags.
 * @return The number of digits required for the pointer representation.
 */
static short ft_digits_count_p(unsigned long long p, t_data *data)
{
	short digits_count;

	digits_count = 0;
	if (!p)
	{
		digits_count = 1;
		if (data->precision > 0)
			digits_count = data->precision;
	}
	digits_count += 2 + ft_digits_in_number(p, 16);
	if (data->precision > 2 + ft_digits_in_number(p, 16))
		digits_count = data->precision + 2;
	return (digits_count);
}

/**
 * @brief Processes the pointer value for the 'p' conversion specifier.
 *
 * @param p    The pointer value to be processed.
 * @param data Pointer to a t_data structure that holds parsing state and flags.
 * @return A newly allocated string representing the pointer in hexadecimal format.
 */
static char *ft_processing_p(unsigned long long p, t_data *data)
{
	char *rtn;
	short digits_count;

	digits_count = ft_digits_count_p(p, data);
	rtn = ft_memory_p((digits_count + 1), data);
	rtn[digits_count--] = '\0';
	if (!p && data->precision == 0)
		rtn[digits_count] = '\0';
	else if (!p && data->precision < 0)
		rtn[digits_count] = '0';
	ft_hex(rtn, p, &digits_count);
	if (data->precision > 0 && !p)
	{
		while (digits_count)
			rtn[digits_count--] = '0';
	}
	rtn[1] = 'x';
	rtn[0] = '0';
	return (rtn);
}
/**
 * @brief Handles the 'p' conversion specifier in the format string.
 *
 * @param str  The processed pointer string to be printed.
 * @param data Pointer to a t_data structure that holds parsing state and flags.
 */
static void ft_handle_pointer_conversion(char *str, t_data *data)
{
	short len;

	len = ft_strlen(str);
	if (!data->len)
		data->minus = 0;
	else if (data->len < 0)
	{
		data->minus = 1;
		data->len *= -1;
	}
	if (!data->minus)
		while (data->len-- > len)
			data->counter += write(1, " ", 1);
	data->counter += write(1, str, ft_strlen(str));
	if (data->minus)
		while (data->len-- > len)
			data->counter += write(1, " ", 1);
	free(str);
}

/**
 * @brief Handles the '%p' conversion specifier for printing pointer values.
 *
 * The '%p' format specifier prints a pointer (memory address) in an
 * implementation-defined hexadecimal format, typically prefixed with '0x'.
 *
 * @param arg    Variadic argument list to extract the pointer value.
 * @param format Format string being parsed.
 * @param data   Pointer to t_data structure holding parsing state and flags.
 *
 * @note
 *
 * Flags and Modifiers:
 *
 *   - Standard flags ('+', '#', '0', space) are ignored for '%p'.
 *
 *   - Field width and left-justification ('-') are supported
 *
 *   - Precision is ignored.
 *
 *   - Output format (e.g., '0x' prefix, lowercase hex) is implementation-defined.
 *
 * Usage Example:
 *
 *   - printf("%p", ptr); // Output: 0x7ffee4bff618 (address of 'ptr')
 *
 *   - printf("%20p", ptr);   // Right-justified in width 20
 *
 *   - printf("%-20p", ptr);  // Left-justified in width 20
 */
void ft_conversion_p(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'p')
		ft_handle_pointer_conversion(
			ft_processing_p(
				va_arg(arg, unsigned long long), data),
			data);
}
