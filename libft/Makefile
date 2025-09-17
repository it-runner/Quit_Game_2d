# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: so_long <so_long@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 14:24:29 by so_long           #+#    #+#              #
#    Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC				=	inc/
SRC_DIR			=	src/
OBJ_DIR			=	obj/

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -I
RM				=	rm -f
AR				=	ar rcs

LIBFT_DIR		=	$(SRC_DIR)libft/ft_isalpha.c \
					$(SRC_DIR)libft/ft_isdigit.c \
					$(SRC_DIR)libft/ft_isascii.c \
					$(SRC_DIR)libft/ft_isprint.c \
					$(SRC_DIR)libft/ft_strlen.c \
					$(SRC_DIR)libft/ft_memset.c \
					$(SRC_DIR)libft/ft_bzero.c \
					$(SRC_DIR)libft/ft_memcpy.c \
					$(SRC_DIR)libft/ft_memmove.c \
					$(SRC_DIR)libft/ft_strlcpy.c \
					$(SRC_DIR)libft/ft_strlcat.c \
					$(SRC_DIR)libft/ft_toupper.c \
					$(SRC_DIR)libft/ft_tolower.c \
					$(SRC_DIR)libft/ft_strchr.c \
					$(SRC_DIR)libft/ft_strrchr.c \
					$(SRC_DIR)libft/ft_strncmp.c \
					$(SRC_DIR)libft/ft_memchr.c \
					$(SRC_DIR)libft/ft_memcmp.c \
					$(SRC_DIR)libft/ft_strnstr.c \
					$(SRC_DIR)libft/ft_atoi.c \
					$(SRC_DIR)libft/ft_calloc.c \
					$(SRC_DIR)libft/ft_strdup.c \
					$(SRC_DIR)libft/ft_substr.c \
					$(SRC_DIR)libft/ft_strjoin.c \
					$(SRC_DIR)libft/ft_strtrim.c \
					$(SRC_DIR)libft/ft_split.c \
					$(SRC_DIR)libft/ft_itoa.c \
					$(SRC_DIR)libft/ft_strmapi.c \
					$(SRC_DIR)libft/ft_striteri.c \
					$(SRC_DIR)libft/ft_putchar_fd.c \
					$(SRC_DIR)libft/ft_putstr_fd.c \
					$(SRC_DIR)libft/ft_putendl_fd.c \
					$(SRC_DIR)libft/ft_putnbr_fd.c \
					$(SRC_DIR)libft/ft_isspace.c

PRINTF_DIR		=	${SRC_DIR}ft_printf/ft_printf.c \
					${SRC_DIR}ft_printf/print_char.c \
					${SRC_DIR}ft_printf/print_digit.c \
					${SRC_DIR}ft_printf/print_hex.c \
					${SRC_DIR}ft_printf/print_ptr.c \
					${SRC_DIR}ft_printf/print_str.c \
					${SRC_DIR}ft_printf/print_unsigned.c

GNL_DIR			=	${SRC_DIR}get_next_line/get_next_line.c \
					${SRC_DIR}get_next_line/get_next_line_utils.c 

SRC				=	${LIBFT_DIR} ${PRINTF_DIR} ${GNL_DIR}

OBJ 			=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

all: 				${NAME}

$(NAME): 			$(OBJ)
					@$(AR) $(NAME) $(OBJ)
					# @echo "${NAME}: 	library created successfully"

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
					@$(RM) -r $(OBJ_DIR)
					@$(RM) .cache_exists
					# @echo "${NAME}: 	all objects cleaned successfully"

fclean: 			clean
					@$(RM) $(NAME)
					# @echo "${NAME}: 	all objects and library cleaned successfully"

re: 				fclean all

.PHONY: 			all clean fclean re
