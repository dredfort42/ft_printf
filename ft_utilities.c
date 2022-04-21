#include "ft_printf.h"

void	ft_read_number(const char *format, t_data *data, int *num)
{
	while (format[data->index] >= '0' && format[data->index] <= '9')
	{
		*num *= 10;
		*num += format[data->index] - '0';
		data->index++;
	}
	data->index--;
}

long	ft_strlen(char *str)
{
	long	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

short	ft_digits_in_number(long double f, short base)
{
	short				i;
	unsigned long long	num;

	if (f < 0)
		f = -f;
	num = (unsigned long long)f;
	i = 0;
	while (num)
	{
		num /= base;
		i++;
	}
	return (i);
}

char	*ft_capitalizer(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

void	ft_hex(char	*rtn, unsigned long long num, short	*digits_count)
{
	char	*hex;

	hex = "0123456789abcdef";
	while (num)
	{
		rtn[*digits_count] = hex[(num % 16)];
		num /= 16;
		*digits_count -= 1;
	}
}
