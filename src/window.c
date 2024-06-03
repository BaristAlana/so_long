/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:23:24 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/03 16:19:17 by aherbin          ###   ########.fr       */
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
	ft_printf("x= %i, y= %i\n", game->width, game->height);
	return (game);
}

int win_setup(char **map, t_so_long *game)
{
  // Start mlx
  game = canvas_setup(map, game);
  mlx_t* mlx = mlx_init(game->width * 128, game->height * 128, "So Long", false);
  if (!mlx)
        window_error();

  // Try to load the file background
  mlx_texture_t* texture = mlx_load_png(bg_img);
  if (!texture)
        window_error();
  // Convert texture to a displayable image
  game->background = mlx_texture_to_image(mlx, texture);
  if (!game->background)
        window_error();
  mlx_delete_texture(texture);

  // Try to load the file wall
  texture = mlx_load_png(wall_img);
  if (!texture)
        window_error();
  // Convert texture to a displayable image
  game->wall = mlx_texture_to_image(mlx, texture);
  if (!game->wall)
        window_error();
  mlx_delete_texture(texture);

  // Try to load the file player
  texture = mlx_load_png(player_img);
  if (!texture)
        window_error();
  // Convert texture to a displayable image
  game->player = mlx_texture_to_image(mlx, texture);
  if (!game->player)
        window_error();
  mlx_delete_texture(texture);

  // Try to load the file collectible
  texture = mlx_load_png(collec_img);
  if (!texture)
        window_error();
  // Convert texture to a displayable image
  game->collectible = mlx_texture_to_image(mlx, texture);
  if (!game->collectible)
        window_error();
  mlx_delete_texture(texture);

  // Try to load the file exit
  texture = mlx_load_png(exit_img);
  if (!texture)
        window_error();
  // Convert texture to a displayable image
  game->exit = mlx_texture_to_image(mlx, texture);
  if (!game->exit)
        window_error();
  mlx_delete_texture(texture);

  // Display the image
//  if (mlx_image_to_window(mlx, game->background, 0, 0) < 0)
        //window_error();
	int i = 0;
	int j;
	while(i < game->height)
	{
		j = 0;
		while (j < game->width)
			{
				mlx_image_to_window(mlx, game->background, j * 128, i * 128);
				if (map[i][j] == '1')
					mlx_image_to_window(mlx, game->wall, j * 128, i * 128);
				else if (map[i][j] == 'P')
					mlx_image_to_window(mlx, game->player, j * 128, i * 128);
				else if (map[i][j] == 'C')
					mlx_image_to_window(mlx, game->collectible, j * 128, i * 128);
				else if (map[i][j] == 'E')
					mlx_image_to_window(mlx, game->exit, j * 128, i * 128);
				++j;
			}
			++i;
	}

  mlx_loop(mlx);

  mlx_delete_image(mlx, game->background);
  mlx_delete_image(mlx, game->wall);
  mlx_delete_image(mlx, game->player);
  mlx_delete_image(mlx, game->collectible);
  mlx_delete_image(mlx, game->exit);

  // Optional, terminate will clean up any leftover images (not textures!)
  mlx_terminate(mlx);
  free(game);
  return (EXIT_SUCCESS);
}
