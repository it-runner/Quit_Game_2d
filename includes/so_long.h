/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:23:08 by so_long           #+#    #+#             */
/*   Updated: 2025/09/21 12:17:24 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// =========================================================================
// include
// =========================================================================

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/Xutil.h>
# include "linux_keys.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"

// =========================================================================
// define
// =========================================================================

// number of game levels and all available maps
# define TOTAL_LEVELS 8
# define ALL_AVAILABLE_MAPS 8

// move delay in ms
# define STEP_DELAY 140

// full window height (not only map height)
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1024
# endif

// full window width (not only map width)
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1024
# endif

// info panel on the bottom
# ifndef INFO_PANEL_HEIGHT
#  define INFO_PANEL_HEIGHT 256
# endif

// tile (square) size in pixels
# ifndef TILE_SIZE
#  define TILE_SIZE 32
# endif

// popup
# define POPUP_WIDTH 400
# define POPUP_HEIGHT 200
# define BUTTON_WIDTH 120
# define BUTTON_HEIGHT 40

// player data file
# define PLAYER_DATA_FILE "./player_data.txt"

// max nick name length
# define NICK_NAME_LEN 25

// =========================================================================
// structs
// =========================================================================

/* -----------------------------------------------------------
	tile structure for 2D graphics 
		- stores position, image data and rendering info
*/
typedef struct s_tile
{
	int						x_tile;				// Grid X position
	int						y_tile;				// Grid Y position
	char					*img;				// Image data pointer
	char					*addr;				// Pixel memory address
	int						bits_per_pixel;		// Color depth
	int						size_line;			// Bytes per line
	int						endian;				// Byte order
}	t_tile;

/* -----------------------------------------------------------
	Character structure for player/entity
		- stores position, movement and state
*/
typedef struct s_character
{
	int						x_char;				// current X position
	int						y_char;				// current Y position
	int						move_count;			// movement counter/steps
	int						inventory;			// items collected/held
	int						moving_up;			// up movement flag (1/0)
	int						moving_down;		// down movement flag (1/0)
	int						moving_left;		// left movement flag (1/0)
	int						moving_right;		// right movement flag (1/0)
}	t_character;

/* -----------------------------------------------------------
	Map structure for level data
		- stores dimensions, content and object counts
*/
typedef struct s_map
{
	int						x_map;				// map width in tiles/units
	int						y_map;				// map height in tiles/units
	char					**map;				// 2D array for map layout
	int						item_count;			// total collectible items
	int						exit_count;			// number of exit points
	int						hero_count;			// number of player characters
	int						line_size;			// horizontal size/length
	int						col_size;			// vertical size/height
}	t_map;

/* -----------------------------------------------------------
	Line structure for line drawing 
		- stores start + end positions and color of the line
*/
typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
}	t_line;

/* -----------------------------------------------------------
	Queue structure for BFS/character processing 
		- circular buffer implementation
*/
typedef struct s_queue
{
	t_character				*data;				// Array storing character data
	int						front;				// Front index (dequeue pos.)
	int						rear;				// Rear index (enqueue pos.)
	int						capacity;			// Max capacity of the queue
}	t_queue;

/* -----------------------------------------------------------
	Panel structure for UI/graphics 
		- stores image data and dimensions
*/
typedef struct s_panel
{
	void					*img;				// Image identifier/pointer
	char					*addr;				// Pixel data memory address
	int						bits_per_pixel;		// Color depth (bits per pixel)
	int						size_line;			// Bytes per line (stride)
	int						endian;				// Byte order (endianness)
	int						width;				// Panel width in pixels
	int						height;				// Panel height in pixels
}	t_panel;

/* -----------------------------------------------------------
	Display structure for window management
		- stores MLX graphics context
*/
typedef struct s_show
{
	void					*mlx_ptr;			// MLX library instance pointer
	void					*win_ptr;			// Window instance pointer
	void					*img;				// Image buffer pointer
	char					*addr;				// Pixel data memory address
	int						bits_per_pixel;		// Color depth (bits per pixel)
	int						size_line;			// Bytes per line (stride)
	int						endian;				// Byte order (endianness)
	int						x_win;				// Window width
	int						y_win;				// Window height
}	t_show;

/* -----------------------------------------------------------
	Display structure for popup management
		- stores MLX window pointer
		- keeps popup position, size and button states
*/
typedef struct s_popup
{
	void					*win_ptr;			// MLX library instance pointer
	int						x;					// Popup X position
	int						y;					// Popup Y position
	int						width;				// Popup width
	int						height;				// Popup height
	int						continue_clicked;	// Continue button state
	int						quit_clicked;		// Quit button state
}	t_popup;

