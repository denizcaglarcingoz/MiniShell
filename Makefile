

EXECUTABLE := minishell
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./includes
BT_DIR = ./builtins

INCLUDES = ./includes/execution.h ./includes/lexer.h ./includes/minishell.h ./includes/parser.h

SRCS =	./src/backend/execution/child_out_check.c \
		./src/backend/execution/exec_utils.c \
		./src/backend/execution/execution.c \
		./src/backend/execution/last_redirect.c \
		./src/backend/execution/not_in_file.c \
		./src/backend/execution/output_check.c \
		./src/backend/execution/pipe_closings.c \
		./src/backend/execution/pipe_exec_run.c \
		./src/backend/execution/pipe_exec_utils.c \
		./src/backend/execution/pipe_exec.c \
		./src/backend/execution/pipe_hdoc.c \
		./src/backend/execution/single_exec_run.c \
		./src/backend/execution/single_exec.c \
		\
		./src/backend/execve/ft_access.c \
		./src/backend/execve/ft_execve_path_append.c\
		./src/backend/execve/ft_execve.c \
		./src/backend/execve/ft_execve_utils.c \
		./src/backend/execve/get_exit_code.c \
		./src/backend/execve/pipe_execve.c \
		\
		./src/backend/expansion/arg_expand/arg_expand_utils.c \
		./src/backend/expansion/arg_expand/arg_expand.c \
		./src/backend/expansion/arg_expand/split_join.c \
		\
		./src/backend/expansion/expand_utils/expand_utils.c \
		\
		./src/backend/expansion/redir_expand/add_first_loop.c \
		./src/backend/expansion/redir_expand/add_new_content_utils.c \
		./src/backend/expansion/redir_expand/add_new_content.c \
		./src/backend/expansion/redir_expand/add_second_loop.c \
		./src/backend/expansion/redir_expand/exp_check.c \
		./src/backend/expansion/redir_expand/hdoc_expand_quo.c \
		./src/backend/expansion/redir_expand/hdoc_expand.c \
		./src/backend/expansion/redir_expand/redir_expand_utils.c \
		./src/backend/expansion/redir_expand/redir_expand.c \
		\
		./src/backend/expansion/content_check.c \
		./src/backend/expansion/empty_str_dup.c \
		./src/backend/expansion/expandor.c \
		./src/backend/expansion/question_mark.c\
		./src/backend/expansion/quotes.c \
		\
		./src/backend/redirections/hdoc_inside_expand.c \
		./src/backend/redirections/heredoc.c \
		./src/backend/redirections/output.c \
		./src/backend/redirections/hdoc_inside_exp_util.c \
		\
		./src/builtins/add_env.c \
		./src/builtins/builtin_utils.c \
		./src/builtins/builtin.c \
		./src/builtins/cd.c \
		./src/builtins/delete_env.c \
		./src/builtins/echo.c \
		./src/builtins/env_update_utils.c \
		./src/builtins/env_utils.c \
		./src/builtins/exit.c \
		./src/builtins/export.c \
		./src/builtins/ft_getenv.c \
		./src/builtins/pwd.c \
		./src/builtins/quicksort_params.c \
		./src/builtins/unset.c \
		\
		./src/frontend/lexer/lexer_init_loop_utils.c \
		./src/frontend/lexer/lexer_meta_utils.c \
		./src/frontend/lexer/lexer_string_utils.c \
		./src/frontend/lexer/lexer.c \
		\
		./src/frontend/parser/grammer_check.c \
		./src/frontend/parser/parser.c \
		./src/frontend/parser/table_alloc.c \
		./src/frontend/parser/table_content_alloc.c \
		./src/frontend/parser/table_init.c \
		\
		./src/signals/signals_int.c \
		./src/signals/signals.c \
		\
		./src/testing/print_tables.c \
		./src/testing/print_tokens.c \
		\
		./src/utils/checker.c \
		./src/utils/free_all.c \
		./src/utils/free_d_str.c \
		./src/utils/free_exit_utils.c \
		./src/utils/freeing_utils.c \
		./src/utils/print_utils.c \
		./src/utils/table_free.c \
		./src/utils/ft_pid.c \
		./src/utils/ft_strncpy.c \
		./src/utils/temp_hdoc.c \
		\
		./src/main.c


OBJ = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CFLAGS := -Wall -Wextra -Werror -Iincludes

RM := rm -f

LIBFT_PATH = includes/libft

LIBFT_ARCH = $(LIBFT_PATH)/libft.a

CC := cc

OBS := $(SRCS:.c=.o)

MAKEFLAGS += --no-print-directory


all: $(LIBFT_ARCH) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -L$(LIBFT_PATH) -lft -lreadline -lhistory -o $@ 

$(LIBFT_ARCH):
	$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJ)

fclean: clean
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(EXECUTABLE)

re: fclean all



.PHONY: all clean fclean re
