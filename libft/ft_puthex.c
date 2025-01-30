/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:14:21 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:58:47 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(char *base, unsigned long n, int *count)
{
	if (n >= 16)
		*count = ft_puthex(base, n / 16, count);
	if (safe_write(&base[n % 16], 1, count) == -1)
		return (-1);
	return (*count);
}
