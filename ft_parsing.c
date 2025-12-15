#include "ft_printf.h"

/**
 * @brief Parses format flags from a format string and updates the data structure.
 *
 * This function iterates over the format string starting at the current index
 * (data->index) and checks for valid format flags (' ', '-', '+', '#', '0').
 * For each flag found, it sets the corresponding field in the t_data structure
 * to 1, indicating that the flag is present. The index is incremented for each
 * flag processed, so that after the function returns, data->index points to the
 * first character in the format string that is not a flag.
 *
 * @param format The format string to parse.
 * @param data   Pointer to a t_data structure that holds parsing state and flags.
 */
static void ft_parsing_prefix(const char *format, t_data *data)
{
	while (ft_is_flag(format[data->index]))
	{
		if (format[data->index] == ' ')
			data->space = 1;
		else if (format[data->index] == '-')
			data->minus = 1;
		else if (format[data->index] == '+')
			data->plus = 1;
		else if (format[data->index] == '#')
			data->sharp = 1;
		else if (format[data->index] == '0')
			data->zero = 1;
		data->index++;
	}
}

/**
 * @brief Parses the length and precision specifiers from a format string.
 *
 * @param arg    The variadic argument list to extract values from when '*' is used.
 * @param format The format string being parsed.
 * @param data   Pointer to a t_data struct holding parsing state and results.
 *
 * @note The function updates the 'len' and 'precision' fields of the provided t_data struct.
 *       - If a '*' is encountered, the corresponding value is read from the variadic arguments.
 *       - If a digit is encountered, the value is parsed as a number from the format string.
 *       - If a '.' is encountered, the function parses the precision value, supporting both
 *         '*' and numeric values after the dot.
 */
static void ft_parsing_len_precision(va_list arg, char *format, t_data *data)
{
	if (format[data->index] == '*')
	{
		data->len = 0;
		data->len = va_arg(arg, int);
	}
	else if (format[data->index] >= '0' && format[data->index] <= '9')
	{
		data->len = 0;
		ft_read_number(format, data, &data->len);
	}
	else if (format[data->index] == '.')
	{
		data->precision = 0;
		data->index++;
		if (format[data->index] == '*')
		{
			data->precision = 0;
			data->precision = va_arg(arg, int);
		}
		else
		{
			data->precision = 0;
			ft_read_number(format, data, &data->precision);
		}
	}
}

/**
 * @brief Parses length modifiers from the format string and updates the data structure.
 *
 * This function checks for length modifiers ('l', 'll', 'h', 'hh') in the format string
 * starting at the current index (data->index). It sets the corresponding fields in the
 * t_data structure to indicate which length modifier is present. The index is incremented
 * appropriately based on whether a single or double character length modifier is found.
 *
 * @param format The format string being parsed.
 * @param data   Pointer to a t_data structure that holds parsing state and flags.
 */
static void ft_parsing_suffix(const char *format, t_data *data)
{
	if (format[data->index] == 'l')
	{
		if (format[data->index + 1] == 'l')
		{
			data->ll = 1;
			data->index++;
		}
		else
			data->l = 1;
	}
	else if (format[data->index] == 'h')
	{
		if (format[data->index + 1] == 'h')
		{
			data->hh = 1;
			data->index++;
		}
		else
			data->h = 1;
	}
}

/**
 * @brief Parses the format string to extract flags, length, precision, and conversion specifiers.
 *
 * @param arg A va_list containing the variable arguments to be formatted.
 * @param format A character pointer representing the format string.
 * @param data A pointer to the t_data structure containing formatting information.
 */
void ft_parsing(va_list arg, char *format, t_data *data)
{
	ft_parsing_prefix(format, data);
	while (format[data->index] && !ft_is_conversion(format[data->index]))
	{
		ft_parsing_len_precision(arg, format, data);
		ft_parsing_suffix(format, data);
		data->index++;
	}
	if ((data->l + data->ll + data->h + data->hh) > 1)
		data->error = 1;
	ft_handle_conversion(arg, format, data);
}
