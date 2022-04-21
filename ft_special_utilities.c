#include "ft_printf.h"

char	*ft_memory_p(int size, t_data *data)
{
	char	*rtn;

	rtn = malloc(sizeof(char) * size);
	if (!rtn)
	{
		data->error = 1;
		return (0);
	}
	return (rtn);
}

short	ft_is_conversion(char chr)
{
	short	i;
	char	*conversions;

	i = 0;
	conversions = "%cspdiuxXnfge\0";
	while (conversions[i])
	{
		if (chr == conversions[i])
			return (1);
		i++;
	}
	return (0);
}

short	ft_is_flag(char chr)
{
	short	i;
	char	*flags;

	i = 0;
	flags = "' -+#0\0";
	while (flags[i])
	{
		if (chr == flags[i])
			return (1);
		i++;
	}
	return (0);
}
