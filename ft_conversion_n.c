#include "ft_printf.h"

void	ft_conversion_n(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'n')
	{
		if (data->l)
			*((long *)(va_arg(arg, unsigned long long))) = data->counter;
		else if (data->ll)
			*((long long *)(va_arg(arg, unsigned long long))) = data->counter;
		else if (data->h)
			*((short *)(va_arg(arg, unsigned long long))) = (short)
					data->counter;
		else if (data->hh)
			*((char *)(va_arg(arg, unsigned long long))) = (char) data->counter;
		else
			*((int *)(va_arg(arg, unsigned long long))) = data->counter;
	}
}
