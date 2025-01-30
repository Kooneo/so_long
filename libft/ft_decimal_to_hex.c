/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_to_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:14:56 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:58:47 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_decimal_to_hex(char *base, unsigned int num)
{
	char	hex[20];
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (num == 0)
	{
		if (safe_write("0", 1, &count) == -1)
			return (-1);
		return (count);
	}
	while (num > 0)
	{
		hex[i] = base[num % 16];
		num /= 16;
		i++;
	}
	while (i > 0)
	{
		i--;
		if (safe_write(&hex[i], 1, &count) == -1)
			return (-1);
	}
	return (count);
}
