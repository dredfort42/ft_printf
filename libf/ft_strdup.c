/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:30:09 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:30:27 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Duplicates the string `s1` by allocating sufficient memory and copying
 * the content of `s1` into the newly allocated memory.
 * @param s1 The string to duplicate.
 * @return A pointer to the duplicated string, or NULL
 *         if memory allocation fails.
 */
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s1, len + 1);
	return (dup);
}
