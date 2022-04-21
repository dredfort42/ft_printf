#include "ft_printf.h"

static struct	s_diuxX
{
	short	i;
	long	spacer_pc;
	long	spacer_len_count;
	long	str_len;
	short	number_with_sign;
}			t_d;

static void	ft_magic_diuxX_conditions(const char *str, const t_data *data)
{
	if (str[0] == '-' || str[0] == '+' || str[0] == ' ')
		t_d.number_with_sign = 1;
	if (!data->precision && str[0] == '0')
		t_d.str_len = 0;
	if (data->precision >= t_d.str_len)
		t_d.spacer_pc = data->precision - t_d.str_len + t_d.number_with_sign;
	if (data->len > t_d.spacer_pc + t_d.str_len)
		t_d.spacer_len_count = data->len - t_d.spacer_pc - t_d.str_len;
}

static void	ft_magic_diuxX_write(const char *str, t_data *data)
{
	if (data->sharp && data->zero && !data->minus && t_d.spacer_len_count
		&& str[t_d.i] == '0' && (str[t_d.i + 1] == 'x'
			|| str[t_d.i + 1] == 'X') && ft_spacer_c(data)[0] == '0')
	{
		data->counter += write(1, &str[t_d.i++], 1);
		data->counter += write(1, &str[t_d.i++], 1);
	}
	if (t_d.number_with_sign && data->zero && data->precision < 0)
		data->counter += write(1, &str[t_d.i++], 1);
	while (!data->minus && t_d.spacer_len_count)
	{
		data->counter += write(1, ft_spacer_c(data), 1);
		t_d.spacer_len_count--;
	}
	if (str[t_d.i] == '-' || str[t_d.i] == '+' || str[t_d.i] == ' ')
		data->counter += write(1, &str[t_d.i++], 1);
	while (t_d.spacer_pc--)
		data->counter += write(1, "0", 1);
	while (str[t_d.i] && t_d.str_len)
		data->counter += write(1, &str[t_d.i++], 1);
	while (t_d.spacer_len_count--)
		data->counter += write(1, ft_spacer_c(data), 1);
}

void	ft_magic_diuxX(char *str, t_data *data)
{
	t_d.i = 0;
	t_d.spacer_pc = 0;
	t_d.spacer_len_count = 0;
	t_d.str_len = ft_strlen(str);
	t_d.number_with_sign = 0;
	ft_magic_diuxX_conditions(str, data);
	ft_magic_diuxX_write(str, data);
	free(str);
}
