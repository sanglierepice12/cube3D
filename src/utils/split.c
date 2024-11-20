/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:35:58 by sanglier          #+#    #+#             */
/*   Updated: 2024/11/20 17:35:58 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	if (s[i] != c && s[i] != 0)
		words++;
	i++;
	while (s[0] && s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

static size_t	ft_wdlen(char const *s, char c, size_t j)
{
	size_t	i;

	i = j;
	while (s[i] != c && s[i] != 0)
		i++;
	return (i);
}

static char	*ft_superdup(char const *s, char c, size_t *j)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_wdlen(s, c, *j);
	str = malloc(sizeof(char) * (len - *j + 1));
	if (str == NULL)
		return (str);
	i = 0;
	while (*j < len)
	{
		str[i] = s[*j];
		*j += 1;
		i++;
	}
	str[i] = 0;
	return (str);
}

void	*ft_free_tab(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return (NULL);
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	words;
	char	**split;

	i = 0;
	j = 0;
	words = ft_countwords(s, c);
	split = ft_calloc((words + 1), sizeof(char *));
	if (!s[0] || split == NULL)
		return (free(split), NULL);
	while (i < words)
	{
		if (s[j] != c)
		{
			split[i++] = ft_superdup(s, c, &j);
			if (split[i - 1] == NULL)
				return (ft_free_tab(split), exit(0), NULL);
		}
		else
			j++;
	}
	return (split);
}
