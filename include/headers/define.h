/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:48:09 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/26 10:35:20 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*################ KEY MACROS #####################*/

# define UP_KEY        65362
# define DOWN_KEY      65364
# define LEFT_KEY      65361
# define RIGHT_KEY     65363
# define W_KEY         119
# define A_KEY         97
# define S_KEY         115
# define D_KEY         100
# define ESC_KEY       65307

/*################### COLORS #######################*/

# define BLUE  0x0000FF
# define WHITE 0xFFFFFFF
# define GREEN 0x00FF000
# define BLACK 0x0000000
# define PINK  0X0FFC0CB
# define RED  0XFF0000
# define YELLOW  0xFFFF00
# define LIGHT_BLUE 0xADD8E6

# define COLOR_UP    0x0000FF    // Blue for up-facing walls
# define COLOR_DOWN  0x00FF00    // Green for down-facing walls
# define COLOR_LEFT  0xFF0000    // Red for left-facing walls
# define COLOR_RIGHT 0xFFFF00    // Yellow for right-facing walls

/*################ SIZE MACROS #####################*/

# define TILE_SIZE 32
# define PLAYER_SIZE 16
# define BORDER_SIZE 0.5
# define ROTATION_SPEED 0.1
# define MOVE_SPEED 5
# define M_PI 3.14159265358979323846
# define FOV_ANGLE (M_PI / 3)
# define RAY_COUNT 1920
# define GAME_WIDTH 1920
# define GAME_HEIGHT 780

/*#################### CALCULATION MACROS ######################*/

# define DISTANCE_TO_PLANE ((GAME_WIDTH * 0.5) / tan(FOV_ANGLE * 0.5))
# define SCREEN_CENTER_X     (GAME_WIDTH / 2)
# define SCREEN_CENTER_Y     (GAME_HEIGHT / 2)
# define FOV_HALF            (FOV_ANGLE * 0.5)
# define RAY_ANGLE_DELTA     (FOV_ANGLE / (GAME_WIDTH - 1))
# define DISTANCE(x1, y1, x2, y2) sqrt(pow((x2) - (x1), 2) + pow((y2) - (y1), 2))


#endif