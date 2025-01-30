/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:28:26 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/11 15:13:21 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	find_trim_bounds(const char *s1, const char *set, char **start,
		char **end)
{
	*start = (char *)s1;
	*end = (char *)(s1 + ft_strlen(s1) - 1);
	while (**start && ft_strchr(set, **start))
		(*start)++;
	while (*end > *start && ft_strchr(set, **end))
		(*end)--;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p_start;
	char	*p_end;
	char	*string;
	int		trimmed_length;

	if (!s1 || !set)
		return (NULL);
	find_trim_bounds(s1, set, &p_start, &p_end);
	trimmed_length = p_end - p_start + 1;
	string = (char *)malloc((trimmed_length + 1) * sizeof(char));
	if (!string)
		return (NULL);
	ft_memcpy(string, p_start, trimmed_length);
	string[trimmed_length] = '\0';
	return (string);
}
