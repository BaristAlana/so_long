/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:15:18 by aherbin           #+#    #+#             */
/*   Updated: 2024/08/28 12:26:38 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/MLX42/include/MLX42/MLX42.h"

# include "../lib/libft/include/libft.h"

# include <stdlib.h>

# include <math.h>

# include <unistd.h>

# include <fcntl.h>

/**
 * @brief A structure hosting useful information about the player character
 *
 * @param player_x X coordinates of the P char on the map
 * @param player_y Y coordinates of the P char on the map
 * @param exit_x X coordinates of the E char on the map
 * @param exit_y Y coordinates of the P char on the map
 * @param collec Number of collected items
 * @param total_col Total number of collectibles present on the map
 * @param move Number of moves
 */
typedef struct s_player
{
	int	player_x;
	int	player_y;
	int	exit_x;
	int	exit_y;
	int	collec;
	int	total_col;
	int	move;
}				t_player;

/**
 * @brief Temporary structure used to hold the loaded PNG infos
 *
 * @param name Correspond to each assets
 */
typedef struct s_text
{
	mlx_texture_t	*bg;
	mlx_texture_t	*wall;
	mlx_texture_t	*col;
	mlx_texture_t	*exit;
	mlx_texture_t	*player;
}				t_text;

/**
 * @brief Structure used to hold all images used by MLX
 *
 * @param name Correspond to each assets
 */
typedef struct s_img
{
	mlx_image_t	*bg;
	mlx_image_t	*wall;
	mlx_image_t	*col;
	mlx_image_t	*exit;
	mlx_image_t	*player;
}				t_img;

/**
 * Main structure used to store all informations recquired by the game;
 *
 * @param player_info Pointer to a t_player structure
 * @param map Pointer to the map array
 * @param mlx Directly point to the mlx instance used
 * @param width width of the window to render, in number of tiles;
 * Will later be multiplied by the assets resolution
 * @param height same as for the width, but for the evrtical axis
 * @param img Pointer to a t_img struc,
 * used to store all the images we'll be using
 * @param text Pointer to a texture array,
 * used as a temporary buffer to load and transform PNG into images
 */
typedef struct s_so_long
{
	t_player	*player_info;
	char		**map;
	mlx_t		*mlx;
	int32_t		width;
	int32_t		height;
	t_img		*img;
	t_text		*text;
}				t_so_long;

/**
 * @brief the resolution in pixels of the assets
 * Each image has to be square, and of the same resolution
 * Said resolution can be changed on compile with SIZE=*size*
 */
# ifndef SIZE
#  define SIZE 64
# endif

/* ************************************************************************** */
/*                                  Assets                                    */
/* ************************************************************************** */

# define bg_png "./assets/background.png"

# define wall_png "./assets/wall.png"

# define player_png "./assets/player.png"

# define collec_png "./assets/collec.png"

# define exit_png "./assets/exit.png"

/* ************************************************************************** */
/*                                 so_long.c                                  */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                  utils.c                                   */
/* ************************************************************************** */

/**
 * Explicit enough
 *
 * @param[in] file ARGV[1], the string to check
 * @returns 0 if it's a .ber file, something else if it's something else
 */
int		check_file_extension(char *file);

/**
 * Generic exit functionthat also allows the use of a custom exit message
 *
 * @param errmsg The message to display in itself
 * @param status The exit status; EXIT_SUCCESS or EXIT_FAILURE (0 || 1)
 */
void	ft_exit(char *errmsg, int status);

/**
 * Generic function to free a 2D array
 *
 * @param map The array to free
 */
void	free_map(char **map);

/**
 * wrapper function to exit on a map error, while making sure everything is freed
 *
 * @param map The array to free
 */
void	exit_invalid_map(char **map);

/**
 * a function used to count the lines on a file, using GNL
 *
 * @param fd The file descriptor pointing to the file being read
 * @returns An int >= 0, describing the number of lines
 */
int		n_line_gnl(int fd);

