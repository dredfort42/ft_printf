#include "ft_printf.h"

/**
 * @brief Resets the flag fields in the t_data structure to their default values.
 *
 * @param data A pointer to the t_data structure to reset.
 */
static void ft_reset_flags(t_data *data)
{
	data->space = 0;
	data->minus = 0;
	data->plus = 0;
	data->sharp = 0;
	data->zero = 0;
	data->len = 0;
	data->precision = -1;
	data->l = 0;
	data->ll = 0;
	data->h = 0;
	data->hh = 0;
}

/**
 * @brief Allocates and initializes a new t_data structure.
 *
 * @return A pointer to the newly allocated t_data structure, or NULL if allocation fails.
 */
static t_data *ft_new_data()
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->error = 0;
	data->counter = 0;
	data->index = 0;
	ft_reset_flags(data);
	return (data);
}

/**
 * @brief Processes the format string and handles formatting and printing.
 *
 * @param arg A va_list containing the variable arguments to be formatted.
 * @param format A character pointer representing the format string.
 * @param data A pointer to the t_data structure containing formatting information.
 * @return The total number of characters printed, or ERROR if an error occurs.
 */
static int ft_process(va_list arg, char *format, t_data *data)
{
	while (format[data->index] && !data->error)
	{
		if (format[data->index] == '%')
		{
			ft_reset_flags(data);
			data->index++;
			ft_parsing(arg, format, data);
		}
		else
		{
			write(1, &format[data->index], 1);
			data->counter++;
		}
		data->index++;
	}
	if (data->error)
		return (ERROR);
	else
		return (data->counter);
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
	t_data *data;
	int char_number;

	if (!format)
		return (ERROR);
	data = ft_new_data();
	if (!data)
		return (ERROR);
	va_start(arg, format);
	char_number = ft_process(arg, (char *)format, data);
	va_end(arg);
	free(data);
	return (char_number);
}
