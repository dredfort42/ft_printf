/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:41:03 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 17:24:48 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of the null-terminated string needle
 *        in the string haystack, where not more than len
 *        characters are searched.
 * @param haystack Pointer to the string to be searched.
 * @param needle Pointer to the substring to be located.
 * @param len Maximum number of characters to search.
 * @return A pointer to the beginning of the located substring,
 *         or NULL if the substring is not found within the given length.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	nlen;

	nlen = ft_strlen(needle);
	if (!nlen || haystack == needle)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && needle[j]
			&& haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (j == nlen)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
