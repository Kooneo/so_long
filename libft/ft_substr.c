/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:29:04 by zbakour           #+#    #+#             */
/*   Updated: 2024/11/11 13:14:23 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*substr_mem;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if ((str_len - start) < len)
		len = str_len - start;
	substr_mem = malloc((len + 1) * sizeof(char));
	if (substr_mem != NULL)
	{
		ft_memcpy(substr_mem, s + start, len);
		substr_mem[len] = '\0';
		return (substr_mem);
	}
	return (NULL);
}
