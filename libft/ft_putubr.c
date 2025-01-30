/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putubr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:13:48 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:58:47 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putubr(unsigned int n, int count)
{
	char	digit;

	if (n >= 10)
	{
		count = ft_putubr(n / 10, count);
		if (count == -1)
			return (-1);
		count = ft_putubr(n % 10, count);
		if (count == -1)
			return (-1);
	}
	else
	{
		digit = n + '0';
		if (safe_write(&digit, 1, &count) == -1)
			return (-1);
	}
	return (count);
}
