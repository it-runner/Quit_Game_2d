/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:01:38 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 22:07:37 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// set map size (lines and columns)
static void	ft_set_map_size(t_game *game, int i, int j)
{
	game->map.line_size = i - 1;
	game->map.col_size = j - 1;
}

// read the map file and set its dimensions in the game struct
static void	ft_set_map_dimensions(char *map_path, t_game *game)
{
	char	*map_line;
	int		i;
	int		fd;
	int		j;

	i = 0;
	j = 0;
	map_line = "";
	fd = open(map_path, O_RDONLY);
	if (fd <= 0)
		return ;
	else
	{
		while (map_path != NULL && map_line != NULL)
		{
			map_line = get_next_line(fd);
			if (!i)
				i = ft_strlen(map_line);
			free(map_line);
			j++;
		}
	}
	ft_set_map_size(game, i, j);
	close(fd);
}

// read the map file into a 2D char array
char	**ft_load_map(char *map_path, t_game *game, char **map_lines)
{
	int		fd;
	char	*liner;
	int		i;

	fd = open(map_path, O_RDONLY);
	if (fd <= 0)
		return (NULL);
	i = 0;
	while (i < game->map.col_size)
	{
		liner = get_next_line(fd);
		if (liner)
		{
			map_lines[i] = ft_strdup(liner);
			free(liner);
		}
		else
			map_lines[i] = NULL;
		i++;
	}
	close(fd);
	return (map_lines);
}

// initialize game map from file
t_game	*ft_init_game_map(char *map_path, t_game *game)
{
	ft_set_map_dimensions(map_path, game);
	if (game->map.line_size < 3 || game->map.col_size < 3)
		return (NULL);
	game->map.map = malloc(sizeof(char *) * game->map.col_size);
	if (!game->map.map)
		return (NULL);
	game->map.map = ft_load_map(map_path, game, game->map.map);
	return (game);
}
