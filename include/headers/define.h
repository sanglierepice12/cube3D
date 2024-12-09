/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:48:09 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/07 11:24:10 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*################ KEY MACROS #####################*/

// ROTATION KEYS

# define UP_KEY        65362
# define DOWN_KEY      65364
# define LEFT_KEY      65361
# define RIGHT_KEY     65363

// MOVEMENT KEYS

# define W_KEY         119
# define A_KEY         97
# define S_KEY         115
# define D_KEY         100
# define ESC_KEY       65307

/*################### DEBUG COLORS #######################*/

# define WRESET   "\033[0m"      // Reset color
# define WRED     "\033[31m"     // Debug Red
# define WGREEN   "\033[32m"     // Debug Green

/*################### COLORS #######################*/

# define BLUE        0x0000FF
# define WHITE       0xFFFFFFF
# define BLACK       0x0000000
# define YELLOW      0xFFFF00
# define GREEN       0x00FF00
# define LIGHT_BLUE  0xADD8E6
# define RED         0xFF0000
# define PINK        0xFFC0CB
# define COLOR_UP    0x0000FF
# define COLOR_DOWN  0x00FF00
# define COLOR_LEFT  0xFF0000
# define COLOR_RIGHT 0xFFFF00

/*#################### MOVEMENTS ######################*/

# define ROTATION_SPEED 0.1f
# define MOVE_SPEED     5.0f

/*#################### DIRECTIONS ######################*/

# define NORTH 0
# define SOUTH 1
# define EAST  2
# define WEST  3

/*#################### ANGLES ######################*/

# define M_PI           3.14159265358979323846
# define FOV_ANGLE      (M_PI / 3.0f)
# define FOV_HALF       (FOV_ANGLE * 0.5f)

/*#################### DIMENSIONS ######################*/

// FULL GAME

# define GAME_WIDTH     1024.0f
# define GAME_HEIGHT    720.0f

// MAP ITEMS

# define TILE_SIZE      16.0f
# define PLAYER_SIZE    16.0f
# define BORDER_SIZE    0.5f


/*#################### CALCULATIONS ######################*/

# define DISTANCE_TO_PLANE ((GAME_WIDTH / 2.0f) / tan(FOV_HALF))
# define SCREEN_CENTER_X   (GAME_WIDTH / 2.0f)
# define SCREEN_CENTER_Y   (GAME_HEIGHT / 2.0f)
# define RAY_ANGLE_DELTA   (FOV_ANGLE / GAME_WIDTH)
# define DISTANCE(x1, y1, x2, y2) \
    sqrt(pow((x2) - (x1), 2) + pow((y2) - (y1), 2))

#endif // DEFINE_H
