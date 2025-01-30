/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:36:51 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/11 11:59:51 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_backward_move(unsigned char *dest, const unsigned char *src,
		size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		i--;
		dest[i] = src[i];
	}
}

void	*ft_memmove(void *dest_str, const void *src_str, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*src;

	if ((!dest_str && !src_str) || (!dest_str && n == 0))
		return (NULL);
	dest = (unsigned char *)dest_str;
	src = (const unsigned char *)src_str;
	if (dest > src)
		ft_backward_move(dest, src, n);
	else if (dest < src)
		ft_memcpy(dest, src, n);
	return (dest_str);
}
