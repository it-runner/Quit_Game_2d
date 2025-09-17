/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 10:47:20 by so_long           #+#    #+#             */
/*   Updated: 2025/09/17 10:47:27 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// assign a unique default name to the player (e.g., Player1, Player2, etc.)
void	ft_set_default_player_name(t_game *game)
{
	static int	player_num = 1;
	char		*num_str;
	char		default_name[30];

	while (1)
	{
		num_str = ft_itoa(player_num);
		if (!num_str)
		{
			ft_strlcpy(game->player_data.name, "Player",
				sizeof(game->player_data.name));
			break ;
		}
		ft_strlcpy(default_name, "Player", sizeof(default_name));
		ft_strlcat(default_name, num_str, sizeof(default_name));
		free(num_str);
		if (!ft_does_player_exist(default_name))
		{
			ft_strlcpy(game->player_data.name, default_name,
				sizeof(game->player_data.name));
			ft_printf("Using default name: %s\n", default_name);
			break ;
		}
		player_num++;
	}
}