/* -----------------------------------------------------------
	Player data structure for storing player information
*/
typedef struct s_player_data
{
	char					name[50];			// Player name
	int						score;				// Player score
	long long				game_time_ms;		// Game completion time
	int						moves;				// Number of moves
}	t_player_data;

/* -----------------------------------------------------------
	Main game structure
		- contains all game components and state
*/
typedef struct s_game
{
	struct s_character		player;				// player character data
	struct s_tile			hero;				// hero tile graphics
	struct s_tile			item;				// item tile graphics
	struct s_tile			exit;				// exit tile graphics
	struct s_tile			wall;				// wall tile graphics
	struct s_tile			floor;				// floor tile graphics
	struct s_map			map;				// map data and layout
	struct s_show			show;				// display/window context
	struct s_panel			panel;				// UI panel graphics
	int						current_tile_size;	// current tile size in pixels
	int						map_offset_x;		// map X offset for rendering
	int						map_offset_y;		// map Y offset for rendering
	int						frame_count;		// animation frame counter
	long long				last_step_ms;		// last step timestamp (msec)
	void					*side_img_left;		// image on the left
	void					*side_img_right;	// image on the right
	int						side_img_width;		// width of the side image
	int						side_img_height;	// height of the side image
	int						side_img_spacing;	// spacing between side images
	long long				start_time_ms;		// start time (milliseconds)
	long long				end_time_ms;		// end time (milliseconds)
	long long				current_time_ms;	// current time (milliseconds)
	int						current_level;		// current level of the game
	char					**level_list;		// list of level files
	int						total_levels;		// total number of levels
	struct s_popup			popup;				// popup for level completion
	int						level_completed;	// flag for level completion
	struct s_player_data	player_data;		// player information
	long long				total_time_ms;		// total game time
	long long				acc_time_ms;		// accumulated game time
	long long				last_update_ms;		// last update timestamp
	int						completed;			// flag for game completion
}	t_game;

// =========================================================================
// files and functions
// =========================================================================

// check_map.c
int				ft_check_map(t_game *game);

// elem_ready.c
int				ft_mission_ready(t_game *game);

// error.c
int				ft_error(t_game *game, char *err_msg);
int				ft_nomap_error(t_game *game, char *err_msg);

// events_hook.c
int				ft_game_loop(t_game *game);

// events_hook_utils.c
int				ft_key_press(int keycode, t_game *game);
int				ft_key_release(int keycode, t_game *game);

// flood_fill.c
void			ft_flood_fill(t_game *game, t_map size, t_character charpos,
					char filler);
int				ft_flood_access_check(t_game *game);

// flood_fill_utils.c
void			ft_queue_init(t_queue *q, int capacity);
void			ft_queue_push(t_queue *q, t_character c);
t_character		ft_queue_pop(t_queue *q);
int				ft_is_queue_empty(t_queue *q);
void			ft_clear_and_flood(t_game *game, t_map size,
					t_character charpos);

// ft_xpm.c
t_game			*ft_load_xpm_textures(t_game *game);
int				ft_set_xpm_addr(t_game *game);
int				ft_check_xpm_images(t_game *game);
int				ft_load_side_images(t_game *game);

// game_end.c
void			ft_handle_level_win(t_game *game);

// levels.c
t_game			*ft_init_levels(t_game *game);
int				ft_load_next_level(t_game *game);

// map_init.c
t_game			*ft_init_game_map(char *mappy, t_game *game);
char			**ft_load_map(char *mappy, t_game *game, char **mapping);

// mlx_closing.c
int				ft_finish_level(t_game *game);

// mlx_closing_utils_01.c
long long		ft_get_level_time(t_game *game);
int				ft_should_load_next_level(t_game *game);
int				ft_start_next_level(t_game *game, long long level_time);
void			ft_finalize_level(t_game *game, long long level_time);

// mlx_closing_utils_02.c
void			ft_cleanup_game(t_game *game, int should_load_next);
void			ft_free_map(t_game *game);	
void			ft_free_images(t_game *game);
void			ft_free_mlx_resources(t_game *game);

// move.c
void			ft_move_up(t_game *game);
void			ft_move_down(t_game *game);
void			ft_move_left(t_game *game);
void			ft_move_right(t_game *game);

