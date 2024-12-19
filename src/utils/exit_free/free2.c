/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:01:45 by sanglier          #+#    #+#             */
/*   Updated: 2024/11/22 13:01:45 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	force_exit(char *line, t_game *game)
{
	printf("Error, map invalid, line : \"%s\"\n", line);
	free_list(game->list);
	free(line);
	exit_prog(game);
}

void	free_parse(t_game *game)
{
	if (!game)
		return ;
	free_s_map(game->map);
}
