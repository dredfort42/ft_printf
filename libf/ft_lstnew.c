/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:52:33 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 14:54:08 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Creates a new list node with the given content.
 * @param content Pointer to the content to be stored in the new node.
 * @return Pointer to the newly created list node, or NULL if allocation fails.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(*node));
	if (!node)
		return (NULL);
	*node = (t_list){.content = content, .next = NULL};
	return (node);
}