// move_utils.c
void			ft_move_player(t_game *game, int dy, int dx, char dir);

// panel.c
void			ft_display_info_panel(t_game *game);
char			*ft_make_time_str(int hours, int minutes, int seconds);

// panel_leaderboard.c
void			ft_display_leaderboard(t_game *game, int panel_y);

// panel_leaderboard_utils_01.c
void			ft_render_leaderboard_header(t_game *game, int panel_y);
void			ft_render_leaderboard_entries(t_game *game, int panel_y,
					t_player_data *top_players, int count);

// panel_leaderboard_utils_01.c
t_player_data	*ft_add_player(t_player_data *players,
					t_player_data new_player, int *count);
t_player_data	ft_read_player_line(int fd, int *valid);

// panel_time.c
long long		ft_get_level_time_ms(t_game *game);
void			ft_render_time_panel(t_game *game, int panel_y,
					long long current_time_ms);

// panel_utils_01.c
void			ft_render_game_info_title(t_game *game, int panel_y);
void			ft_display_player_name(t_game *game, int panel_y);
void			ft_render_player_stats(t_game *game, int panel_y);
void			ft_display_level_number(t_game *game, int panel_y);

// panel_utils_02.c
void			ft_display_exit_status(t_game *game, int panel_y);
void			ft_put_pixel_to_image(t_panel *panel, int x, int y, int color);
void			ft_draw_line_on_panel(t_game *game, t_line line);
char			*ft_pad_zero(int n);

// parsing.c
t_game			*ft_valid_map(char *map, t_game *game);

// player.c
void			ft_save_player_data(t_game *game);
int				ft_does_player_exist(const char *name);
void			ft_prompt_player_name(t_game *game);
void			ft_print_name_prompt(void);

// player_defaults.c
void			ft_set_default_player_name(t_game *game);

// player_line_write.c
int				ft_process_lines_and_write(int fd, t_game *game, char **lines,
					int count);

// player_utils_01.c
void			ft_write_player_entry(int fd, t_player_data *player);
int				ft_save_player_data_temp(t_game *game, char **lines, int count);
int				ft_handle_player_input(t_game *game, char *input,
					int bytes_read);

// player_utils_02.c
char			**ft_read_player_data(int *count);
int				ft_is_valid_player_name(const char *name);
int				ft_str_is_alnum(const char *str);

// start_game.c
int				ft_start_game(t_game *game);
int				ft_get_screen_workarea(Display *display, int screen, int *width,
					int *height);

// start_game_utils_01.c
void			ft_set_game_start_time(t_game *game);
int				ft_init_mlx(t_game *game);
int				ft_init_window(t_game *game);
int				ft_get_screen_resolution(int *width, int *height);
void			ft_center_map_on_screen(t_game *game);

// start_game_utils_02.c
void			ft_render_map(t_game *game);
void			ft_reset_player_file(void);
int				ft_set_window_resolution(t_game *game, int *w, int *h);
int				ft_init_game_window(t_game *game, int w, int h);
void			ft_move_window_to_top_left(void *mlx_ptr, void *win_ptr);

// struct_init.c
int				ft_init_game_structs(t_game *game);

// struct_tiles_init.c
int				ft_init_tile_hero(t_game *game);
int				ft_init_tile_item(t_game *game);
int				ft_init_tile_exit(t_game *game);
int				ft_init_tile_floor(t_game *game);
int				ft_init_tile_wall(t_game *game);

// tiles.c
void			ft_draw_tiles(t_game *game, int x_map, int y_map,
					int tile_size);
void			ft_update_display_after_move(t_game *game, int next_y,
					int next_x, int tile_size);
void			ft_load_exit(t_game *game);
void			ft_handle_exit_tile(t_game *game, int tile_code, char mod,
					int tile_size);
void			ft_display_side_images(t_game *game);

// tiles_utils_01.c
void			ft_draw_basic_tiles(t_game *game, int x_map,
					int y_map, int tile_size);
void			ft_draw_special_tiles(t_game *game, int x_map,
					int y_map, int tile_size);
void			ft_draw_player(t_game *game, int next_y, int next_x,
					int tile_size);
void			ft_restore_previous_tile(t_game *game, int tile_size);

// tiles_utils_02.c
int				ft_draw_open_exit_texture(t_game *game);
void			ft_render_exit(t_game *game);
void			ft_draw_exit(t_game *game, char mod, int tile_size);
void			ft_display_left_images(t_game *game, int left_x);
void			ft_display_right_image(t_game *game);

#endif
