/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 21:59:48 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 16:12:53 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// display exit status (open or locked) based on collected items
void	ft_display_exit_status(t_game *game, int panel_y)
{
	if (game->player.inventory == game->map.item_count)
		mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
			30, panel_y + 170, 0x00FF00, "E  X  I  T       O _ P _ E _ N");
	else
		mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
			130, panel_y + 170,
			0xFF0000, "E  X  I  T       L _ O _ C _ K _ E _ D");
}

// sets a pixel at (x, y) in the panel to the specified color
void	ft_put_pixel_to_image(t_panel *panel, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < panel->width && y >= 0 && y < panel->height)
	{
		dst = panel->addr + (y * panel->size_line + x
				* (panel->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

// calculate absolute differences and step directions for a line
static void	ft_init_line_steps(t_line line, int steps[4])
{
	steps[0] = abs(line.x1 - line.x0);
	steps[1] = abs(line.y1 - line.y0);
	if (line.x0 < line.x1)
		steps[2] = 1;
	else
		steps[2] = -1;
	if (line.y0 < line.y1)
		steps[3] = 1;
	else
		steps[3] = -1;
}

// draw a line on the panel using Bresenham's algorithm
void	ft_draw_line_on_panel(t_game *game, t_line line)
{
	int	steps[4];
	int	error;
	int	error_double;

	ft_init_line_steps(line, steps);
	error = steps[0] - steps[1];
	while (1)
	{
		ft_put_pixel_to_image(&game->panel, line.x0, line.y0, line.color);
		if (line.x0 == line.x1 && line.y0 == line.y1)
			break ;
		error_double = 2 * error;
		if (error_double > -steps[1])
		{
			error -= steps[1];
			line.x0 += steps[2];
		}
		if (error_double < steps[0])
		{
			error += steps[0];
			line.y0 += steps[3];
		}
	}
}

// convert integer to a string, padding with a leading zero if < 10
char	*ft_pad_zero(int n)
{
	char	*num;
	char	*result;

	num = ft_itoa(n);
	if (!num)
		return (NULL);
	if (n < 10)
	{
		result = ft_strjoin("0", num);
		free(num);
		return (result);
	}
	return (num);
}
