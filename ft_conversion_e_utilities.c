#include "ft_printf.h"

static void	ft_e_num(char *e_str, short e, short i)
{
	if (ft_digits_in_number(e, 10) < 2)
	{
		e_str[i] = '0' + e;
		e_str[i - 1] = '0';
	}
	else
	{
		while (e)
		{
			e_str[i] = '0' + (e % 10);
			e /= 10;
			i--;
		}
	}
}

static void	ft_e_sign(char *e_sign, short *e)
{
	if ((*e) < 0)
	{
		(*e_sign) = '-';
		(*e) *= -1;
	}
	else
		(*e_sign) = '+';
}

char	*ft_e_str(short *e, t_data *data)
{
	char	*e_str;
	short	i;
	char	e_sign;

	i = 4;
	e_str = ft_memory_p(5, data);
	e_str[i--] = '\0';
	ft_e_sign(&e_sign, e);
	ft_e_num(e_str, *e, i);
	e_str[1] = e_sign;
	e_str[0] = 'e';
	return (e_str);
}
