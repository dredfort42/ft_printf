#include "ft_printf.h"

/**
 * @brief Allocates memory for a string of given size.
 *
 * @param size The size of memory to allocate.
 * @param data Pointer to a t_data structure that holds parsing state and flags.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
char *ft_memory_p(int size, t_data *data)
{
	char *rtn;

	rtn = (char *)malloc(sizeof(char) * size);
	if (!rtn)
	{
		data->error = 1;
		return (NULL);
	}
	return (rtn);
}

/**
 * @brief Checks if the given character is a conversion specifier.
 *
 * @param chr The character to check.
 * @return Returns TRUE if the character is a conversion specifier, otherwise FALSE.
й */
short ft_is_conversion(char chr)
{
	short i;
	char *conversions;

	i = 0;
	conversions = "%cspdiuxXnfge\0";
	while (conversions[i])
	{
		if (chr == conversions[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

short ft_is_flag(char chr)
{
	short i;
	char *flags;

	i = 0;
	flags = "' -+#0\0";
	while (flags[i])
	{
		if (chr == flags[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}
