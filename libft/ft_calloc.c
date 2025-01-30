/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:24:03 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/11 15:53:21 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	size_t	total_mem;
	void	*p_mem;

	if (nitems && size && size > SIZE_MAX / nitems)
		return (NULL);
	total_mem = nitems * size;
	p_mem = malloc(total_mem);
	if (p_mem != NULL)
	{
		ft_bzero(p_mem, total_mem);
		return (p_mem);
	}
	return (NULL);
}
