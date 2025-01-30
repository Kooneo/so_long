/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:46:29 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:58:32 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	safe_write(const char *str, int len, int *count)
{
	int	result;

	result = write(1, str, len);
	if (result == -1)
		return (-1);
	*count += result;
	return (result);
}
