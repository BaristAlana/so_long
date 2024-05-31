/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:24:31 by aherbin           #+#    #+#             */
/*   Updated: 2024/05/31 12:39:20 by aherbin          ###   ########.fr       */
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

static void depth_first_search(char **map, int x, int y)
{
	int	i;
	int	j;

	i = len_arr(map);
	j = ft_strlen(map[0]);
	if ((x < 0 || x >= i || y < 0 || y >= j) || (map[x][y] != 'P' && map[x][y] != '0'))
		return ;
	ft_putendl_fd("test", 1);
	map[x][y] = '.';
	depth_first_search(map, x + 1, y);
	depth_first_search(map, x - 1, y);
	depth_first_search(map, x, y + 1);
	depth_first_search(map, x, y - 1);
}

void	flood_fill(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] && map[i][j] != 'P')
	{
		j = 0;
		while (map[i][j] && map[i][j] != 'P')
		{
			if (map[i][j] == 'P')
				break;
			else
				++j;
		}
		if (map[i][j] != 'P')
			++i;
	}
	depth_first_search(map, i, j);
	ft_printf("i = %i, j = %i \n", i, j);
}
