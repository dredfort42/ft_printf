/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:19:29 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 14:19:33 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is printable.
 * @param c The character to check.
 * @return Returns a non-zero value if the character is printable,
 *         otherwise returns 0.
 */
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
