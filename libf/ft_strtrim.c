/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:43:58 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:44:11 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Trims characters from the beginning and end of the string `s1`
 * that are present in the string `set`. Allocates memory for
 * the trimmed string.
 * @param s1 The original string to trim.
 * @param set The set of characters to trim from `s1`.
 * @return A pointer to the newly allocated trimmed string,
 *         or NULL if allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*trimmed;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = s1 + ft_strlen(s1);
	while (end > start && ft_strchr(set, *(end - 1)))
		end--;
	len = (size_t)(end - start);
	trimmed = (char *)malloc(len + 1);
	if (!trimmed)
		return (NULL);
	if (len)
		ft_memcpy(trimmed, start, len);
	trimmed[len] = '\0';
	return (trimmed);
}
