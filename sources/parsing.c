/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:36:47 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:29:40 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// check map filename extension
static int	check_ext(char *map)
{
	char	*name_ext;
	char	*correct_ext;

	correct_ext = ".ber";
	name_ext = ft_substr(map, (ft_strlen(map) - 4), 4);
	if (ft_strncmp(name_ext, correct_ext, 4) != 0)
	{
		free(name_ext);
		return (0);
	}
	free(name_ext);
	return (1);
}

// map full checking (extension, shapes, etc.)
t_game	*ft_valid_map(char *map_path, t_game *game)
{
	if (!check_ext(map_path))
	{
		ft_nomap_error(game, "    Invalid map file extension");
		return (0);
	}
	if (!ft_init_game_map(map_path, game))
	{
		ft_nomap_error(game, "    Invalid map.");
		return (0);
	}
	if (!ft_check_map(game))
		return (0);
	if (!ft_flood_access_check(game))
		return (0);
	if (game->map.map)
		ft_free_map(game);
	ft_init_game_map(map_path, game);
	return (game);
}
