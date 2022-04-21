#include "ft_printf.h"

static char	*ft_processing_g_f(long double f, t_data *data, short *precision,
							short e)
{
	char	*rtn;
	short	pa;
	short	din;

	data->precision = *precision - (e + 1);
	if (*precision == 6 && f)
	{
		pa = ft_precision_adjustment(f);
		din = ft_digits_in_number(f, 10);
		if (pa != 1)
			data->precision = 6 - din + pa;
		else
			data->precision = 6 - din;
	}
	rtn = ft_processing_f(f, data);
	if (!data->sharp && ft_dot_in_str(rtn))
		rtn = ft_trim_trailing_f_zeros(rtn);
	return (rtn);
}

static char	*ft_processing_g(long double f, t_data *data)
{
	short	precision;
	short	e;
	char	*rtn;

	precision = data->precision;
	if (!precision)
		precision = 1;
	if (precision < 0)
		precision = 6;
	e = 0;
	ft_power_e_g(f, &precision, &e);
	if (precision > e && e >= -4)
		rtn = ft_processing_g_f(f, data, &precision, e);
	else
	{
		data->precision = precision - 1;
		rtn = ft_processing_e(f, data);
		if (!data->sharp)
			rtn = ft_trim_trailing_e_zeros(rtn);
	}
	return (rtn);
}

static char	*ft_g_status(va_list arg, t_data *data)
{
	va_list		copy;
	long double	f;
	long double	tmp_f;
	short		minus;

	va_copy(copy, arg);
	if (ft_is_nan(copy))
		return (ft_nan(data));
	f = va_arg(arg, double);
	tmp_f = f;
	minus = 0;
	if (tmp_f < 0)
	{
		minus = 1;
		tmp_f = -tmp_f;
	}
	if (tmp_f > 9223372036854775808.0)
		return (ft_inf(minus, data));
	return (ft_processing_g(f, data));
}

void	ft_conversion_g(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'g')
		ft_magic_fe(ft_g_status(arg, data), data);
}
