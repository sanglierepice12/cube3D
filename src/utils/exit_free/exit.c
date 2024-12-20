/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:20:32 by gsuter            #+#    #+#             */
/*   Updated: 2024/12/20 15:46:40 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

int	ft_puterr(char *str)
{
	write(2, "error: ", 8);
	return (write(2, str, ft_strlen(str)));
}

void	simple_exit(char *msg, int code)
{
	printf("%s", msg);
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
