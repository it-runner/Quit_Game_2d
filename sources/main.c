/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 07:20:59 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:55:07 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	(void)argc;
	(void)argv;
	game = malloc(sizeof(t_game));
	if (!game)
		ft_nomap_error(game, "    Malloc error.");
	ft_bzero(&game->player_data, sizeof(game->player_data));
	ft_prompt_player_name(game);
	ft_printf("Welcome, %s!\n\n", game->player_data.name);
	if (!ft_init_levels(game))
		return (1);
	if (ft_init_game_structs(game)
		&& ft_valid_map(game->level_list[game->current_level], game))
		ft_start_game(game);
	return (0);
}
