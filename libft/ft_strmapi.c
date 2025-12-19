/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:38:39 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 15:39:31 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory for the result string of given length.
 * @param len The length of the string to allocate (excluding NUL terminator).
 * @return A pointer to the newly allocated string, or NULL if allocation fails.
 */
static char	*alloc_result(size_t len)
{
	char	*res;

	res = (char *)malloc(len + 1);
	if (res)
		res[len] = '\0';
	return (res);
}

/**
 * @brief Applies the mapping function f to each character of the source string
 *        and stores the result in the destination string.
 * @param src The source string.
 * @param dst The destination string.
 * @param f The mapping function to apply.
 * @param len The length of the strings.
 */
static void	apply_map(
	const char *src,
	char *dst,
	char (*f)(unsigned int, char),
	size_t len
)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = f((unsigned int)i, src[i]);
		i++;
	}
}

/**
 * @brief Applies the function f to each character of the string s,
 *        passing its index as the first argument to create a new string.
 * @param s The input string.
 * @param f The function to apply to each character and its index.
 * @return A pointer to the newly allocated string resulting from
 *         the successive applications of f. Returns NULL if
 *         memory allocation fails or if s or f is NULL.
 */
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*res;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	res = alloc_result(len);
	if (!res)
		return (NULL);
	apply_map(s, res, f, len);
	return (res);
}
