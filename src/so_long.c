/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:16:25 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/04 11:32:36 by aherbin          ###   ########.fr       */
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
		ft_exit("Please put a valid map file!", EXIT_FAILURE);
	map = read_map(argv[1]);
	player = calloc(1, sizeof(t_player));
	check_map(map, player);
	if (!player)
		exit_invalid_map(map);
	map_2 = read_map(argv[1]);
	if (!flood_fill(map_2, player))
		exit_invalid_map(map);
	game = NULL;
	win_setup(map, game, player);
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

	int	i = 0;


	while (map[i])
	{
		ft_putstr_fd(map[i], 1);
		++i;
	}
	i = 0;
	//while (map_2[i])
	//{
	//	ft_putstr_fd(map_2[i], 1);
	//	++i;
	//}
	//free_map(map_2);
	free_map(map);
	free(player);
}
