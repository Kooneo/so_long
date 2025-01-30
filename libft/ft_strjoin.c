/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:00:27 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/11 15:06:44 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	if (s1 != NULL)
		len_s1 = ft_strlen(s1);
	if (s2 != NULL)
		len_s2 = ft_strlen(s2);
	string = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!string)
		return (NULL);
	if (s1)
		ft_strlcpy(string, s1, len_s1 + 1);
	else
		string[0] = '\0';
	if (s2)
		ft_strlcat(string, s2, len_s1 + len_s2 + 1);
	return (string);
}
