#include "ft_printf.h"

char	*ft_processing_f(long double f, t_data *data)
{
	char				*rtn;
	unsigned long long	whole_part;
	short				minus;

	u_bits.ld = f;
	minus = u_bits.s_bits.sign;
	if (data->precision < 0)
		data->precision = 6;
	if (f < 0)
	{
		minus = 1;
		f *= -1;
	}
	f = ft_rounding_f(f, data->precision);
	if (f > 9223372036854775807.0)
		return (ft_inf(minus, data));
	whole_part = (unsigned long long)f;
	f -= whole_part;
	rtn = ft_f_join(minus, ft_whole_part_f(whole_part, data),
			ft_fractional_part_f(f, data), data);
	return (rtn);
}

static void	ft_magic_fe_write(char *str,
						  t_data *data, short i, long spacer_len_count)
{
	long	str_len;

	str_len = ft_strlen(str);
	while (!data->minus && spacer_len_count)
	{
		data->counter += write(1, ft_spacer_f(data), 1);
		spacer_len_count--;
	}
	if (str[0] == '-' || str[0] == ' ' || str[0] == '+')
		data->counter += write(1, &str[i++], 1);
	while (str[i] && str_len)
		data->counter += write(1, &str[i++], 1);
	while (spacer_len_count--)
		data->counter += write(1, ft_spacer_f(data), 1);
}

void	ft_magic_fe(char *str, t_data *data)
{
	short	i;
	long	spacer_len_count;
	long	str_len;
	short	number_with_extra;

	i = 0;
	spacer_len_count = 0;
	str_len = ft_strlen(str);
	number_with_extra = 0;
	if (str[0] == '-' || str[0] == ' ' || str[0] == '+')
		number_with_extra = 1;
	if (data->len > str_len)
		spacer_len_count = data->len - str_len;
	if (number_with_extra && data->zero)
		data->counter += write(1, &str[i++], 1);
	ft_magic_fe_write(str, data, i, spacer_len_count);
	free(str);
}

static char	*ft_f_status(va_list arg, t_data *data)
{
	va_list	copy;

	va_copy(copy, arg);
	if (ft_is_nan(copy))
		return (ft_nan(data));
	return (ft_processing_f(va_arg(arg, double), data));
}

void	ft_conversion_f(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'f')
		ft_magic_fe(ft_f_status(arg, data), data);
}
