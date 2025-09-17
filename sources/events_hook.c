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
	if (keycode == K_W || keycode == K_AR_U)
		game->player.moving_up = 1;
	if (keycode == K_S || keycode == K_AR_D)
		game->player.moving_down = 1;
	if (keycode == K_A || keycode == K_AR_L)
		game->player.moving_left = 1;
	if (keycode == K_D || keycode == K_AR_R)
		game->player.moving_right = 1;
	if (keycode == K_ESC)
		ft_finish_level(game);
	return (0);
}

// handle key release events and stop player movement
int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == K_W || keycode == K_AR_U)
		game->player.moving_up = 0;
	if (keycode == K_S || keycode == K_AR_D)
		game->player.moving_down = 0;
	if (keycode == K_A || keycode == K_AR_L)
		game->player.moving_left = 0;
	if (keycode == K_D || keycode == K_AR_R)
		game->player.moving_right = 0;
	return (0);
}

// main game loop handler: update time, info panel, process player movement
int	ft_game_loop(t_game *game)
{
	long long	t;

	t = ft_now_ms();
	if (game->last_step_ms == 0)
		game->last_step_ms = t;
	if (game->last_update_ms == 0 || t - game->last_update_ms >= 100)
	{
		game->last_update_ms = t;
		game->current_time_ms = t - game->start_time_ms;
		ft_display_info_panel(game);
	}
	if (t - game->last_step_ms < STEP_DELAY)
		return (0);
	game->last_step_ms = t;
	if (game->player.moving_up)
		ft_move_up(game);
	else if (game->player.moving_down)
		ft_move_down(game);
	else if (game->player.moving_left)
		ft_move_left(game);
	else if (game->player.moving_right)
		ft_move_right(game);
	return (0);
}
