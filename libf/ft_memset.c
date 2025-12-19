/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:24 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:15:31 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills the first len bytes of the memory area pointed to by b
 *        with the constant byte c.
 * @param b Pointer to the memory area to be filled.
 * @param c The byte value to fill the memory with (converted to unsigned char).
 * @param len The number of bytes to be set to the value.
 * @return A pointer to the memory area b.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)b;
	i = 0;
	while (i < len)
	{
		tmp[i] = (char)c;
		i++;
	}
	return (b);
}
