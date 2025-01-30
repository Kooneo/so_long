/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:26:13 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/11 13:11:17 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	str_len;
	char	*new_str;

	str_len = ft_strlen(str) + 1;
	new_str = (char *)malloc(str_len * sizeof(char));
	if (new_str != NULL)
	{
		ft_memcpy(new_str, str, str_len);
		return ((char *)new_str);
	}
	return (NULL);
}
