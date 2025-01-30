/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:12:29 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/10 14:23:24 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char delimiter)
{
	int	i;
	int	word_count;
	int	in_word;

	if (!str)
		return (0);
	word_count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != delimiter && !in_word)
		{
			in_word = 1;
			word_count++;
		}
		else if (str[i] == delimiter)
			in_word = 0;
		i++;
	}
	return (word_count);
}

static char	**ft_free(int result_index, char **result)
{
	int	j;

	j = 0;
	while (j < result_index)
	{
		free(result[j]);
		j++;
	}
	free(result);
	return (NULL);
}

static char	*ft_fill(int *i, const char *s, char c)
{
	int	word_start;

	word_start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	return (ft_substr(s, word_start, *i - word_start));
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		result_index;

	if (!s)
		return (NULL);
	i = 0;
	result_index = 0;
	result = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			result[result_index] = ft_fill(&i, s, c);
			if (!result[result_index])
				return (ft_free(result_index, result));
			result_index++;
		}
		if (s[i] != '\0')
			i++;
	}
	result[result_index] = NULL;
	return (result);
}
