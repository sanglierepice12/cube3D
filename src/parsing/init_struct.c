/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:47:55 by sanglier          #+#    #+#             */
/*   Updated: 2024/11/22 11:47:55 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	have_double_ext(t_tex *tex)
{
	if (ft_comp_str(tex->no, tex->so) || ft_comp_str(tex->no, tex->we) || \
			ft_comp_str(tex->no, tex->ea))
		return (true);
	if (ft_comp_str(tex->so, tex->no) || ft_comp_str(tex->so, tex->we) || \
			ft_comp_str(tex->so, tex->ea))
		return (true);
	if (ft_comp_str(tex->we, tex->so) || ft_comp_str(tex->we, tex->no) || \
			ft_comp_str(tex->we, tex->ea))
		return (true);
	if (ft_comp_str(tex->ea, tex->so) || ft_comp_str(tex->ea, tex->no) || \
			ft_comp_str(tex->ea, tex->we))
		return (true);
	return (false);
}

bool	init_map(t_map **map)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!(*map))
		return (false);
	ft_bzero((*map)->matt, sizeof((*map)->matt));
	(*map)->tex = ft_calloc(1, sizeof(t_tex));
	if (!(*map)->tex)
		return (false);
	(*map)->ceiling = ft_calloc(1, sizeof(t_rgb));
	if (!(*map)->ceiling)
		return (false);
	(*map)->floor = ft_calloc(1, sizeof(t_rgb));
	if (!(*map)->floor)
		return (false);
	return (true);
}

void	init_struct(t_game **game)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (!(*game))
		simple_exit("Error init game\n", 1);
	(*game)->list = NULL;
	if (!init_map(&(*game)->map))
		exit_prog(*game);
}
