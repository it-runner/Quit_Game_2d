/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:43:53 by so_long           #+#    #+#             */
/*   Updated: 2025/09/17 11:24:11 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// returns current time in milliseconds since UNIX epoch
static long long	ft_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

// handle key press events and update player movement or exit the game
int	ft_key_press(int keycode, t_game *game)
{
	ft_handle_movement_keys(keycode, game);
	ft_handle_special_keys(keycode, game);
	return (0);
}

// handle key release events and stop player movement
int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == K_W || keycode == K_AR_U)
	{
		game->player.moving_up = 0;
		game->player.up_pressed = 0;
	}
	if (keycode == K_S || keycode == K_AR_D)
	{
		game->player.moving_down = 0;
		game->player.down_pressed = 0;
	}
	if (keycode == K_A || keycode == K_AR_L)
	{
		game->player.moving_left = 0;
		game->player.left_pressed = 0;
	}
	if (keycode == K_D || keycode == K_AR_R)
	{
		game->player.moving_right = 0;
		game->player.right_pressed = 0;
	}
	return (0);
}

// main game loop handler: update time, info panel, process player movement
int	ft_game_loop(t_game *game)
{
	long long	t;

	t = ft_now_ms();
	ft_handle_instant_move(game, t);
	ft_handle_continuous_move(game, t);
	ft_update_info_panel(game, t);
	return (0);
}
