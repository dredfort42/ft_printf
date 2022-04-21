#include "ft_printf.h"

char	*ft_e_join(char *s1, char *s2, t_data *data)
{
	char	*rtn;
	int		i;
	int		j;

	i = 0;
	j = 0;
	rtn = ft_memory_p((ft_strlen(s1) + ft_strlen(s2) + 2), data);
	while (s1[i])
	{
		rtn[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		rtn[i + j] = s2[j];
		j++;
	}
	rtn[i + j] = '\0';
	free(s1);
	free(s2);
	return (rtn);
}
