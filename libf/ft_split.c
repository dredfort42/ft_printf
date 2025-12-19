/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnovikov <dnovikov@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:18:38 by dnovikov          #+#    #+#             */
/*   Updated: 2025/11/04 16:32:49 by dnovikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of words in the string s
 *        separated by the delimiter c.
 * @param s The input string.
 * @param c The delimiter character.
 * @return The number of words found in the string.
 */
static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

/**
 * @brief Calculates the length of the next word in the string s
 *        up to the delimiter c.
 * @param s The input string.
 * @param c The delimiter character.
 * @return The length of the next word.
 */
static size_t	next_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

/**
 * @brief Frees the allocated memory for the array of words.
 * @param arr The array of strings to be freed.
 * @param filled The number of words that have been allocated in the array.
 */
static void	free_words(char **arr, size_t filled)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < filled)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief Splits the string s into an array of strings using the delimiter c.
 * @param s The input string to be split.
 * @param c The delimiter character.
 */
void	ft_split_safely(char **arr, size_t words, char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		len = next_word_len(s, c);
		arr[i] = (char *)malloc(len + 1);
		if (!arr[i])
		{
			free_words(arr, i);
			return ;
		}
		ft_strlcpy(arr[i], s, len + 1);
		s += len;
		i++;
	}
	arr[i] = NULL;
}

/**
 * @brief Splits the string s into an array of strings using the delimiter c.
 * @param s The input string to be split.
 * @param c The delimiter character.
 * @return A NULL-terminated array of strings resulting from the split.
 *         Returns NULL if memory allocation fails or if s is NULL.
 */
char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	ft_split_safely(arr, words, s, c);
	return (arr);
}
