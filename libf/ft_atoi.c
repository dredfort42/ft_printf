/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:00:23 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 17:29:11 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts the initial portion of the string pointed to by str
 *        to an integer representation.
 * @param sign Detected integer sign.
 * @param str Pointer to the null-terminated string with digits to be converted.
 * @return The converted value.
 */
static int	atoi_result(int sign, const char *str)
{
	size_t				i;
	unsigned long long	res;
	unsigned long long	pos_limit;
	unsigned long long	neg_limit;

	i = 0;
	res = 0;
	pos_limit = 2147483647ULL;
	neg_limit = 2147483648ULL;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (sign == 1 && res > pos_limit)
			return ((int)pos_limit);
		if (sign == -1 && res > neg_limit)
			return ((int)(-(long long)neg_limit));
		i++;
	}
	return ((int)(sign * (long long)res));
}

/**
 * @brief Converts the initial portion of the string pointed to by str
 *        to an integer representation.
 * @param str Pointer to the null-terminated string to be converted.
 * @return The converted integer value.
 */
int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	if (!str)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (atoi_result(sign, &str[i]));
}
