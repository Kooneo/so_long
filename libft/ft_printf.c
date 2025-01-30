/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:18:07 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:57:58 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_body(const char *s, va_list args, int *count)
{
	int		i;
	short	is_fail;

	i = 0;
	is_fail = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			while (s[i + 1] == ' ')
				i++;
			is_fail = handle_format(s[++i], args, count);
			if (is_fail == -1)
				return (-1);
			else
				*count += is_fail;
		}
		else if (safe_write(&s[i], 1, count) == -1)
			return (-1);
		i++;
	}
	return (*count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;

	if (!s)
		return (-1);
	count = 0;
	va_start(args, s);
	count = ft_printf_body(s, args, &count);
	va_end(args);
	return (count);
}
