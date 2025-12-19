/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:17:19 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 17:35:59 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of digits in a non-negative long integer.
 * @param n The integer to analyze.
 * @return The number of digits in the integer.
 */
int ft_digcount(int n)
{
	int digits;

	if (!n)
		return (1);
	digits = 0;
	while (n)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}
