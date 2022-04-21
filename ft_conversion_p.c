#include "ft_printf.h"

static short	ft_digits_count_p(unsigned long long p, t_data *data)
{
	short	digits_count;

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

static char	*ft_processing_p(unsigned long long p, t_data *data)
{
	char	*rtn;
	short	digits_count;

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

static void	ft_magic_p(char *str, t_data *data)
{
	short	len;

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

void	ft_conversion_p(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'p')
		ft_magic_p(ft_processing_p(
				va_arg(arg, unsigned long long), data), data);
}
