/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:48:12 by so_long           #+#    #+#             */
/*   Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns an array of strings obtained
	by splitting ’s’ using the character ’c’ as a delimiter. The array
	must end with a NULL pointer.

	It returns the array of new strings resulting from the split or NULL
	if the allocation fails.
*/

#include "libft.h"

static size_t	count_words(const char *str, char c);
static char		*duplicate_word(const char *str, int start, int end);

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**split;

	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = duplicate_word(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

static size_t	count_words(const char *str, char c)
{
	int		i;
	int		trigger;
	size_t	counter;

	i = 0;
	trigger = 1;
	counter = 0;
	while (str[i])
	{
		if (str[i] != c && trigger)
		{
			trigger = 0;
			counter++;
		}
		else if (str[i] == c)
			trigger = 1;
		i++;
	}
	return (counter);
}

static char	*duplicate_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}
