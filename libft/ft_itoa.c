/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:21:12 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 17:37:27 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts an integer to its string representation.
 * @param n The integer to convert.
 * @return A pointer to the newly allocated string representing the integer.
 *         Returns NULL if memory allocation fails.
 */
char	*ft_itoa(int n)
{
	long	value;
	int		neg;
	int		digits;
	int		len;
	char	*str;

	value = n;
	neg = (n < 0);
	if (neg)
		value = -value;
	digits = ft_digcount(value);
	len = digits + neg + 1;
	str = (char *)malloc((size_t)len);
	if (!str)
		return (NULL);
	str[len - 1] = '\0';
	while (digits--)
	{
		str[neg + digits] = (char)('0' + (value % 10));
		value /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
