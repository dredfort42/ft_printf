#include "ft_printf.h"

char	*ft_negative_di(char *str, t_data *data)
{
	char	*rtn;
	short	i;

	rtn = ft_memory_p((ft_strlen(str) + 1), data);
	i = 0;
	rtn[0] = '-';
	while (str[i])
	{
		rtn[i + 1] = str[i];
		i++;
	}
	rtn[i + 1] = '\0';
	free(str);
	return (rtn);
}

char	*ft_positive_di(char *str, t_data *data)
{
	char	*rtn;
	short	i;
	short	str_len;

	str_len = ft_strlen(str);
	rtn = ft_memory_p((str_len + 1), data);
	i = 0;
	rtn[0] = '+';
	if (str_len == 1 && str[0] == '0' && data->precision == 0)
	{
		rtn[1] = '\0';
		free(str);
		return (rtn);
	}
	while (str[i])
	{
		rtn[i + 1] = str[i];
		i++;
	}
	rtn[i + 1] = '\0';
	free(str);
	return (rtn);
}

char	*ft_space_di(char *str, t_data *data)
{
	char	*rtn;
	short	i;
	int		strlen;

	strlen = ft_strlen(str);
	rtn = ft_memory_p((strlen + 1), data);
	i = 0;
	rtn[0] = ' ';
	if (strlen == 1 && str[0] == '0' && !data->precision)
		rtn[1] = '\0';
	else
	{
		while (str[i])
		{
			rtn[i + 1] = str[i];
			i++;
		}
		rtn[i + 1] = '\0';
	}
	free(str);
	return (rtn);
}
