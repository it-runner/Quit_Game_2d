/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 21:55:25 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 21:02:36 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// draw the ASCII-style game title on the panel
void	ft_render_game_info_title(t_game *game, int panel_y)
{
	int	x;

	x = game->show.x_win / 2 - 180;
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		x, panel_y + 20, 0xBBBBBB,
		" ######  #####  ##   ## ######       ## ##   ## ###### ##### ");
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		x, panel_y + 30, 0xBBBBBB,
		"##      ##   ## ### ### ##           ## ###  ## ##    ##   ##");
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		x, panel_y + 40, 0xBBBBBB,
		"##  ### ####### ## # ## #####        ## ## # ## ##### ##   ##");
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		x, panel_y + 50, 0xBBBBBB,
		"##   ## ##   ## ##   ## ##           ## ##  ### ##    ##   ##");
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		x, panel_y + 60, 0xBBBBBB,
		" ###### ##   ## ##   ## ######       ## ##   ## ##     #####");
}

// display the player's name on the game panel
void	ft_display_player_name(t_game *game, int panel_y)
{
	char	*player_name;

	player_name = ft_strjoin("P L A Y E R      ", game->player_data.name);
	if (player_name)
	{
		mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
			30, panel_y + 40, 0x88AADD, player_name);
		free(player_name);
	}
	else
	{
		mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
			30, panel_y + 40, 0xFFFFFF, "PLAYER: ");
		mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
			100, panel_y + 40, 0xFFFFFF, game->player_data.name);
	}
}

// display player's moves and collected items on the panel
void	ft_render_player_stats(t_game *game, int panel_y)
{
	char	*moves;
	char	*items;
	char	*max_items;

	moves = ft_itoa(game->player.move_count);
	items = ft_itoa(game->player.inventory);
	max_items = ft_itoa(game->map.item_count);
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		30, panel_y + 100, 0xFFFF00, "M O V E S");
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		130, panel_y + 100, 0xDDDDDD, moves);
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		30, panel_y + 130, 0x44BBFF, "I T E M S");
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		130, panel_y + 130, 0xDDDDDD, items);
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		150, panel_y + 130, 0xDDDDDD, "/");
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		170, panel_y + 130, 0xDDDDDD, max_items);
	free(moves);
	free(items);
	free(max_items);
}
