#include "ft_printf.h"

static char	*ft_processing_s(char *str, t_data *data)
{
	char	*rtn;
	long	i;
	long	max_len;

	if (!str)
		str = "(null)";
	max_len = ft_strlen(str);
	rtn = ft_memory_p(max_len + 1, data);
	i = 0;
	if (data->precision > -1 && max_len > data->precision)
		max_len = data->precision;
	while (i < max_len)
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

static void	ft_write_wcstr(wchar_t *wcstr, t_data *data)
{
	int	i;

	i = 0;
	while (wcstr[i])
		ft_processing_wc(wcstr[i++], data);
}

static void	ft_processing_ls(wchar_t *wcstr, t_data *data)
{
	long	spaces_count;
	int		i;
	char	*spacer;
	short	empty;

	empty = 0;
	spacer = ft_spacer_c(data);
	spaces_count = 0;
	i = 0;
	if (!wcstr)
		wcstr = ft_null_wc(data, &empty);
	while (wcstr[i])
		i++;
	if (data->len > i)
		spaces_count = data->len - i;
	if (!data->minus)
		while (spaces_count--)
			data->counter += write(1, spacer, 1);
	ft_write_wcstr(wcstr, data);
	if (data->minus)
		while (spaces_count--)
			data->counter += write(1, spacer, 1);
	if (empty)
		free(wcstr);
}

static void	ft_magic_s(char *str, t_data *data)
{
	long	spaces_count;
	char	*spacer;

	spacer = ft_spacer_c(data);
	spaces_count = 0;
	if (data->len > ft_strlen(str))
		spaces_count = data->len - ft_strlen(str);
	if (!data->minus)
	{
		while (spaces_count--)
			data->counter += write(1, spacer, 1);
	}
	data->counter += write(1, str, ft_strlen(str));
	if (data->minus)
	{
		while (spaces_count--)
			data->counter += write(1, spacer, 1);
	}
	free(str);
}

void	ft_conversion_s(va_list arg, const char *format, t_data *data)
{
	if (format[data->index] == 's')
	{
		if (data->len < 0)
		{
			data->minus = 1;
			data->len *= -1;
		}
		if (!data->l)
			ft_magic_s(ft_processing_s(va_arg(arg, char *), data), data);
		else
			ft_processing_ls(va_arg(arg, wint_t *), data);
	}
}
