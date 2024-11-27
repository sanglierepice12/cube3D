/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:33:45 by jedusser          #+#    #+#             */
/*   Updated: 2024/01/15 10:14:25 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static char	*_fill_line_buffer(int fd, char *left_chars, char *buffer);
static char	*_set_line(char *line);
static char	*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	static char	*left_chars;
	char		*line;
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_chars);
		free(buffer);
		left_chars = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = _fill_line_buffer(fd, left_chars, buffer);
	free(buffer);
	if (!line)
		return (NULL);
	left_chars = _set_line(line);
	return (line);
}

static char	*_set_line(char *line_buffer)
{
	ssize_t	i;
	char	*left_chars;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[1] == '\0')
		return (NULL);
	left_chars = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (!left_chars || *left_chars == '\0')
	{
		free(left_chars);
		left_chars = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (left_chars);
}

static char	*_fill_line_buffer(int fd, char *line_buffer, char *buffer)
{
	ssize_t	rd;
	char	*tmp;

	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			free(line_buffer);
			return (NULL);
		}
		if (rd == 0)
			break ;
		buffer[rd] = '\0';
		if (!line_buffer)
			line_buffer = ft_strdup("");
		tmp = line_buffer;
		line_buffer = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line_buffer);
}

static char	*ft_strchr(char *string, int searchedChar)
{
	int		i;
	int		str_len;
	char	needle;

	needle = searchedChar;
	str_len = ft_strlen(string);
	i = 0;
	while (i <= str_len)
	{
		if (string[i] == needle)
			return ((char *)&string[i]);
		if (needle == '\0')
			return ((char *)&string[str_len]);
		else
			i++;
	}
	return (NULL);
}
