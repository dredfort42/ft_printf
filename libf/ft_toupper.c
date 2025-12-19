/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:50:42 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:50:46 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a lowercase letter to uppercase.
 * @param c The character to convert.
 * @return The uppercase equivalent if c is a lowercase letter;
 *         otherwise, returns c unchanged.
 */
int	ft_toupper(int c)
{
	if (ft_islower(c))
		c -= 32;
	return (c);
}
