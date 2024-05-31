/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:24:31 by aherbin           #+#    #+#             */
/*   Updated: 2024/05/31 14:59:53 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	len_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		++i;
	return (i - 1);
}

static void	depth_first_search(char **map, int x, int y)
{
	int	i;
	int	j;

	i = len_arr(map);
	j = ft_strlen(map[0]);
	if ((x < 0 || x >= i || y < 0 || y >= j) || \
	(map[x][y] != 'P' && map[x][y] != '0' && map[x][y] != 'C'))
		return ;
	map[x][y] = '.';
	depth_first_search(map, x + 1, y);
	depth_first_search(map, x - 1, y);
	depth_first_search(map, x, y + 1);
	depth_first_search(map, x, y - 1);
}

void	fill_struct(char c, int x, int y, t_player *player)
{
	if (c == 'P')
	{
		player->player_x = x;
		player->player_y = y;
	}
	else if (c == 'E')
	{
		player->exit_x = x;
		player->exit_y = y;
	}
}

void	find_coord(char **map, t_player *player, char c)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (map[i] && map[i][j] != c)
	{
		j = 0;
		while (map[i][j] && map[i][j] != c)
		{
			if (map[i][j] == c)
				break ;
			else
				++j;
		}
		if (map[i][j] != c)
			++i;
	}
	fill_struct(c, i, j, player);
	fill_struct(c, i, j, player);
}

int	flood_fill(char **map, t_player *player)
{
	int	i;
	int	j;

	find_coord(map, player, 'P');
	find_coord(map, player, 'E');
	depth_first_search(map, player->player_x, player->player_y);
	i = player->exit_x;
	j = player->exit_y;
//////////////////////////////////////////////////////////////////
	ft_printf("player x = %i, player y = %i\
 \n", player->player_x, player->player_y);
	ft_printf("exit x = %i, exit y = %i \n", player->exit_x, player->exit_y);
//////////////////////////////////////////////////////////////////
	if (map[i + 1][j] == '.' || map[i - 1][j] == '.'\
	|| map[i][j + 1] == '.' || map[i][j - 1] == '.')
	{
		free_map(map);
		return (1);
	}
	free_map(map);
	return (0);
}
