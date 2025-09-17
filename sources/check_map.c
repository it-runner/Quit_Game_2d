/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 07:18:17 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 21:01:22 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// check single char on map (0 1 P E C)
static int	ft_check_char(char board_item, t_game *game)
{
	char	*char_ok;

	char_ok = "01EPC";
	if (board_item == 'P')
		game->map.hero_count++;
	if (board_item == 'E')
		game->map.exit_count++;
	if (board_item == 'C')
		game->map.item_count++;
	if (!ft_strchr(char_ok, board_item))
	{
		ft_error(game, "Map contains invalid character(s)!\n\
		Valid characters : 0 1 P E C\n");
		return (0);
	}
	if (game->map.hero_count > 1)
	{
		ft_error(game, "There can be no more than one player!");
		return (0);
	}
	if (game->map.exit_count > 1)
	{
		ft_error(game, "Map can contain only one exit");
		return (0);
	}
	return (1);
}

// check all chars on map (0 1 P E C)
static int	ft_valid_char(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.col_size - 1)
	{
		j = 0;
		while (game->map.map[i][j] != '\n')
		{
			if (!ft_check_char(game->map.map[i][j], game))
				return (0);
			j++;
		}
		i++;
	}
	if (!ft_mission_ready(game))
		return (0);
	return (1);
}

// check whether the map is closed (has 1 on the border)
static int	ft_closed_up(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.line_size)
	{
		if (game->map.map[0][i] != '1'
			|| game->map.map[game->map.col_size - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map.col_size)
	{
		if (game->map.map[i][0] != '1'
			|| game->map.map[i][game->map.line_size - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

// check map shape
static int	ft_map_shape_check(t_game *game)
{
	int	i;
	int	expected_len;
	int	actual_len;

	i = 0;
	expected_len = game->map.line_size;
	while (i < game->map.col_size)
	{
		actual_len = ft_strlen(game->map.map[i]);
		if (game->map.map[i][actual_len - 1] == '\n')
			actual_len--;
		if (actual_len != expected_len)
		{
			ft_printf("Line %d: expected %d, got %d\n", i,
				expected_len, actual_len);
			return (0);
		}
		i++;
	}
	return (1);
}

// check the map (whether it is rectangular, closed and has valid chars)
int	ft_check_map(t_game *game)
{
	if (!ft_map_shape_check(game))
	{
		ft_error(game, "The map has to be rectangular");
		return (0);
	}
	if (!ft_closed_up(game))
	{
		ft_error(game, "Map is not closed properly or \
			has invalid characters on the border");
		return (0);
	}
	if (!ft_valid_char(game))
		return (0);
	return (1);
}
