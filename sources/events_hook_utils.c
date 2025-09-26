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

// handle instant movement based on key presses
void	ft_handle_instant_move(t_game *game, long long t)
{
	if (game->player.up_pressed)
	{
		ft_move_up(game);
		game->player.up_pressed = 0;
		game->last_step_ms = t;
	}
	else if (game->player.down_pressed)
	{
		ft_move_down(game);
		game->player.down_pressed = 0;
		game->last_step_ms = t;
	}
	else if (game->player.left_pressed)
	{
		ft_move_left(game);
		game->player.left_pressed = 0;
		game->last_step_ms = t;
	}
	else if (game->player.right_pressed)
	{
		ft_move_right(game);
		game->player.right_pressed = 0;
		game->last_step_ms = t;
	}
}

// continuous movement handler
void	ft_handle_continuous_move(t_game *game, long long t)
{
	if (t - game->last_step_ms >= STEP_DELAY)
	{
		if (game->player.moving_up)
			ft_move_up(game);
		else if (game->player.moving_down)
			ft_move_down(game);
		else if (game->player.moving_left)
			ft_move_left(game);
		else if (game->player.moving_right)
			ft_move_right(game);
		game->last_step_ms = t;
	}
}

// update info panel every 100ms
void	ft_update_info_panel(t_game *game, long long t)
{
	if (game->last_update_ms == 0 || t - game->last_update_ms >= 100)
	{
		game->last_update_ms = t;
		game->current_time_ms = t - game->start_time_ms;
		ft_display_info_panel(game);
	}
}

// handle movement keys
void	ft_handle_movement_keys(int keycode, t_game *game)
{
	if (keycode == K_W || keycode == K_AR_U)
	{
		if (!game->player.moving_up)
			game->player.up_pressed = 1;
		game->player.moving_up = 1;
	}
	else if (keycode == K_S || keycode == K_AR_D)
	{
		if (!game->player.moving_down)
			game->player.down_pressed = 1;
		game->player.moving_down = 1;
	}
	else if (keycode == K_A || keycode == K_AR_L)
	{
		if (!game->player.moving_left)
			game->player.left_pressed = 1;
		game->player.moving_left = 1;
	}
	else if (keycode == K_D || keycode == K_AR_R)
	{
		if (!game->player.moving_right)
			game->player.right_pressed = 1;
		game->player.moving_right = 1;
	}
}

// handle special keys
void	ft_handle_special_keys(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		ft_finish_level(game);
}
