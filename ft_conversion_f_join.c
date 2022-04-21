#include "ft_printf.h"

static void	ft_f_join_sign(char *rtn, short minus, t_data *data, short
*sign)
{
	*sign = 0;
	if (minus || data->plus || data->space)
		*sign = 1;
	if (minus)
		data->plus = 0;
	if (minus || data->plus)
		data->space = 0;
	if (data->space)
		rtn[0] = ' ';
	if (data->plus)
		rtn[0] = '+';
	if (minus)
		rtn[0] = '-';
}

char	*ft_f_join(short minus, char *str1, char *str2, t_data *data)
{
	char	*rtn;
	int		i;
	int		j;
	short	sign;

	i = 0;
	j = 0;
	rtn = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 3));
	ft_f_join_sign(rtn, minus, data, &sign);
	while (str1[i])
	{
		rtn[sign + i] = str1[i];
		i++;
	}
	if (str2[j] || (data->sharp && !data->precision))
		rtn[sign + i++] = '.';
	while (str2[j])
	{
		rtn[sign + i + j] = str2[j];
		j++;
	}
	rtn[sign + i + j] = '\0';
	free(str1);
	free(str2);
	return (rtn);
}
