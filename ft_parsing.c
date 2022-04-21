#include "ft_printf.h"

static void	ft_parsing_prefix(const char *format, t_data *data)
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

static void	ft_parsing_len_precision(va_list arg, char *format, t_data *data)
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

static void	ft_parsing_suffix(const char *format, t_data *data)
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

void	ft_parsing(va_list arg, char *format, t_data *data)
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
	ft_parsing_conversion(arg, format, data);
}
