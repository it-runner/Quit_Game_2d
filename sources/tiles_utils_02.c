/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 13:16:30 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 22:49:06 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// load the open exit image into the game
int	ft_draw_open_exit_texture(t_game *game)
{
	if (game->exit.img)
		mlx_destroy_image(game->show.mlx_ptr, game->exit.img);
	game->exit.img = mlx_xpm_file_to_image(game->show.mlx_ptr,
			"graphics/E_exit_open.xpm",
			&game->exit.bits_per_pixel,
			&game->exit.size_line);
	if (!game->exit.img)
	{
		ft_printf("Error: Could not load open exit texture\n");
		return (0);
	}
	game->exit.addr = mlx_get_data_addr(game->exit.img,
			&game->exit.bits_per_pixel,
			&game->exit.size_line,
			&game->exit.endian);
	return (1);
}

// draw the exit tile and print a message that the door is open
void	ft_render_exit(t_game *game)
{
	int	offset_x;
	int	offset_y;
	int	tile_size;

	offset_x = game->map_offset_x;
	offset_y = game->map_offset_y;
	tile_size = TILE_SIZE;
	mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
		game->floor.img, offset_x + game->exit.x_tile * tile_size,
		offset_y + game->exit.y_tile * tile_size);
	mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
		game->exit.img, offset_x + game->exit.x_tile * tile_size,
		offset_y + game->exit.y_tile * tile_size);
	ft_printf("\nThe door has been opened\n\n");
}

void	ft_draw_exit(t_game *game, char mod, int tile_size)
{
	int	offset_x;
	int	offset_y;

	offset_x = game->map_offset_x;
	offset_y = game->map_offset_y;
	if (mod == 'u')
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->exit.img, offset_x + game->player.x_char * tile_size,
			offset_y + (game->player.y_char - 1) * tile_size);
	if (mod == 'd')
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->exit.img, offset_x + game->player.x_char * tile_size,
			offset_y + (game->player.y_char + 1) * tile_size);
	if (mod == 'l')
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->exit.img, offset_x + (game->player.x_char - 1) * tile_size,
			offset_y + game->player.y_char * tile_size);
	if (mod == 'r')
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->exit.img, offset_x + (game->player.x_char + 1) * tile_size,
			offset_y + game->player.y_char * tile_size);
}

// draw left-side images with dynamic spacing based on map size
void	ft_display_left_images(t_game *game, int left_x)
{
	int	i;
	int	spacing;
	int	start_y;
	int	image_count;

	if (game->map.col_size < 14)
		image_count = 2;
	else
		image_count = 3;
	spacing = 155;
	start_y = game->map_offset_y
		+ (int)(((float)(game->map.col_size * TILE_SIZE)
				- (game->side_img_height * image_count + spacing
					* (image_count - 1))) / 3.8f);
	i = 0;
	while (i < image_count)
	{
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->side_img_left, left_x,
			start_y + i * (game->side_img_height + spacing));
		i++;
	}
}

// draw the right-side image next to the map, vertically centered
void	ft_display_right_image(t_game *game)
{
	int	map_width;
	int	right_x;
	int	right_y;
	int	spacing;

	map_width = game->map.line_size * TILE_SIZE;
	spacing = 155;
	right_x = game->map_offset_x + map_width + spacing;
	right_y = game->map_offset_y + (game->map.col_size * TILE_SIZE
			- game->side_img_height) / 2;
	mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
		game->side_img_right, right_x, right_y);
}
