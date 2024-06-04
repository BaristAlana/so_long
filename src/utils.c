/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:39:49 by aherbin           #+#    #+#             */
/*   Updated: 2024/06/04 15:00:20 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_file_extension(char *file)
{
	int		len;
	char	*temp;

	temp = ft_strrchr(file, '.');
	if (!temp)
		return (1);
	len = ft_strlen(temp);
	if (len != 4)
		return (1);
	return (ft_strncmp(temp, ".ber", len));
}

int	ft_exit(char *errmsg, int status)
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
		return ;
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		++i;
	}
	free(map);
}

void	exit_invalid_map(char **map)
{
	free_map(map);
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
