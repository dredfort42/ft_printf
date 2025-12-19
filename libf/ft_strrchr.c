/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:43:07 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:43:30 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the last occurrence of character c in the string s.
 * @param s Pointer to the string to be searched.
 * @param c The character to locate (converted to char).
 * @return A pointer to the last occurrence of c in s,
 *         or NULL if c is not found.
 */
char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	char	ch;

	if (!s)
		return (NULL);
	ch = (char)c;
	p = (char *)s + ft_strlen(s);
	while (p >= s)
	{
		if (*p == ch)
			return (p);
		p--;
	}
	return (NULL);
}
