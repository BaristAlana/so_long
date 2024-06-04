/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:13:27 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/04 15:15:35 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	text_clear(t_so_long *game)
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
	free(game->text);
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
}

void	texture_setup(t_so_long *game)
{
	game->text = ft_calloc(1, sizeof(t_text));
	game->text->bg = mlx_load_png(bg_png);
	if (!game->text->bg)
		window_error(game);
	game->text->wall = mlx_load_png(wall_png);
	if (!game->text->wall)
		window_error(game);
	game->text->col = mlx_load_png(collec_png);
	if (!game->text->col)
		window_error(game);
	game->text->exit = mlx_load_png(exit_png);
	if (!game->text->exit)
		window_error(game);
	game->text->player = mlx_load_png(player_png);
	if (!game->text->player)
		window_error(game);
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

void	window_error(t_so_long *game)
{
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	if (game->text)
		text_clear(game);
	if (game->img)
		image_clear(game);
	if (game->player_info)
		free(game->player_info);
	if (game->map)
		free_map(game->map);
	free(game);
	ft_exit((char *)mlx_strerror(mlx_errno), mlx_errno);
}
