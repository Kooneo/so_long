/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:03:02 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/11 15:16:23 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == 2147483647)
		return (10);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	fill_string(char *result, long long nb, size_t str_len,
		int is_negative)
{
	int	c;

	result[str_len] = '\0';
	while (str_len--)
	{
		c = nb % 10;
		nb = nb / 10;
		result[str_len] = c + '0';
	}
	if (is_negative)
		result[0] = '-';
}

char	*ft_itoa(int n)
{
	size_t		str_len;
	char		*result;
	short int	is_negative;
	long long	nb;

	nb = (long long)n;
	is_negative = 0;
	str_len = ft_intlen(nb);
	if (nb == 0)
		return (ft_strdup("0"));
	if (nb < 0)
	{
		nb = -nb;
		is_negative = 1;
	}
	result = (char *)malloc((str_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	fill_string(result, nb, str_len, is_negative);
	return (result);
}
