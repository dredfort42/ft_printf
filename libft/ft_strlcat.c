/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:34:57 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:37:46 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends the string src to the end of dst.
 *        It will append at most dstsize - strlen(dst) - 1 characters.
 *        It will then NUL-terminate, unless dstsize is 0 or
 *        the original dst string was longer than dstsize.
 * @param dst Pointer to the destination string.
 * @param src Pointer to the source string.
 * @param dstsize The total size of the destination buffer.
 * @return The total length of the string it tried to create,
 *         that is the initial length of dst plus the length of src.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;
	size_t	copy;

	dlen = 0;
	while (dlen < dstsize && dst[dlen])
		dlen++;
	if (dlen == dstsize)
		return (dstsize + ft_strlen(src));
	if (dstsize - dlen - 1 > 0)
		copy = dstsize - dlen - 1;
	else
		copy = 0;
	if (copy)
	{
		i = 0;
		while (i < copy && src[i])
		{
			dst[dlen + i] = src[i];
			i++;
		}
		dst[dlen + i] = '\0';
	}
	return (dlen + ft_strlen(src));
}
