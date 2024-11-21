/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:20:32 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/13 13:20:32 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	exit_prog(char *msg, int code)
{
	printf("%s", msg);
	exit(code);
}

void	exit_parse(t_game *game)
{
	free_list(game->list);
	if (game->map->texture)
		free_texture(game->map->texture);
	printf("parsing has exited with security");
	exit(1);
}
