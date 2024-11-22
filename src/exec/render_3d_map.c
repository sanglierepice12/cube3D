/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:39:11 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/22 09:04:09 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	clear_image(t_img_data *img, int ceiling_color, int floor_color)
{
	int	*pixel_data;
	int	half_height;

	pixel_data = (int *)img->addr;
	half_height = GAME_HEIGHT / 2;
	ft_memset(pixel_data, ceiling_color, half_height * GAME_WIDTH * sizeof(int));
	ft_memset(&pixel_data[half_height * GAME_WIDTH], floor_color, half_height * GAME_WIDTH * sizeof(int));
}

void	draw_3d_column(t_game *game)
{
	int	y_start;
	int	y_end;
	int	y;

	y_start = game->projection.wall_start;
	y_end = game->projection.wall_end;
	if (game->raycaster.ray_index >= 0
		&& game->raycaster.ray_index < GAME_WIDTH)
	{
		y = y_start;
		while (y <= y_end)
		{
			if (y >= 0 && y < GAME_HEIGHT)
				my_mlx_pixel_put(&game->game_img, game->raycaster.ray_index, y, BLUE);
			y++;
		}
	}
}
void	ray_caster(t_player *player, t_raycaster *raycaster,
		t_proj *projection)
{
	float	step_x; 
	float	step_y;

	projection->distance_to_wall = DISTANCE(raycaster->ray_x, raycaster->ray_y, player->player_px_pos_x, player->player_px_pos_y);
	projection->wall_height = (int)(TILE_SIZE * DISTANCE_TO_PLANE / projection->distance_to_wall);
	projection->wall_start = SCREEN_CENTER_Y - (projection->wall_height * 0.5);
	projection->wall_end = SCREEN_CENTER_Y + (projection->wall_height * 0.5);
	step_x = cos(raycaster->ray_angle);
	step_y = -sin(raycaster->ray_angle);
	raycaster->ray_x += step_x;
	raycaster->ray_y += step_y;
}

int check_bounds(t_map *map, t_raycaster *raycaster)
{
	return (map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] != '1');
}

void	render_3d_map(t_game *game, t_player *player, t_raycaster *raycaster,
		t_proj *projection)
{
	float	ray_cos;
	float	ray_sin;

	raycaster->ray_index = 0;
	clear_image(&game->game_img, BLACK, LIGHT_BLUE);
	while (raycaster->ray_index < GAME_WIDTH)
	{
		raycaster->ray_angle = player->angle - FOV_HALF + (raycaster->ray_index * RAY_ANGLE_DELTA);
		ray_cos = cos(raycaster->ray_angle);
		ray_sin = sin(raycaster->ray_angle);
		raycaster->ray_x = player->player_px_pos_x;
		raycaster->ray_y = player->player_px_pos_y;
		while (check_bounds(&game->map, raycaster))
		{
			raycaster->ray_x += ray_cos; //horizontal
			raycaster->ray_y += ray_sin; //vertical
		}
		ray_caster(player, raycaster, projection);
		draw_3d_column(game);
		raycaster->ray_index++;
	}
}
/* ************************************************************************** */

/* Synthesis of Explanations: 

1. **Cosine (cos) and Sine (sin)**:
   - These are trigonometric functions used to calculate movement along the x-axis and y-axis based on an angle.
   - `cos(angle)` determines the horizontal (x-axis) movement.
   - `sin(angle)` determines the vertical (y-axis) movement.

2. **Why Increment Using cos and sin?**:
   - Raycasting involves tracing a ray from the player's position in a specific direction.
   - By incrementing the ray’s x and y positions using cos and sin of the ray’s angle, the ray moves smoothly in the correct direction.

3. **Unit Circle**:
   - The unit circle relates angles to positions in a 2D plane.
   - For any angle, `cos(angle)` gives the x-coordinate, and `sin(angle)` gives the y-coordinate of a point on the circle.

4. **Applications in This Code**:
   - The code calculates steps (`step_x` and `step_y`) using `cos` and `sin`, which represent small movements in the ray’s direction.
   - These small steps allow the ray to check for collisions with walls incrementally.

5. **Raycasting Overview**:
   - A ray is cast for every screen column, calculating where the ray hits a wall.
   - The distance to the wall determines the wall's height on the screen.
   - This process creates the illusion of depth in a 3D-rendered environment.

By using these principles, the code achieves realistic 3D rendering for a 2D game world.
*/