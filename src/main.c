/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbin <aherbin@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:16:25 by aherbin           #+#    #+#             */
/*   Updated: 2024/05/30 17:02:07 by aherbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		++i;
	}
	free(map);
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

void	exit_invalid_map(char **map)
{
	free_map(map);
	ft_exit("Map appears to be invalid.", EXIT_FAILURE);
}

void	check_collectibles(char **map, int exit, int player)
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
			if (map[i][j] == 'C')
				++c;
			++j;
		}
		++i;
	}
	if (exit != 1 || player != 1 || c < 1)
		exit_invalid_map(map);
}

void	check_player_exit(char **map)
{
	int	i;
	int	j;
	int	e;
	int	p;

	e = 0;
	p = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				++e;
			else if (map[i][j] == 'P')
				++p;
			++j;
		}
		++i;
	}
	check_collectibles(map, e, p);
}

void	is_map_bordered(char **map, int len)
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
	check_player_exit(map);
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

int	main(int argc, char **argv)
{
	char	**map;

	if (argc != 2 || (argc == 2 && !argv[1]) || check_file_extension(argv[1]))
		ft_exit("Please put a valid map file!", EXIT_FAILURE);
	map = read_map(argv[1]);
	check_map(map);

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
	free_map(map);
}
