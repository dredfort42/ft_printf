/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:20:55 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 14:23:49 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is an uppercase letter.
 * @param c The character to check.
 * @return Returns a non-zero value if the character is an uppercase letter,
 *         otherwise returns 0.
 */
int ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}
