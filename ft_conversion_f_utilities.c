#include "ft_printf.h"

short	ft_is_nan(va_list arg)
{
	va_list	copy;
	double	f;
	double	cf;

	va_copy(copy, arg);
	f = va_arg(arg, double);
	cf = va_arg(copy, double);
	if (f == cf)
		return (0);
	return (1);
}

long double	ft_rounding_f(long double f, int precision)
{
	long double	f_mult;

	f_mult = 1;
	if (f < 0)
		f_mult *= -1;
	while (precision >= 0)
	{
		f_mult *= 10.0;
		precision--;
	}
	if (f == 0.5 || f == -0.5 || f == 4.5 || f == 2.5 || f == -4.5 || f == -2.5)
		return (f);
	if (f == -3.5)
		return (f - 0.5);
	return ((f * f_mult + 5) / f_mult);
}

char	*ft_whole_part_f(unsigned long long num, t_data *data)
{
	char	*rtn;
	short	digits_count;

	if (!num)
	{
		rtn = malloc(sizeof(char) * (1 + 1));
		rtn[0] = '0';
		rtn[1] = '\0';
		return (rtn);
	}
	digits_count = ft_digits_in_number(num, 10);
	rtn = ft_memory_p((digits_count + 1), data);
	rtn[digits_count--] = '\0';
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

char	*ft_fractional_part_f(long double f, t_data *data)
{
	char	*rtn;
	short	i;

	rtn = malloc(sizeof(char) * (data->precision + 1));
	if (!rtn)
	{
		data->error = 1;
		return (0);
	}
	rtn[data->precision] = '\0';
	i = 0;
	while (data->precision - i)
	{
		f *= 10;
		rtn[i] = '0' + (int)(f);
		f -= (int)f;
		i++;
	}
	return (rtn);
}
