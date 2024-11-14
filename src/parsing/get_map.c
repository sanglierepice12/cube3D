/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:42:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/14 13:03:39 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3D.h"


void free_tab(char **tab)
{
    int y = 0;
    while (tab[y])
	{
        free(tab[y]);
        y++;
    }
    free(tab);
}

void print_tab(char **tab)
{
    int y = 0;
    printf("===========FILLED TAB ==========\n");
    while (tab[y])
	{
        printf("%s\n", tab[y]);
        y++;
    }
    printf("\n");
}

int allocate_tab(t_map *map)
{
    int y = 0;
    while (y < map->map_height)
	{
        map->map[y] = calloc(map->map_length + 1, sizeof(char));
        if (!map->map[y])
            return (free_tab(map->map), -1);
        y++;
    }
    map->map[y] = NULL; 
    return 0;
}

int fill_tab(t_map *map)
{
    char *line;
    int fd;
    int y = 0;
    int i;

   
    if (allocate_tab(map) != 0)
        return (-1);

    fd = open("./map/map.cub", O_RDONLY);
    if (fd == -1)
        return (-1);

    line = get_next_line(fd);
    while (line && y < map->map_length)
	{
        i = 0;
        while (i < map->map_length && line[i] != '\0')
		{
            map->map[y][i] = line[i];
            i++;
        }
        y++;

        free(line);
        line = get_next_line(fd);
    }
   // print_tab(map->map);
    close(fd);
    return (0);
}