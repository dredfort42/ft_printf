/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:50:34 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:50:39 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts an uppercase letter to lowercase.
 * @param c The character to convert.
 * @return The lowercase equivalent if c is an uppercase letter;
 *         otherwise, returns c unchanged.
 */
int	ft_tolower(int c)
{
	if (ft_isupper(c))
		c += 32;
	return (c);
}
