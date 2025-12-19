/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:57:06 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:55:57 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Scans the initial n bytes of the memory area pointed to by s
 *        for the first instance of c.
 * @param s Pointer to the memory area to be scanned.
 * @param c The character to locate (converted to char).
 * @param n The number of bytes to be analyzed.
 * @return A pointer to the matching byte or NULL if the character
 *         does not occur in the given memory area.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*us;
	unsigned char		uc;

	us = (const unsigned char *)s;
	uc = (unsigned char)c;
	while (n--)
	{
		if (*us == uc)
			return ((void *)us);
		us++;
	}
	return (NULL);
}
