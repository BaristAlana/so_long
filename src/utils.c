/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:39:49 by aherbin           #+#    #+#             */
/*   Updated: 2024/09/02 15:16:30 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_file_extension(char *file)
{
	int		len;
	char	*temp;
	char	*subfolder;

	len = ft_strlen(file);
	temp = ft_strrchr(file, '.');
	subfolder = ft_strrchr(file, '/');
	if (!temp)
		ft_exit("Bad extension", EXIT_FAILURE);
	if (len <= 4 || !file[len - 5])
		ft_exit("Bad extension", EXIT_FAILURE);
	if (subfolder)
	{
		++subfolder;
		if (ft_strncmp(subfolder, temp, ft_strlen(subfolder)) == 0)
			ft_exit("Wrong file", EXIT_FAILURE);
	}
	return (ft_strncmp(temp, ".ber", ft_strlen(temp)));
}

void	ft_exit(char *errmsg, int status)
{
	if (!errmsg)
		exit(1);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(errmsg, 2);
	exit(status);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
	{
		return ;
	}
	i = 0;
	while (map[i])
	{
		free(map[i]);
		++i;
	}
	free(map[i]);
	free(map);
}

void	exit_invalid_map(char **map, t_player *player)
{
	free_map(map);
	if (player)
		free(player);
	ft_exit("Map appears to be invalid.", EXIT_FAILURE);
}

int	n_line_gnl(int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\n')
			break ;
		++i;
		free(line);
	}
	free(line);
	close(fd);
	return (i);
}
