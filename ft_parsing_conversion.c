#include "ft_printf.h"

static void	ft_conversion_percent(const char *format, t_data *data)
{
	if (format[data->index] == '%')
	{
		data->precision = -1;
		if (data->len < 0)
		{
			data->minus = 1;
			data->len *= -1;
		}
		if (data->minus)
			data->zero = 0;
		if (!data->minus)
			while (data->len-- - 1 > 0)
				data->counter += write(1, ft_spacer_c(data), 1);
		data->counter += write(1, "%", 1);
		if (data->minus)
			while (data->len-- - 1 > 0)
				data->counter += write(1, ft_spacer_c(data), 1);
	}
}

void	ft_parsing_conversion(va_list arg, char *format, t_data *data)
{
	ft_conversion_percent(format, data);
	ft_conversion_c(arg, format, data);
	ft_conversion_s(arg, format, data);
	ft_conversion_p(arg, format, data);
	ft_conversion_diu(arg, format, data);
	ft_conversion_x(arg, format, data);
	ft_conversion_X(arg, format, data);
	ft_conversion_n(arg, format, data);
	ft_conversion_f(arg, format, data);
	ft_conversion_e(arg, format, data);
	ft_conversion_g(arg, format, data);
}
