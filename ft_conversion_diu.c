#include "ft_printf.h"

static char	*ft_processing_u(unsigned long long num, t_data *data)
{
	char	*rtn;
	short	digits_count;

	if (data->h)
		num = (unsigned short)num;
	if (data->hh)
		num = (unsigned char)num;
	digits_count = ft_digits_in_number(num, 10);
	if (!digits_count)
		digits_count = 1;
	rtn = ft_memory_p((digits_count + 1), data);
	rtn[digits_count--] = '\0';
	if (!num)
		rtn[digits_count--] = '0';
	while (num)
	{
		if (num > 9)
			rtn[digits_count] = '0' + (num % 10);
		else
			rtn[digits_count] = '0' + num;
		num /= 10;
		digits_count--;
	}
	return (rtn);
}

static char	*ft_processing_di(long long num, t_data *data)
{
	char	*rtn;
	short	num_is_negative;

	if (data->h)
		num = (short)num;
	if (data->hh)
		num = (char)num;
	num_is_negative = 0;
	if (num < 0)
	{
		num_is_negative = 1;
		num *= -1;
	}
	rtn = ft_processing_u(num, data);
	if (num_is_negative)
		rtn = ft_negative_di(rtn, data);
	if (!num_is_negative && data->plus)
		rtn = ft_positive_di(rtn, data);
	if (!num_is_negative && !data->plus && data->space)
		rtn = ft_space_di(rtn, data);
	return (rtn);
}

static void	ft_prepare_di_processing(va_list arg, t_data *data)
{
	if (!data->l && !data->ll)
		ft_magic_diuxX(ft_processing_di(va_arg(arg, int), data), data);
	if (data->l)
		ft_magic_diuxX(ft_processing_di(va_arg(arg, long), data), data);
	if (data->ll)
		ft_magic_diuxX(ft_processing_di(va_arg(arg, long long), data),
			data);
}

static void	ft_prepare_u_processing(va_list arg, t_data *data)
{
	if (!data->l && !data->ll)
		ft_magic_diuxX(ft_processing_u(va_arg(arg, unsigned), data),
			data);
	if (data->l)
		ft_magic_diuxX(ft_processing_u(va_arg(arg, unsigned long), data),
			data);
	if (data->ll)
		ft_magic_diuxX(ft_processing_u(va_arg(arg, unsigned long long),
				data), data);
}

void	ft_conversion_diu(va_list arg, const char *format, t_data *data)
{
	if (data->len < 0)
	{
		data->minus = 1;
		data->len *= -1;
	}
	if (data->minus)
		data->zero = 0;
	if (format[data->index] == 'd' || format[data->index] == 'i')
		ft_prepare_di_processing(arg, data);
	if (format[data->index] == 'u')
		ft_prepare_u_processing(arg, data);
}
