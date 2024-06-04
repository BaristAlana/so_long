/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:15:18 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/04 15:31:43 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"

# include "libft.h"

# include <stdlib.h>

# include <math.h>

# include <unistd.h>

# include <fcntl.h>

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

typedef struct s_text{
	mlx_texture_t	*bg;
	mlx_texture_t	*wall;
	mlx_texture_t	*col;
	mlx_texture_t	*exit;
	mlx_texture_t	*player;
}				t_text;

typedef struct s_img{
	mlx_image_t	*bg;
	mlx_image_t	*wall;
	mlx_image_t	*col;
	mlx_image_t	*exit;
	mlx_image_t	*player;
}				t_img;

typedef struct s_so_long {
	t_player	*player_info;
	char		**map;
	mlx_t		*mlx;
	int32_t		width;
	int32_t		height;
	t_img		*img;
	t_text		*text;
}				t_so_long;

# ifndef SIZE
#  define SIZE 128
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

int		check_file_extension(char *file);

int		ft_exit(char *errmsg, int status);

void	free_map(char **map);

void	exit_invalid_map(char **map);

int		n_line_gnl(int fd);

/* ************************************************************************** */
/*                                 map_tools.c                                */
/* ************************************************************************** */

void	check_map(char **map, t_player *player);

char	**read_map(char *file);

/* ************************************************************************** */
/*                                flood_fill.c                                */
/* ************************************************************************** */

int	flood_fill(char **map, t_player *player);

/* ************************************************************************** */
/*                                  window.c                                  */
/* ************************************************************************** */

void	image_setup(t_so_long *game);

void	image_clear(t_so_long	*game);

void	texture_setup(t_so_long *game);

int		win_setup(char **map, t_so_long *game, t_player *player);



void	ft_key_hook(mlx_key_data_t keydata, void *param);


void	window_exit(t_so_long *game, int status);


void	ft_collec(t_so_long *game);

#endif
