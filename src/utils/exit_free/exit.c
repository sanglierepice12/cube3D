/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:20:32 by gsuter            #+#    #+#             */
/*   Updated: 2024/12/18 15:26:09 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	simple_exit(char *msg, int code)
{
	if (write(2, msg, ft_strlen(msg)) == -1)
		exit(2);
	exit(code);
}

void	exit_prog(t_game *game)
{
	clean_textures(&game->mlx_data, game->map->tex);
	free_parse(game);
	clean_up(game);
	free(game);
	exit(0);
}
