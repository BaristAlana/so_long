/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:15:18 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/03 11:00:45 by aherbin          ###   ########.fr       */
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
	int	score;
}				t_player;

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
/*                                 so_long.c                                  */
/* ************************************************************************** */

int	flood_fill(char **map, t_player *player);

#endif
