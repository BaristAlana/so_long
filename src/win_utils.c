/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:13:27 by aherbin           #+#    #+#             */
/*   Updated: 2024/08/28 11:49:07 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	text_clear(t_so_long *game)
{
	if (game->text->bg)
		mlx_delete_texture(game->text->bg);
	if (game->text->col)
		mlx_delete_texture(game->text->col);
	if (game->text->wall)
		mlx_delete_texture(game->text->wall);
	if (game->text->exit)
		mlx_delete_texture(game->text->exit);
	if (game->text->player)
		mlx_delete_texture(game->text->player);
	if (game->text)
		free(game->text);
	game->text = NULL;
}

void	image_clear(t_so_long	*game)
{
	if (game->img->bg)
		mlx_delete_image(game->mlx, game->img->bg);
	if (game->img->wall)
		mlx_delete_image(game->mlx, game->img->wall);
	if (game->img->col)
		mlx_delete_image(game->mlx, game->img->col);
	if (game->img->exit)
		mlx_delete_image(game->mlx, game->img->exit);
	if (game->img->player)
		mlx_delete_image(game->mlx, game->img->player);
	if (game->img)
		free(game->img);
	game->img = NULL;
}

static void	check_texture_size(t_so_long *game)
{
	if (game->text->bg->height != game->text->bg->width \
	|| game->text->bg->height != SIZE || game->text->bg->width != SIZE)
		window_exit(game, 2);
	if (game->text->wall->height != game->text->wall->width \
	|| game->text->wall->height != SIZE || game->text->wall->width != SIZE)
		window_exit(game, 2);
	if (game->text->col->height != game->text->col->width \
	|| game->text->col->height != SIZE || game->text->col->width != SIZE)
		window_exit(game, 2);
	if (game->text->exit->height != game->text->exit->width \
	|| game->text->exit->height != SIZE || game->text->exit->width != SIZE)
		window_exit(game, 2);
	if (game->text->player->height != game->text->player->width \
	|| game->text->player->height != SIZE || game->text->player->width != SIZE)
		window_exit(game, 2);
}

void	texture_setup(t_so_long *game)
{
	game->text = ft_calloc(1, sizeof(t_text));
	game->text->bg = mlx_load_png(bg_png);
	if (!game->text->bg)
		window_exit(game, EXIT_FAILURE);
	game->text->wall = mlx_load_png(wall_png);
	if (!game->text->wall)
		window_exit(game, EXIT_FAILURE);
	game->text->col = mlx_load_png(collec_png);
	if (!game->text->col)
		window_exit(game, EXIT_FAILURE);
	game->text->exit = mlx_load_png(exit_png);
	if (!game->text->exit)
		window_exit(game, EXIT_FAILURE);
	game->text->player = mlx_load_png(player_png);
	if (!game->text->player)
		window_exit(game, EXIT_FAILURE);
	check_texture_size(game);
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
	text_clear(game);
}
