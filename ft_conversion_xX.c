#include "ft_printf.h"

static short	ft_digits_count_xX(unsigned long long num, t_data *data)
{
	short	digits_count;

	digits_count = ft_digits_in_number(num, 16);
	if (!num)
		digits_count = 1;
	if (data->sharp && num)
	{
		if (digits_count < data->precision)
			digits_count = data->precision;
		if (data->precision != -1)
			data->precision += 1;
		if (num)
			digits_count += 2;
	}
	return (digits_count);
}

static char	*ft_processing_x(unsigned long long num, t_data *data)
{
	char	*rtn;
	short	digits_count;

	digits_count = ft_digits_count_xX(num, data);
	rtn = ft_memory_p((digits_count + 1), data);
	rtn[digits_count--] = '\0';
	if (!num)
	{
		rtn[0] = '0';
		rtn[1] = '\0';
		return (rtn);
	}
	ft_hex(rtn, num, &digits_count);
	if (data->sharp)
	{
		while (digits_count > 1)
			rtn[digits_count--] = '0';
		rtn[1] = 'x';
		rtn[0] = '0';
	}
	return (rtn);
}

void	ft_conversion_x(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'x')
	{
		if (data->l)
			ft_magic_diuxX(ft_processing_x(
					va_arg(arg, unsigned long), data), data);
		else if (data->ll)
			ft_magic_diuxX(ft_processing_x(
					va_arg(arg, unsigned long long), data), data);
		else if (data->h)
			ft_magic_diuxX(ft_processing_x(
					(unsigned short)va_arg(arg, unsigned int), data), data);
		else if (data->hh)
			ft_magic_diuxX(ft_processing_x(
					(unsigned char)va_arg(arg, unsigned int), data), data);
		else
			ft_magic_diuxX(ft_processing_x(
					va_arg(arg, unsigned int), data), data);
	}
}

void	ft_conversion_X(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'X')
	{
		if (data->l)
			ft_magic_diuxX(ft_capitalizer(
					ft_processing_x(
						va_arg(arg, unsigned long), data)), data);
		else if (data->ll)
			ft_magic_diuxX(ft_capitalizer(
					ft_processing_x(
						va_arg(arg, unsigned long long), data)), data);
		else if (data->h)
			ft_magic_diuxX(ft_capitalizer(ft_processing_x(
						(unsigned short)va_arg(arg, unsigned long long),
						data)), data);
		else if (data->hh)
			ft_magic_diuxX(ft_capitalizer(ft_processing_x(
						(unsigned char) va_arg(arg, unsigned long long),
						data)), data);
		else
			ft_magic_diuxX(ft_capitalizer(ft_processing_x(
						va_arg(arg, unsigned int), data)), data);
	}
}
