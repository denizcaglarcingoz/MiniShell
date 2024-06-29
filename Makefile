EXECUTABLE := minishell
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./includes
BT_DIR = ./builtins

#INCLUDES = $(wildcard $(INC_DIR)/*)

INCLUDES = ./inlcudes/execution.h ./inlcudes/lexer.h ./inlcudes/minishell.h ./includes/parser.h

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)  $(wildcard $(SRC_DIR)/*/*/*.c) $(wildcard $(SRC_DIR)/*/*/*/*.c)

#SRCS =	backend/execution/exec_utils.c\
		backend/execution/execution.c \
		backend/execution/last_redirect.c \
		backend/execution/output_check.c \
		backend/execution/pipe_exec_run.c \
		backend/execution/pipe_exec_utils.c \
		backend/execution/pipe_exec.c \
		backend/execution/single_exec.c \
		\
		backend/execve/execve_utils.c \
		backend/execve/ft_access.c \
		backend/execve/ft_execve.c \
		backend/execve/get_exit_code.c \
		backend/execve/pipe_execve.c \
		\
		backend/expansion/arg_expand/arg_expand_utils.c \
		backend/expansion/arg_expand/arg_expand.c \
		backend/expansion/arg_expand/split_join.c \
		\
		backend/expansion/expand_utils/expand_utils.c \
		\
		backend/expansion/redir_expand/add_new_content.c \
		backend/expansion/redir_expand/exp_check.c \
		backend/expansion/redir_expand/hdoc_expand_quo.c \
		backend/expansion/redir_expand/hdoc_expand.c \
		backend/expansion/redir_expand/redir_expand_utils.c \
		backend/expansion/redir_expand/redir_expand.c \
		\
		backend/expansion/content_check.c \
		backend/expansion/empty_str_dup.c \
		backend/expansion/expandor.c \
		backend/expansion/question_mark.c\
		backend/expansion/quotes.c \
		\
		backend/redirections/heredoc.c \
		backend/redirections/output.c \
		\
		builtins/add_env.c \
		builtins/builtin_utils.c \
		builtins/builtin.c \
		builtins/cd.c \
		builtins/delete_env.c \
		builtins/echo.c \
		builtins/env_update_utils.c \
		builtins/env_utils.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/ft_getenv.c \
		builtins/pwd.c \
		builtins/quicksort_params.c \
		builtins/unset.c \
		\
		frontend/lexer/lexer_init_loop_utils.c \
		frontend/lexer/lexer_meta_utils.c \
		frontend/lexer/lexer_string_utils.c \
		frontend/lexer/lexer.c \
		\
		frontend/parser/grammer_check.c \
		frontend/parser/parser.c \
		frontend/parser/table_alloc.c \
		frontend/parser/table_content_alloc.c \
		frontend/parser/table_init.c \
		\
		signals/signals_int.c \
		signals/signals.c \
		\
		testing/print_tables.c \
		testing/print_tokens.c \
		\
		utils/checker.c \
		utils/free_all.c \
		utils/free_d_str.c \
		utils/free_exit_utils.c \
		utils/freeing_utils.c \
		utils/print_utils.c \
		utils/table_free.c \
		\
		main.c


OBJ = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CFLAGS := -Wall -Wextra -Werror -fPIE -g -Iincludes

RM := rm -f

LIBFT_PATH = includes/libft

LIBFT_ARCH = $(LIBFT_PATH)/libft.a

CC := cc

OBS := $(SRCS:.c=.o)

MAKEFLAGS += --no-print-directory


.SILENT:

all: $(LIBFT_ARCH) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -L$(LIBFT_PATH) -lft -lreadline -lhistory -o $@ 

$(LIBFT_ARCH):
	$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re