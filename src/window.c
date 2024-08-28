/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:23:24 by aherbin           #+#    #+#             */
/*   Updated: 2024/08/28 11:50:05 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	window_exit(t_so_long *game, int status)
{
	if (game->text)
		text_clear(game);
	if (game->img)
		image_clear(game);
	if (game->player_info)
		free(game->player_info);
	if (game->map)
		free_map(game->map);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	if (game)
		free(game);
	if (status == EXIT_FAILURE)
		ft_exit((char *)mlx_strerror(mlx_errno), mlx_errno);
	else if (status == 2)
		ft_exit("The assets size is invalid", EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static t_so_long	*canvas_setup(t_so_long *game, t_player *player)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	while (game->map[i])
		++i;
	j = 0;
	while (game->map[0][j])
		++j;
	game->width = j - 1;
	game->height = i;
	game->img = NULL;
	game->player_info = player;
	game->player_info->move = 0;
	game->mlx = mlx_init(game->width * SIZE, \
	game->height * SIZE, "So Long", true);
	mlx_set_window_limit(game->mlx, -1, -1, \
	game->width * SIZE, game->height * SIZE);
	if (!game->mlx)
		window_exit(game, EXIT_FAILURE);
	texture_setup(game);
	return (game);
}

static void	win_display(t_so_long *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			mlx_image_to_window(game->mlx, game->img->bg, j * SIZE, i * SIZE);
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, \
	game->img->wall, j * SIZE, i * SIZE);
			else if (game->map[i][j] == 'C')
				mlx_image_to_window(game->mlx, \
	game->img->col, j * SIZE, i * SIZE);
			else if (game->map[i][j] == 'E')
				mlx_image_to_window(game->mlx, game->img->exit, \
	j * SIZE, i * SIZE);
			++j;
		}
		++i;
	}
	mlx_image_to_window(game->mlx, game->img->player, \
	game->player_info->player_y * SIZE, game->player_info->player_x * SIZE);
}

void	win_setup(char **map, t_so_long *game, t_player *player)
{
	game = malloc(sizeof(t_so_long));
	if (!game)
		window_exit(game, EXIT_FAILURE);
	game->map = map;
	canvas_setup(game, player);
	game->player_info->move = 0;
	win_display(game);
	mlx_key_hook(game->mlx, ft_key_hook, game);
	mlx_loop(game->mlx);
	window_exit(game, EXIT_SUCCESS);
}
