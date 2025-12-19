/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:37:54 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:38:02 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies up to dstsize - 1 characters from the string src to dst,
 *        null-terminating the result if dstsize is not 0.
 * @param dst Pointer to the destination string.
 * @param src Pointer to the source string.
 * @param dstsize The size of the destination buffer.
 * @return The total length of the string it tried to create,
 *         that is the length of src.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	copylen;
	size_t	i;

	if (!dst || !src)
		return (0);
	srclen = ft_strlen(src);
	if (dstsize != 0)
	{
		if (srclen >= dstsize)
			copylen = dstsize - 1;
		else
			copylen = srclen;
		i = 0;
		while (i < copylen)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}
