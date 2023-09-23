# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caunhach <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/16 15:52:42 by caunhach          #+#    #+#              #
#    Updated: 2023/07/16 15:52:45 by caunhach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = src/executor/error.c \
       src/executor/exec_cmd.c \
	   src/executor/exec_main.c \
	   src/executor/exec_single_main.c \
	   src/executor/free.c \
	   src/executor/main.c \
	   src/executor/utils.c \
	   src/executor/parse_env.c \
	   src/executor/utils_env.c \
	   src/builtin/builtin.c \
	   src/builtin/ft_cd.c \
	   src/builtin/ft_echo.c \
	   src/builtin/ft_env.c \
	   src/builtin/ft_export.c \
	   src/builtin/ft_pwd.c \
	   src/builtin/builtin_utils.c \
	   src/expander/expander_utils.c \
	   src/lexer/utils_lexer.c

OBJS = $(SRCS:.c=.o)

LIBFT = lib/libft/

LIBFT_PATH = lib/libft/libft.a

CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(OBJS)
	@make -C $(LIBFT) all
	@gcc $(CFLAGS) $(OBJS) $(LIBFT_PATH) -lreadline -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)
	make fclean -C $(LIBFT)
fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re
