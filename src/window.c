/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:23:24 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/04 15:40:03 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	if (!game->mlx)
		window_exit(game, EXIT_FAILURE);
	ft_printf("x= %i, y= %i\n", game->width, game->height);
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

int	win_setup(char **map, t_so_long *game, t_player *player)
{
	game = ft_calloc(1, sizeof(t_so_long));
	if (!game)
		window_exit(game, EXIT_FAILURE);
	game->map = map;
	canvas_setup(game, player);
	game->player_info->move = 0;
	win_display(game);
	mlx_key_hook(game->mlx, ft_key_hook, game);
	mlx_loop(game->mlx);
	window_exit(game, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
