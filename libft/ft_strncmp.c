/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:39:45 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:40:42 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares up to n characters of two strings.
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @param n Maximum number of characters to compare.
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 *         respectively, to be less than, to match, or be greater than s2.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	if (!n)
		return (0);
	while (n-- > 0)
	{
		c1 = (unsigned char)*s1++;
		c2 = (unsigned char)*s2++;
		if (c1 != c2)
			return ((int)c1 - (int)c2);
		if (c1 == '\0')
			break ;
	}
	return (0);
}
