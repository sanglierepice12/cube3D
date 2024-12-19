/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostr <gostr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 08:37:39 by gsuter            #+#    #+#             */
/*   Updated: 2024/04/09 11:40:40 by gostr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	ft_bz(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		str[i] = 0;
		i++;
	}
}

void	ft_clean_buf(char *buf)
{
	ssize_t	i;
	ssize_t	j;

	i = 0;
	while (buf[i] != '\n' && buf[i])
		i++;
	if (buf[i] == '\n')
		i++;
	j = 0;
	while (buf[i + j])
	{
		buf[j] = buf[i + j];
		j++;
	}
	buf[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		bytes_readed;
	char		*line;

	bytes_readed = 1;
	if (read(fd, buf, 0) < 0 || fd < 0)
		return (ft_bz(buf), NULL);
	line = ft_strdup(buf);
	if (!line)
		return (free(line), NULL);
	while (!ft_end(line) && bytes_readed)
	{
		bytes_readed = read(fd, buf, BUFFER_SIZE);
		if (bytes_readed < 0)
			return (ft_bz(buf), free(line), NULL);
		buf[bytes_readed] = '\0';
		line = ft_strjoin(line, buf);
		if (!line)
			return (NULL);
	}
	ft_clean_buf(buf);
	if (line[0] == 0)
		return (free(line), NULL);
	return (line);
}
