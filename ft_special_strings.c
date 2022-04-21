#include "ft_printf.h"

wchar_t	*ft_null_wc(t_data *data, short *is_empty)
{
	wchar_t	*null_wcsrt;

	null_wcsrt = malloc(sizeof(wchar_t) * 6);
	if (!null_wcsrt)
	{
		data->error = 1;
		return (0);
	}
	*is_empty = 1;
	null_wcsrt[0] = L'(';
	null_wcsrt[1] = L'n';
	null_wcsrt[2] = L'u';
	null_wcsrt[3] = L'l';
	null_wcsrt[4] = L'l';
	null_wcsrt[5] = L')';
	null_wcsrt[6] = 0;
	return (null_wcsrt);
}

char	*ft_inf(short minus, t_data *data)
{
	char	*rtn;
	short	len;

	len = 0;
	data->zero = 0;
	rtn = malloc(sizeof(char) * (3 + minus));
	if (!rtn)
	{
		data->error = 1;
		return (0);
	}
	if (minus)
		rtn[len++] = '-';
	rtn[len++] = 'i';
	rtn[len++] = 'n';
	rtn[len++] = 'f';
	rtn[len] = '\0';
	return (rtn);
}

char	*ft_nan(t_data *data)
{
	char	*rtn;

	data->zero = 0;
	rtn = malloc(sizeof(char) * 4);
	if (!rtn)
	{
		data->error = 1;
		return (0);
	}
	rtn[0] = 'n';
	rtn[1] = 'a';
	rtn[2] = 'n';
	rtn[3] = '\0';
	return (rtn);
}

char	*ft_spacer_c(t_data *data)
{
	if (data->zero && data->precision < 0)
		return ("0");
	else
		return (" ");
}

char	*ft_spacer_f(t_data *data)
{
	if (data->zero)
		return ("0");
	else
		return (" ");
}
