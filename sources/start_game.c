/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 07:46:28 by so_long           #+#    #+#             */
/*   Updated: 2025/09/17 11:21:38 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// render initial map, display info panel, and set graphics hooks
static void	ft_init_game_display(t_game *game)
{
	ft_render_map(game);
	ft_display_info_panel(game);
	mlx_do_sync(game->show.mlx_ptr);
	mlx_hook(game->show.win_ptr, KeyPress, KeyPressMask, ft_key_press, game);
	mlx_hook(game->show.win_ptr, KeyRelease, KeyReleaseMask,
		ft_key_release, game);
	mlx_loop_hook(game->show.mlx_ptr, ft_game_loop, game);
	mlx_hook(game->show.win_ptr, DestroyNotify,
		StructureNotifyMask, ft_finish_level, game);
	mlx_hook(game->show.win_ptr, ClientMessage,
		LeaveWindowMask, ft_finish_level, game);
	mlx_loop(game->show.mlx_ptr);
}

// retrieve the _NET_WORKAREA property from the root window (X11)
static long	*ft_get_x11_workarea(Display *display, int screen,
								unsigned long *nitems)
{
	Window			root;
	Atom			workarea_atom;
	Atom			cardinal_atom;
	unsigned char	*data;

	root = RootWindow(display, screen);
	workarea_atom = XInternAtom(display, "_NET_WORKAREA", False);
	cardinal_atom = XInternAtom(display, "CARDINAL", False);
	data = NULL;
	if (XGetWindowProperty(display, root, workarea_atom,
			0, 4, False, cardinal_atom,
			&workarea_atom, (int []){0}, nitems,
		(unsigned long []){0}, &data) == Success)
		return ((long *)data);
	return (NULL);
}

// retrieve the usable screen area for the specified display and screen.
int	ft_get_screen_workarea(Display *display, int screen, int *width,
	int *height)
{
	long			*workarea;
	unsigned long	nitems;

	workarea = ft_get_x11_workarea(display, screen, &nitems);
	if (workarea && nitems >= 4)
	{
		*width = workarea[2];
		*height = workarea[3];
		XFree(workarea);
		return (1);
	}
	if (workarea)
		XFree(workarea);
	return (0);
}

// initialize game graphics and load all necessary textures/images
static int	ft_load_game_graphics(t_game *game)
{
	if (ft_load_xpm_textures(game))
	{
		if (!ft_load_side_images(game))
		{
			ft_error(game, "Could not load side images");
			return (0);
		}
		ft_init_game_display(game);
	}
	return (1);
}

// initialize and start the gam
int	ft_start_game(t_game *game)
{
	ft_printf("\n   --- START ---\n\n");
	ft_set_game_start_time(game);
	if (!ft_init_mlx(game))
		return (0);
	if (!ft_init_window(game))
		return (0);
	ft_center_map_on_screen(game);
	if (!ft_load_game_graphics(game))
		return (0);
	return (1);
}
