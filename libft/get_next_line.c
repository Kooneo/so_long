/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbakour <zbakour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:49:02 by zbakour           #+#    #+#             */
/*   Updated: 2024/12/21 15:51:28 by zbakour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	read_save(int fd, char **str)
{
	char	*tmp_read;
	int		len_readed;

	tmp_read = malloc((size_t)BUFFER_SIZE + 1);
	if (!tmp_read)
		return ;
	while (!ft_strchr_gn(*str, '\n'))
	{
		len_readed = read(fd, tmp_read, BUFFER_SIZE);
		if (len_readed == -1)
		{
			free(tmp_read);
			free(*str);
			return ;
		}
		tmp_read[len_readed] = '\0';
		if (len_readed == 0)
			break ;
		*str = ft_strjoin_gn(*str, tmp_read);
	}
	free(tmp_read);
}

char	*handle_remaining(char *buff)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	str = malloc(ft_strlen_gn(buff) - i + 1);
	i++;
	if (!str)
		return (NULL);
	j = 0;
	while (buff[i])
		str[j++] = buff[i++];
	str[j] = '\0';
	free(buff);
	return (str);
}

static char	*copy_to_nl(char *str, int index, int is_nl)
{
	int		i;
	char	*f_line;

	i = 0;
	f_line = malloc(index + is_nl + 1);
	if (!f_line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		f_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		f_line[i] = str[i];
		i++;
	}
	f_line[i] = '\0';
	return (f_line);
}

char	*get_string(char *str)
{
	int		i;
	short	is_nl;

	i = 0;
	if (!str || !str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	is_nl = 0;
	if (str[i] && str[i] == '\n')
		is_nl = 1;
	return (copy_to_nl(str, i, is_nl));
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_save(fd, &buff);
	if (!buff)
		return (NULL);
	next_line = get_string(buff);
	buff = handle_remaining(buff);
	return (next_line);
}
