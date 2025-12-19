/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:00:59 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:01:10 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n bytes from memory area src to memory area dst.
 * @param dst Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n The number of bytes to copy.
 * @return A pointer to the destination memory area dst.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*pdst;
	char	*psrc;
	size_t	i;

	if (!n || dst == src)
		return (dst);
	pdst = (char *)dst;
	psrc = (char *)src;
	i = 0;
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}
