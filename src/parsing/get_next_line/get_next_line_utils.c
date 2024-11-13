/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:39:15 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/04 06:10:03 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

char	*ft_strdup(char *s1)
{
	char			*dest;
	unsigned int	i;

	dest = (char *) malloc(ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, int start, int len)
{
	int	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	len;
	int	i;
	char	*str;
	int	length;

	length = ft_strlen(s1);
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	len = length + ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i < length)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		str[i] = s2[i - length];
		i++;
	}
	str[i] = '\0';
	return (str);
}
