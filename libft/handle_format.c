/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:33:55 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:58:08 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_format(char specifier, va_list args, int *count)
{
	if (specifier == 'c')
		return (handle_char(args));
	if (specifier == 's')
		return (handle_string(args));
	if (specifier == 'd' || specifier == 'i')
		return (handle_integer(args));
	if (specifier == 'u')
		return (handle_unsigned(args));
	if (specifier == '%')
		return (handle_percent());
	if (specifier == 'p')
		return (handle_pointer(args));
	if (specifier == 'x')
		return (handle_hex(args, 0));
	if (specifier == 'X')
		return (handle_hex(args, 1));
	if (specifier == '\0')
		return (-1);
	else
	{
		safe_write("%", 1, count);
		safe_write(&specifier, 1, count);
	}
	return (0);
}
