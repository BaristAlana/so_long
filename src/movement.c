/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:21:36 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/04 15:25:33 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_up(t_so_long *game)
{
	if (game->map[game->img->player->instances->y / SIZE - 1]
		[game->img->player->instances->x / SIZE] != '1')
	{
		game->img->player->instances->y -= SIZE;
		game->player_info->move += 1;
		ft_printf("Move: %i\n", \
	game->player_info->move, game->player_info->collec);
	}
}

void	move_right(t_so_long *game)
{
	if (game->map[game->img->player->instances->y / SIZE]
		[game->img->player->instances->x / SIZE + 1] != '1')
	{
		game->img->player->instances->x += SIZE;
		game->player_info->move += 1;
		ft_printf("Move: %i\n", \
	game->player_info->move, game->player_info->collec);
	}
}

void	move_down(t_so_long *game)
{
	if (game->map[game->img->player->instances->y / SIZE + 1]
		[game->img->player->instances->x / SIZE] != '1')
	{
		game->img->player->instances->y += SIZE;
		game->player_info->move += 1;
		ft_printf("Move: %i\n", \
	game->player_info->move, game->player_info->collec);
	}
}

void	move_left(t_so_long *game)
{
	if (game->map[game->img->player->instances->y / SIZE]
		[game->img->player->instances->x / SIZE - 1] != '1')
	{
		game->img->player->instances->x -= SIZE;
		game->player_info->move += 1;
		ft_printf("Move: %i\n", \
	game->player_info->move, game->player_info->collec);
	}
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_so_long	*game;

	game = param;
	if ((keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE))
		move_up(game);
	if ((keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE))
		move_right(game);
	if ((keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE))
		move_down(game);
	if ((keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE))
		move_left(game);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx);
	ft_collec(game);
}
