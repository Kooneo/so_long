/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:05:59 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/10 14:23:22 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int search_str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)search_str)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)search_str == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
