#include "ft_printf.h"

char	*ft_trim_trailing_e_zeros(char *str)
{
	short	i;

	i = ft_strlen(str) - 5;
	while (i && (str[i] == '0' || str[i] == '.'))
	{
		str[i] = str[i + 1];
		str[i + 1] = str[i + 2];
		str[i + 2] = str[i + 3];
		str[i + 3] = str[i + 4];
		str[i + 4] = '\0';
		i--;
	}
	return (str);
}

char	*ft_trim_trailing_f_zeros(char *str)
{
	short	i;

	i = ft_strlen(str) - 1;
	while (str[i] == '0' && i > 0
		   && (str[i - 1] != ' ' && str[i - 1] != '-' && str[i - 1] != '+'))
		str[i--] = '\0';
	if (str[i] == '.')
		str[i] = '\0';
	return (str);
}

short	ft_precision_adjustment(long double f)
{
	short		i;
	long double	mask;

	i = 0;
	mask = 1;
	if (f < 0)
		f = -f;
	while (f < mask)
	{
		mask /= 10;
		i++;
	}
	return (i);
}

short	ft_dot_in_str(char *str)
{
	long	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '.')
			return (1);
	}
	return (0);
}

void	ft_power_e_g(long double f, short *precision, short *e)
{
	if (f < 0)
		f = -f;
	if (f)
	{
		while (ft_rounding_f(f, *precision) > 9)
		{
			f /= 10;
			*e += 1;
		}
		while (ft_rounding_f(f, *precision) <= 1)
		{
			f *= 10;
			*e -= 1;
		}
	}
}
