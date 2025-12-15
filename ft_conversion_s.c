#include "ft_printf.h"

/**
 * @brief Processes a regular string for the 's' conversion specifier.
 *
 * @param str  The input string to be processed.
 * @param data Pointer to a t_data structure that holds parsing state and flags.
 * @return A newly allocated string that has been processed according to
 *         the precision specified in the t_data structure.
 *
 * @note If the input string is NULL, it is replaced with "(null)".
 */
static char *ft_processing_s(char *str, t_data *data)
{
	char *rtn;
	long i;
	long max_len;

	if (!str)
		str = "(null)";
	max_len = ft_strlen(str);
	rtn = ft_memory_p(max_len + 1, data);
	i = 0;
	if (data->precision > -1 && max_len > data->precision)
		max_len = data->precision;
	while (i < max_len)
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

/**
 * @brief Writes a wide character string to standard output.
 *
 * @param wcstr The wide character string to be written.
 * @param data  Pointer to a t_data structure that holds parsing state and flags.
 */
static void ft_write_wcstr(wchar_t *wcstr, t_data *data)
{
	int i;

	i = 0;
	while (wcstr[i])
		ft_wchar_writer(wcstr[i++], data);
}

/**
 * @brief Processes a wide character string for the 'S' conversion specifier.
 *
 * @param wcstr The input wide character string to be processed.
 * @param data  Pointer to a t_data structure that holds parsing state and flags.
 *
 * @note If the input wide character string is NULL, it is replaced with
 *       a representation of "(null)" in wide characters.
 */
static void ft_processing_ls(wchar_t *wcstr, t_data *data)
{
	long spaces_count;
	int i;
	char *spacer;
	short empty;

	empty = 0;
	spacer = ft_c_space_str(data);
	spaces_count = 0;
	i = 0;
	if (!wcstr)
		wcstr = ft_null_str(data, &empty);
	while (wcstr[i])
		i++;
	if (data->len > i)
		spaces_count = data->len - i;
	if (!data->minus)
		while (spaces_count--)
			data->counter += write(1, spacer, 1);
	ft_write_wcstr(wcstr, data);
	if (data->minus)
		while (spaces_count--)
			data->counter += write(1, spacer, 1);
	if (empty)
		free(wcstr);
}

/**
 * @brief Handles the string conversion with padding and alignment.
 *
 * @param str  The string to be printed.
 * @param data Pointer to a t_data structure that holds parsing state and flags.
 */
static void ft_handle_string_conversion(char *str, t_data *data)
{
	long spaces_count;
	char *space;

	space = ft_c_space_str(data);
	spaces_count = 0;
	if (data->len > ft_strlen(str))
		spaces_count = data->len - ft_strlen(str);
	if (!data->minus)
	{
		while (spaces_count--)
			data->counter += write(1, space, 1);
	}
	data->counter += write(1, str, ft_strlen(str));
	if (data->minus)
	{
		while (spaces_count--)
			data->counter += write(1, space, 1);
	}
	free(str);
}

/**
 * @brief Handles the 's' conversion specifier in the format string.
 *
 * @param arg    The variadic argument list to extract values from.
 * @param format The format string being parsed.
 * @param data   Pointer to a t_data structure that holds parsing state and flags.
 */
void ft_conversion_s(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 's')
	{
		if (data->len < 0)
		{
			data->minus = 1;
			data->len *= -1;
		}
		if (!data->l)
			ft_handle_string_conversion(ft_processing_s(va_arg(arg, char *), data), data);
		else
			ft_processing_ls(va_arg(arg, wint_t *), data);
	}
}
