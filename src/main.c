/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:16:25 by aherbin           #+#    #+#             */
/*   Updated: 2024/05/30 11:20:23 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int main(void)
{
    mlx_t	*mlx_ptr;

    mlx_ptr = mlx_init(25, 25, "test", 0);
    mlx_terminate(mlx_ptr);
    //free(mlx_ptr);
	ft_putendl_fd("Ceci est un test", 1);
	exit(0);
}

