/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:23:24 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/04 11:38:41 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void window_error(void)
{
	ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

static t_so_long	*canvas_setup(char**map, t_so_long *game)
{
	int32_t	i;
	int32_t	j;

	game = malloc(sizeof(t_so_long));
	if (!game)
		window_error();
	i = 0;
	while (map[i])
		++i;
	j = 0;
	while (map[0][j])
		++j;
	game->width = j - 1;
	game->height = i;
	game->map = map;
	game->mlx = mlx_init(game->width * 128, game->height * 128, "So Long", true);
	if (!game->mlx)
		window_error();
	ft_printf("x= %i, y= %i\n", game->width, game->height);
	texture_setup(game);
	return (game);
}

void	texture_setup(t_so_long *game)
{
	game->text = ft_calloc(1, sizeof(t_text));
	game->text->bg = mlx_load_png(bg_png);
	game->text->wall = mlx_load_png(wall_png);
	game->text->col = mlx_load_png(collec_png);
	game->text->exit = mlx_load_png(exit_png);
	game->text->player = mlx_load_png(player_png);
	image_setup(game);
}

void	image_setup(t_so_long *game)
{
	game->img = ft_calloc(1, sizeof(t_img));
	game->img->bg = mlx_texture_to_image(game->mlx, game->text->bg);
	game->img->wall = mlx_texture_to_image(game->mlx, game->text->wall);
	game->img->col = mlx_texture_to_image(game->mlx, game->text->col);
	game->img->exit = mlx_texture_to_image(game->mlx, game->text->exit);
	game->img->player = mlx_texture_to_image(game->mlx, game->text->player);
	mlx_delete_texture(game->text->bg);
	mlx_delete_texture(game->text->col);
	mlx_delete_texture(game->text->wall);
	mlx_delete_texture(game->text->exit);
	mlx_delete_texture(game->text->player);
	free(game->text);
}

void	image_clear(t_so_long	*game)
{
	mlx_delete_image(game->mlx, game->img->bg);
	mlx_delete_image(game->mlx, game->img->wall);
	mlx_delete_image(game->mlx, game->img->col);
	mlx_delete_image(game->mlx, game->img->exit);
	mlx_delete_image(game->mlx, game->img->player);
}

int win_setup(char **map, t_so_long *game, t_player *player)
{
	// Start mlx
	game = canvas_setup(map, game);
	// Display the image
	//  if (mlx_image_to_window(mlx, game->background, 0, 0) < 0)
		//window_error();
	int i = 0;
	int j;
	game->player_info = player;
	while(i < game->height)
	{
		j = 0;
		while (j < game->width)
			{
				mlx_image_to_window(game->mlx, game->img->bg, j * 128, i * 128);
				if (map[i][j] == '1')
					mlx_image_to_window(game->mlx, game->img->wall, j * 128, i * 128);
				else if (map[i][j] == 'C')
					mlx_image_to_window(game->mlx, game->img->col, j * 128, i * 128);
				else if (map[i][j] == 'E')
					mlx_image_to_window(game->mlx, game->img->exit, j * 128, i * 128);
				++j;
			}
			++i;
	}
	mlx_image_to_window(game->mlx, game->img->player, game->player_info->player_y * 128, game->player_info->player_x * 128);

	mlx_key_hook(game->mlx, my_key_hook, game);
	mlx_loop(game->mlx);

	// Optional, terminate will clean up any leftover images (not textures!)
	mlx_terminate(game->mlx);
	free(game->img);
	free(game);
	return (EXIT_SUCCESS);
}
