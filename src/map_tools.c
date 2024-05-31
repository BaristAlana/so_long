/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:49:41 by aherbin           #+#    #+#             */
/*   Updated: 2024/05/31 11:02:15 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	count_component(char **map, char component)
{
	int	i;
	int	j;
	int	c;

	c = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == component)
				++c;
			++j;
		}
		++i;
	}
	return (c);
}

static void	is_map_bordered(char **map, int len)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][len - 2] != '1')
			exit_invalid_map(map);
		++i;
	}
	j = 0;
	while (j < len - 1)
	{
		if (map[i - 1][j] != '1' || map[0][j] != '1')
			exit_invalid_map(map);
		++j;
	}
	if (count_component(map, 'E') != 1 \
	|| count_component(map, 'P') != 1 || count_component(map, 'C') < 1)
		exit_invalid_map(map);
}

char	**read_map(char *file)
{
	char	**map;
	int		fd;
	int		i;
	int		n_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_exit("Could not open map file. \
Check for typos or permissions!", EXIT_FAILURE);
	n_line = n_line_gnl(fd);
	map = malloc(sizeof(char *) * (n_line + 1));
	if (!map)
		ft_exit("Could not allocate memory!", EXIT_FAILURE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_exit("Could not open map file. \
Check for typos or permissions!", EXIT_FAILURE);
	i = 0;
	while (i < n_line)
	{
		map[i] = get_next_line(fd);
		++i;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	check_map(char **map)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = ft_strlen(map[i]);
	while (map[i])
	{
		j = 0;
		if ((int)ft_strlen(map[i]) != len)
			exit_invalid_map(map);
		while (map[i][j])
		{
			if (ft_strchr("01CEP\n", map[i][j]) == NULL)
				exit_invalid_map(map);
			++j;
		}
		++i;
	}
	is_map_bordered(map, len);
}
