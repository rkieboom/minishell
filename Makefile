# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rkieboom <rkieboom@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/12 19:17:36 by rkieboom      #+#    #+#                  #
#    Updated: 2021/05/17 13:30:37 by rkieboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

FLAGS = -Wall -Werror -Wextra

SRCS =					functions.c \
						main.c \
						$(FUNCTIONS) \
						$(SRCS.COMMANDS.ECHO) \
						$(SRCS.COMMANDS.ENV) \
						$(SRCS.COMMANDS.PWD) \
						$(SRCS.ENV.LIST) \
						$(SRCS.ENV.LIST.FUNC) \
						$(SRCS.EXECUTE) \
						$(SRCS.FREE) \
						$(SRCS.GNL) \
						$(SRCS.PARSING) \
						
FUNCTIONS =				functions/ft_skipspaces.c \
						functions/add_new_line.c \

SRCS.COMMANDS.ECHO =	commands/echo/echo.c \

SRCS.COMMANDS.ENV =		commands/env/env.c \

SRCS.COMMANDS.PWD =		commands/pwd/pwd.c \

SRCS.ENV.LIST =			env_list/env_lst_new.c \
						env_list/env_lstadd_back.c \
						env_list/env_lstlast.c \
						env_list/env_lstsize.c \

SRCS.ENV.LIST.FUNC =	env_list/functions/init.c \
						env_list/functions/search_env.c \

SRCS.EXECUTE =			execute/checkcommand.c \
						execute/execute.c \

SRCS.FREE =				free/free_parse_commands.c \

SRCS.GNL =				get_next_line/get_next_line.c \
						get_next_line/get_next_line_utils.c \

SRCS.PARSING =			parsing/parse.c \
						parsing/parse_split.c \

O.SRCS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(O.SRCS) $(LIBFT)
	@echo "\033[1;30mCompiling files"
	@echo "Making executable"
	@$(CC) -g $(O.SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C Libft/.

%.o: %.c
	@$(CC) -g -Ilibft -c $< -o $@

clean:
	@echo "\033[1;31mCleaning..."
	@rm -rf $(O.SRCS)
	@make -C Libft/. clean

fclean: clean
	@echo "\033[1;31mRemoving minishell"
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	@echo "\033[1;31mRemoving libft.a"

re: fclean all