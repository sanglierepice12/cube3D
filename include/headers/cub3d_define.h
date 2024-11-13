/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:48:09 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/12 11:29:05 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_DEFINE_H
# define CUBE3D_DEFINE_H

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

/*################ SIZE MACROS #####################*/

# define TILE_SIZE 64
# define PLAYER_SIZE 16
# define BORDER_SIZE 0.5
//#define STEP_SIZE 10
# define ROTATION_SPEED 0.1
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
# define FOV_ANGLE (M_PI / 3)
# define RAY_COUNT 1920
# define GAME_WIDTH 1920
# define GAME_HEIGHT 780
# define DISTANCE_TO_PLANE ((GAME_WIDTH * 0.5) / tan(FOV_ANGLE * 0.5))
//#define DISTANCE_TO_PLANE GAME_WIDTH / (2 * tan(FOV_ANGLE / 2))


#endif