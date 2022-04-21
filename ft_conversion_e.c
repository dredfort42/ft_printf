#include "ft_printf.h"

static void	ft_power_e_e(t_data *data, long double *f, short *e, short *f_mult)
{
	if (data->precision < 0)
		data->precision = 6;
	(*e) = 0;
	(*f_mult) = 1;
	if ((*f) < 0)
	{
		(*f_mult) = -1;
		(*f) = -(*f);
	}
	if ((*f))
	{
		while (ft_rounding_f((*f), data->precision + 1) > 9)
		{
			(*f) /= 10;
			(*e)++;
		}
		while (ft_rounding_f((*f), data->precision + 1) < 1 )
		{
			(*f) *= 10;
			(*e)--;
		}
	}
}

char	*ft_processing_e(long double f, t_data *data)
{
	char	*rtn;
	char	*e_str;
	short	e;
	short	f_mult;

	ft_power_e_e(data, &f, &e, &f_mult);
	rtn = ft_processing_f(f * f_mult, data);
	e_str = ft_e_str(&e, data);
	rtn = ft_e_join(rtn, e_str, data);
	return (rtn);
}

static char	*ft_e_status(va_list arg, t_data *data)
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
	return (ft_processing_e(f, data));
}

void	ft_conversion_e(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'e')
		ft_magic_fe(ft_e_status(arg, data), data);
}
