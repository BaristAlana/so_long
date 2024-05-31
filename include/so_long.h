/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:15:18 by aherbin           #+#    #+#             */
/*   Updated: 2024/05/31 10:53:15 by aherbin          ###   ########.fr       */
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

void	check_map(char **map);

char	**read_map(char *file);

#endif
