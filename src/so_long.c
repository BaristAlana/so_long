/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:16:25 by aherbin           #+#    #+#             */
/*   Updated: 2024/09/02 15:45:28 by aherbin          ###   ########.fr       */
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
	if (!player)
		exit_invalid_map(map, NULL);
	check_map(map, player);
	map_2 = read_map(argv[1]);
	if (!flood_fill(map_2, player))
		exit_invalid_map(map, player);
	game = NULL;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	win_setup(map, game, player);
}
