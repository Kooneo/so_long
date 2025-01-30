/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:15:39 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:52:01 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gn(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gn(char *str, int c_chr)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c_chr)
			return (str + i);
		i++;
	}
	if (c_chr == '\0')
		return (str + i);
	return (NULL);
}

char	*ft_strdup_gn(char *str2)
{
	char	*f_str;
	int		i;

	i = 0;
	f_str = malloc(ft_strlen_gn(str2) + 1);
	if (!f_str)
		return (NULL);
	i = 0;
	while (str2[i] != '\0')
	{
		f_str[i] = str2[i];
		i++;
	}
	f_str[i] = '\0';
	return (f_str);
}

char	*ft_strjoin_gn(char *str1, char *str2)
{
	char	*final_str;
	size_t	i;
	size_t	j;

	if (!str1 && !str2)
		return (NULL);
	if (!str1)
		return (ft_strdup_gn(str2));
	if (!str2)
		return (ft_strdup_gn(str1));
	final_str = malloc(ft_strlen_gn(str1) + ft_strlen_gn(str2) + 1);
	if (!final_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i] != '\0')
		final_str[j++] = str1[i++];
	i = 0;
	while (str2[i] != '\0')
		final_str[j++] = str2[i++];
	final_str[j] = '\0';
	free(str1);
	return (final_str);
}
