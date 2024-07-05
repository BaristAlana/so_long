/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:16:25 by aherbin           #+#    #+#             */
/*   Updated: 2024/07/05 14:39:08 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	char		**map;
	char		**map_2;
	t_player	*player;
	t_so_long	*game;

	if (argc != 2 || (argc == 2 && !argv[1]) || check_file_extension(argv[1]))
		ft_exit("Wrong number of arguments", EXIT_FAILURE);
	map = read_map(argv[1]);
	player = ft_calloc(1, sizeof(t_player));
	check_map(map, player);
	if (!player)
		exit_invalid_map(map);
	map_2 = read_map(argv[1]);
	if (!flood_fill(map_2, player))
		exit_invalid_map(map);
	game = NULL;
	win_setup(map, game, player);
}
