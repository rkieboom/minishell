# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rkieboom <rkieboom@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/03 16:05:06 by rkieboom      #+#    #+#                  #
#    Updated: 2022/10/17 18:04:08 by rkieboom      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# The name of your executable
NAME		= minishell

# Compiler and compiling flags
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra

# Debug, use with`make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS	+= -g3
endif
ifeq ($(DEBUG),2)
CFLAGS	+= -g3 -fsanitize=address -fno-omit-frame-pointer
endif
ifeq ($(DEBUG),3)
CFLAGS	+= -g3 -fsanitize=leak
endif

# Folder name
SRCDIR	= ./
OBJDIR	= bin/
LIBFTDIR = libft/

INCLUDES = header.h newparsing/parse.h execute/execute.h \
libft/libft.h env_list/env_list.h commands/commands.h cmd/cmd.h cmd/tokens_cmd/tokens.h

LIBFTLIB = $(LIBFTDIR)/libft.a

INCLUDES_MAC = -I/opt/homebrew/Cellar/readline/8.1.2/include

INCLUDES_L = -L./libft/.

SRCS =					main.c \
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
						$(SRCS.FREE) \
						$(SRCS.GNL) \
						$(SRCS.NEW.PARSING) \
						$(SRCS.CREATE.CMD) \
						$(SRCS.EXECUTE)
						
						
FUNCTIONS =				functions/ft_skipspaces.c \
						functions/add_new_line.c \
						functions/ft_swap.c \
						functions/check_input.c \
						functions/read_input.c \
						functions/syntax_error.c \
						functions/array_thingy.c \
						functions/functions.c \
						functions/signal_handler.c \

SRCS.COMMANDS.CD =		commands/cd/cd.c \
						commands/cd/cd_tilde_expansion.c \
						commands/cd/check_pwd_oldpwd.c \
						commands/cd/non_working_dir_except.c \
						

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

SRCS.COMMANDS.EXIT = 	commands/exit/ft_exit.c \
						commands/exit/ret_exit.c \

SRCS.ENV.LIST =			env_list/env_lst_new.c \
						env_list/env_lstadd_back.c \
						env_list/env_lstlast.c \
						env_list/env_lstsize.c \

SRCS.ENV.LIST.FUNC =	env_list/functions/init.c \
						env_list/functions/search_env.c \

SRCS.EXECUTE =			execute/checkcommand.c \
						execute/createcommand_pipe.c \
						execute/execute.c \
						execute/redirections.c \
						execute/exec_cmd_builtin_pipe.c \
						execute/setup_builtin.c \

SRCS.EXECUTE =			execute/execute.c execute/run_cmd.c \
						execute/set_cmd.c \
						execute/redirections/loop_over_redirs.c \
						execute/redirections/redirections.c \
						execute/redirections/heredoc.c \
						execute/setup_single_cmd.c \
						execute/setup_pipes_cmd.c \
						execute/exit_status.c \
						

SRCS.NEWEXECUTE =		newexecute/execute.c newexecute/run_cmd.c \
						newexecute/set_cmd.c \
						newexecute/redirections/redirection_functions.c \
						newexecute/redirections/redirections.c \
						newexecute/redirections/set_redirections.c \
						newexecute/redirections/get_last_redir.c \
						newexecute/pipes/heredoc_pipes.c \
						newexecute/pipes/pipes.c \
						newexecute/pipes/setup_pipes.c \
						newexecute/pipes/clear_pipes.c \

SRCS.FREE =				free/free_all.c \
						free/free_commands.c \
						free/free_heredoc.c \

SRCS.NEW.PARSING = 		newparsing/parse.c \
						newparsing/parse_arraysize.c \
						newparsing/splitting/parse_split_spaces.c \
						newparsing/splitting/parse_split_commands.c \
						newparsing/splitting/parse_split_tokens.c \
						newparsing/checkword.c \
						newparsing/createstring.c \
						newparsing/tokens.c \
						newparsing/heredoc/heredoc_functions.c \
						newparsing/heredoc/heredoc_functions2.c \
						newparsing/heredoc/heredoc_parsing.c \
						newparsing/heredoc/heredoc_calc_len.c \
						newparsing/heredoc/heredoc_create_str.c \
						newparsing/heredoc/signal_handler_hdoc.c \
						newparsing/check_chars.c \

SRCS.CREATE.CMD =		cmd/create_cmd.c \
						cmd/declaring_values.c \
						cmd/tokens_cmd/tokens_cmd.c \
						cmd/tokens_cmd/set_tokens.c \
						cmd/tokens_cmd/init_new_tokens.c \
						cmd/tokens_cmd/count_tokens.c \
						cmd/tokens_cmd/set_heredoc_tokens.c \

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.c=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

SRC_B		:= $(notdir $(SRCS.BONUS))
OBJ_B		:= $(SRC_B:.c=.o)
OBJS_B	:= $(addprefix $(OBJDIR), $(OBJ_B))

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# Implicit rules
VPATH := $(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)

# ================================== RULES =================================== #

all : $(NAME)

linux : $(LIBFTLIB) $(SRCS)  $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRC)$(RC)\n"
	@$(CC) $(INCLUDES_L) $(CFLAGS) $(LIBFTLIB) $(OBJS) -o $(NAME) -lreadline -l:libft.a

mac : $(LIBFTLIB) $(SRCS)  $(OBJS)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRC)$(RC)\n"
	@$(CC) $(CFLAGS) $(LIBFTLIB) $(OBJS) -o $(NAME) $(INCLUDES_MAC) -lreadline -L /opt/homebrew/Cellar/readline/8.1.2/lib/
	
# Compiling
$(OBJDIR)%.o : %.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@  $(INCLUDES_MAC) -I/Users/$(USER)/.brew/opt/readline/include/

# Linking
$(NAME)	: $(LIBFTLIB) $(SRCS)  $(OBJS) $(INCLUDES)
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRC)$(RC)\n"
	@$(CC) $(CFLAGS) $(LIBFTLIB) $(OBJS) -o $(NAME) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

$(LIBFTLIB) :
	make -C $(LIBFTDIR)
	
# Cleaning
clean :
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean

fclean : clean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@make -C $(LIBFTDIR) fclean

# Special rule to force to remake everything
re : fclean all

# This runs the program
run : $(NAME)
	@printf "$(CY)>>> Running $(NAME)$(RC)\n"
	./$(NAME)

# This specifies the rules that does not correspond to any filename
.PHONY	= all run clean fclean re bonus