/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:24:16 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 16:44:24 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds a new node at the end of the list.
 * @param lst Double pointer to the head of the list.
 * @param new Pointer to the new node to be added.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
