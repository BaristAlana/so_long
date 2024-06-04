/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:08:05 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/04 15:22:20 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	delete_collec(t_so_long *game)
{
	int	i;
	int	count;

	i = 0;
	count = game->player_info->total_col;
	while (i < count)
	{
		if (((game->img->col->instances[i].y
					== game->img->player->instances->y)
				&& (game->img->col->instances[i].x
					== game->img->player->instances->x))
			&& game->img->col->instances[i].enabled == true)
		{
			count--;
			game->img->col->instances[i].enabled = false;
			return ;
		}
		i++;
	}
}

void	ft_collec(t_so_long *game)
{
	if (game->map[game->img->player->instances->y / SIZE]
		[game->img->player->instances->x / SIZE] == 'C')
	{
		delete_collec(game);
		game->map[game->img->player->instances->y / SIZE]
		[game->img->player->instances->x / SIZE] = '0';
		game->player_info->collec++;
	}
	if (game->map[game->img->player->instances->y / SIZE]
		[game->img->player->instances->x / SIZE] == 'E')
	{
		if (game->player_info->collec == game->player_info->total_col)
			mlx_close_window(game->mlx);
	}
}
