# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: so_long <so_long@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 11:59:59 by so_long           #+#    #+#              #
#    Updated: 2025/09/21 11:52:19 by so_long          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	Quit_Game_2d

CC						=	gcc
CFLAGS					=	-Wall -Wextra -Werror -g3 -MMD
MAKEFLAGS 				+= --no-print-directory -s

RM						=	rm -rf

SRC_FILES				=	check_map.c 									\
							elem_ready.c 									\
							error.c											\
							events_hook.c									\
							flood_fill.c									\
							flood_fill_utils.c								\
							ft_xpm.c										\
							game_end.c										\
							levels.c										\
							main.c											\
							map_init.c										\
							mlx_closing.c									\
							mlx_closing_utils_01.c							\
							mlx_closing_utils_02.c							\
							move.c											\
							move_utils.c									\
							panel.c											\
							panel_leaderboard.c								\
							panel_leaderboard_utils_01.c					\
							panel_leaderboard_utils_02.c					\
							panel_time.c									\
							panel_utils_01.c								\
							panel_utils_02.c								\
							parsing.c										\
							player.c 										\
							player_default.c								\
							player_line_write.c								\
							player_utils_01.c								\
							player_utils_02.c								\
							start_game.c									\
							start_game_utils_01.c							\
							start_game_utils_02.c							\
							struct_init.c									\
							struct_tiles_init.c								\
							tiles.c											\
							tiles_utils_01.c								\
							tiles_utils_02.c

SRC_DIR					=	sources
OBJ_DIR					=	obj
OBJ						=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

INCLS					=	-I./includes/ -I./libft/ -I./mlx/

LIBFT_PATH				=	./libft
LIBFT					=	$(LIBFT_PATH)/libft.a
LIBINCL					=	-L$(LIBFT_PATH) -lft

MLX_PATH				=	./mlx
MLX						=	$(MLX_PATH)/libmlx.a
MLXFLAGS				=	-L$(MLX_PATH) -lmlx -lXext -lX11

DEPS					=	$(OBJ:.o=.d)

all:					$(NAME)
						@echo "\033[38;5;171m\n*** Program ready! ***\033[0m\n"

$(NAME):				$(LIBFT) $(OBJ)
						@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBINCL) $(MLXFLAGS)

$(LIBFT):
						@$(MAKE) -C $(LIBFT_PATH) all

$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c | $(OBJ_DIR)
						@$(CC) $(CFLAGS) $(INCLS) -c $< -o $@

$(OBJ_DIR):
						@mkdir -p $(OBJ_DIR)

-include $(DEPS)

clean:
						@$(MAKE) -C $(LIBFT_PATH) clean
						@$(RM) $(OBJ_DIR)
						@echo "\033[33mCleaned\033[0m"

fclean:					clean
						@$(MAKE) -C $(LIBFT_PATH) fclean
						@$(RM) $(NAME)
						@echo "\033[33mFully Cleaned\033[0m"

re:						fclean all

debug:					CXXFLAGS += -g -fsanitize=address
debug: 					re
						@echo "(debug mode)\n"

.PHONY:	all clean fclean re debug
