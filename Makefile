# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rkieboom <rkieboom@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/12 19:17:36 by rkieboom      #+#    #+#                  #
#    Updated: 2021/05/11 14:34:12 by rkieboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

FLAGS = -Wall -Werror -Wextra

SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\
parsing/parse.c ft_error.c main.c freebuf.c ft_skipspaces.c free/ft_free.c\
execute/execute.c execute/checkcommand.c parsing/parse_split.c print_input.c\
env_list/env_lst_new.c env_list/env_lstadd_back.c env_list/env_lstlast.c env_list/functions/functions.c

O.SRCS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(O.SRCS) $(LIBFT)
	$(CC) $(O.SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C Libft/.

%.o: %.c
	$(CC) -Ilibft -c $< -o $@

clean:
	rm -rf $(O.SRCS)
	make -C Libft/. clean

fclean:
	rm -rf $(NAME)
	rm -rf $(LIBFT)
	rm -rf $(O.SRCS)
	make -C Libft/. clean

re: fclean all