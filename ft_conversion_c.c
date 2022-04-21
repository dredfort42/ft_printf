#include "ft_printf.h"

static void	write_wc_arr_4(wchar_t wc, t_data *data)
{
	char	wc_arr[4];

	wc_arr[0] = ((wc >> 18) + 240);
	wc_arr[1] = (((wc >> 12) & 63) + 128);
	wc_arr[2] = (((wc >> 6) & 63) + 128);
	wc_arr[3] = ((wc & 63) + 128);
	data->counter += write(1, wc_arr, 4);
}

void	ft_processing_wc(wchar_t wc, t_data *data)
{
	char	wc_arr[3];

	if (wc >= 0 && wc <= 255)
		data->counter += write(1, &wc, 1);
	else if (wc >= 128 && wc <= 2047)
	{
		wc_arr[0] = ((wc >> 6) + 192);
		wc_arr[1] = ((wc & 63) + 128);
		data->counter += write(1, wc_arr, 2);
	}
	else if (wc >= 2048 && wc <= 65535)
	{
		wc_arr[0] = ((wc >> 12) + 224);
		wc_arr[1] = (((wc >> 6) & 63) + 128);
		wc_arr[2] = ((wc & 63) + 128);
		data->counter += write(1, wc_arr, 3);
	}
	else if (wc >= 65536 && wc <= 1114111)
		write_wc_arr_4(wc, data);
}

static void	ft_processing_c(char c, t_data *data)
{
	data->counter += write(1, &c, 1);
}

static void	ft_magic_c_wc(va_list arg, t_data *data)
{
	if (data->len < 0)
	{
		data->minus = 1;
		data->len *= -1;
	}
	if (!data->minus)
	{
		while (data->len-- > 1)
			data->counter += write(1, " ", 1);
	}
	if (!data->l)
		ft_processing_c(va_arg(arg, int), data);
	else
		ft_processing_wc(va_arg(arg, wint_t), data);
	if (data->minus)
	{
		while (data->len-- > 1)
			data->counter += write(1, " ", 1);
	}
}

void	ft_conversion_c(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 'c')
		ft_magic_c_wc(arg, data);
}
