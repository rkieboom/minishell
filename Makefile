# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rkieboom <rkieboom@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/12 19:17:36 by rkieboom      #+#    #+#                  #
#    Updated: 2021/11/27 18:34:41 by rkieboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

FLAGS = -fsanitize=address

SRCS =					functions.c \
						main.c \
						$(FUNCTIONS) \
						$(SRCS.COMMANDS.CD) \
						$(SRCS.COMMANDS.ECHO) \
						$(SRCS.COMMANDS.ENV) \
						$(SRCS.COMMANDS.PWD) \
						$(SRCS.COMMANDS.EXPORT) \
						$(SRCS.COMMANDS.UNSET) \
						$(SRCS.COMMANDS.EXECVE) \
						$(SRCS.COMMANDS.EXIT) \
						$(SRCS.ENV.LIST) \
						$(SRCS.ENV.LIST.FUNC) \
						$(SRCS.EXECUTE) \
						$(SRCS.FREE) \
						$(SRCS.GNL) \
						$(SRCS.NEW.PARSING) \
						
						
FUNCTIONS =				functions/ft_skipspaces.c \
						functions/add_new_line.c \
						functions/ft_swap.c \

SRCS.COMMANDS.CD =		commands/cd/cd.c \

SRCS.COMMANDS.ECHO =	commands/echo/echo.c \

SRCS.COMMANDS.ENV =		commands/env/env.c \

SRCS.COMMANDS.PWD =		commands/pwd/pwd.c \

SRCS.COMMANDS.EXPORT =	commands/export/export.c \
						commands/export/export_utils.c \

SRCS.COMMANDS.UNSET =	commands/unset/unset.c \

SRCS.COMMANDS.EXECVE =	commands/execve/execve.c \
						commands/execve/commands.c \
						commands/execve/relative_path.c \
						commands/execve/absolute_path.c \

SRCS.COMMANDS.EXIT = 	commands/exit/exit.c \

SRCS.ENV.LIST =			env_list/env_lst_new.c \
						env_list/env_lstadd_back.c \
						env_list/env_lstlast.c \
						env_list/env_lstsize.c \

SRCS.ENV.LIST.FUNC =	env_list/functions/init.c \
						env_list/functions/search_env.c \

SRCS.EXECUTE =			execute/checkcommand.c \
						execute/execute.c \
						execute/redirections.c \

SRCS.FREE =				free/free_parse_commands.c \

SRCS.PARSING =			parsing/parse.c \
						parsing/parse_split.c \
						parsing/split_spaces.c \
						parsing/functions/double_quote.c \
						parsing/functions/single_quote.c \
						parsing/functions/dollar.c \
						parsing/tokens.c \
						parsing/tokens_utils.c \

SRCS.NEW.PARSING = 		newparsing/parse.c \
						newparsing/parse_split_spaces.c \
						newparsing/parse_split_commands.c \

O.SRCS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(O.SRCS) $(LIBFT)
	@echo "Compiling files"
	@echo "Making executable"
	@$(CC) -ggdb3 -lreadline $(FLAGS) $(O.SRCS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C libft/.

%.o: %.c
	@$(CC) -ggdb3 $(FLAGS) -Ilibft -c $< -o $@

clean:
	@echo "Cleaning..."
	@rm -rf $(O.SRCS)
	@make -C libft/. clean

fclean: clean
	@echo "Removing minishell"
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)
	@echo "Removing libft.a"

re: fclean all