/* ************************************************************************** */
/*                                 map_tools.c                                */
/* ************************************************************************** */

/**
 * @brief A wrapper function to check a 2D array (the map) for all kind of errors
 * Also add infos to the player structure
 *
 * @param map The array to check
 * @param player A pointer to the t_player struct
 */
void	check_map(char **map, t_player *player);

/**
 * @brief The file parser; This function reads the .ber file to create a 2D array
 * Will only proceeds if the file exist and is valid.
 *
 * @param file The file path/name, ARGV[1]
 * @return A **char pointer allocated on the heap with all the map infos
 */
char	**read_map(char *file);

/* ************************************************************************** */
/*                                flood_fill.c                                */
/* ************************************************************************** */

/**
 * @brief This function checks the validity of the map;
 * Specifically, both the number of items (exit, player and collectibles)
 * but also checks by DFS if a there is a valid path between the player and
 * the exit without missing any collectible.
 *
 * It works by creating a duplicate of the map and by changing all characters
 * that are not an exit or a wall to a '.'. When the map has been fully filled,
 * it frees it.
 *
 * It also fills the plyer_info (t_player) struct with useful info such as
 * total number of collectibles, starting coordinates, exit coordinates, etc.
 *
 * @param map A duplicate of the map to check
 * @param player The t_player structure that has to be filled
 * @return A boolean; 0 for an invalid map, 1 for a valid one
 */
int		flood_fill(char **map, t_player *player);

/* ************************************************************************** */
/*                                  window.c                                  */
/* ************************************************************************** */

/**
 * @brief A generic garbage collector to exit the program after a MLX instance
 * has been launched. It frees every allocated space of the game structure and
 * properly terminate the MLX instance.
 *
 * @param game The t_so_long struct to clean
 * @param status exit status
 */
void	window_exit(t_so_long *game, int status);

/**
 * @brief Setups the window in itself; starts the MLX instance, creates the
 * t_so_long (game) structure and fills it with all the recquired infos through
 * canvas_setu[(), etc.
 *
 * It also initialize the render and start the loop for both the display and the
 * key hooks.
 *
 * @param map The map array
 * @param game A pointer to the game stuct
 * @param player A pointer to the t_player struct used to fill game
 */
void	win_setup(char **map, t_so_long *game, t_player *player);

/* ************************************************************************** */
/*                                 win_utils.c                                */
/* ************************************************************************** */

/**
 * @brief Garbage collector that frees every texture inside a t_text structure
 *
 * @param game The t_so_long struct hosting the t_text struct to be free
 */
void	text_clear(t_so_long *game);

/**
 * @brief Garbage collector that frees every image inside a t_img structure
 *
 * @param game The t_so_long struct hosting the t_img struct to be free
 */
void	image_clear(t_so_long	*game);

/**
 * @brief This function sets up the t_text struct inside the main game struct
 * by loading all the assets.
 *
 * @param game The main game (t_so_long) structure.
 */
void	texture_setup(t_so_long *game);

/**
 * @brief This function sets up the t_img struct inside the main game struct
 * by converting the texture buffers to images.
 *
 * It then free the t_text struct.
 *
 * @param game The main game (t_so_long) structure.
 */
void	image_setup(t_so_long *game);

/* ************************************************************************** */
/*                                 movement.c                                 */
/* ************************************************************************** */

/**
 * @brief Generic key hook function used to detect escape, WASD or arrows press
 * while the program is running.
 *
 * @param keydata The pressed key and its status
 * @param param A pointer to the game structure, used by the function to move
 * the player
 */
void	ft_key_hook(mlx_key_data_t keydata, void *param);

/* ************************************************************************** */
/*                                   score.c                                  */
/* ************************************************************************** */

/**
 * @brief A function called everytime the player moves, to check if a
 * collectible has been found and to delete it from the game if so.
 * Also updates the score inside the t_player struct to activate the exit if
 * all collectibles have been found.
 *
 * @param game  t_so_long; the main game structure
 */
void	ft_collec(t_so_long *game);

#endif
