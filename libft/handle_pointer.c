/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:31:19 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:58:21 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_pointer(va_list args)
{
	int			count;
	void		*p;
	uintptr_t	address;

	count = 0;
	p = va_arg(args, void *);
	if (p == NULL)
		return (write(1, "(nil)", 5));
	address = (uintptr_t)p;
	if (safe_write("0x", 2, &count) == -1)
		return (-1);
	if (ft_puthex("0123456789abcdef", address, &count) == -1)
		return (-1);
	return (count);
}
