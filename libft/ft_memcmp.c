/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:26:19 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/10 14:23:59 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*p_str1;
	const unsigned char	*p_str2;
	size_t				i;

	i = 0;
	p_str1 = (const unsigned char *)str1;
	p_str2 = (const unsigned char *)str2;
	while (i < n)
	{
		if (p_str1[i] != p_str2[i])
			return (p_str1[i] - p_str2[i]);
		i++;
	}
	return (0);
}
