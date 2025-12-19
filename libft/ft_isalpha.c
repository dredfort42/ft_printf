/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:17:52 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 14:17:57 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is an alphabetic letter.
 * @param c The character to check.
 * @return Returns a non-zero value if the character is an alphabetic letter,
 *         otherwise returns 0.
 */
int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
