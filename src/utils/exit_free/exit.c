/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:20:32 by gsuter            #+#    #+#             */
/*   Updated: 2024/12/05 15:30:25 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	simple_exit(char *msg, int code)
{
	printf("%s", msg);
	exit(code);
}

/*void	exit_parse(t_game *game)
{
	free_list(game->list);
	if (game->map->texture)
		free_texture(game->map->texture);
	printf("parsing has exited with security");
	exit(1);
}*/

void	exit_prog(t_game *game)
{
	free_parse(game);
	clean_up(game);
	free(game);
	exit(0);
}
