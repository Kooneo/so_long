/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:42:54 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:58:47 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_handle_negative(int *n, int *count)
{
	if (safe_write("-", 1, count) == -1)
		return (-1);
	*n = -(*n);
	return (*n);
}

int	ft_putnbr(int n, int count)
{
	char	digit;

	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		if (ft_putnbr_handle_negative(&n, &count) == -1)
			return (-1);
	}
	if (n >= 10)
	{
		count = ft_putnbr(n / 10, count);
		if (count == -1)
			return (-1);
		count = ft_putnbr(n % 10, count);
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
