NAME := minishell

SRCS := main.c print_intro.c signals/signals.c utils/list_utils.c lexer.c checker.c
  
CFLAGS := -Wall -Wextra -Werror -I./headers

OBJDIR := objects

RM := rm -f

LIBFT_PATH = libft

LIBFT_ARCH = $(LIBFT_PATH)/libft.a

CC := cc

OBS := $(SRCS:/%.c=$(OBJDIR)/%.o)

COLOR_RESET = \033[0m
COLOR_GREEN = \033[1;92m
COLOR_BLUE = \033[1;96m 

MAKEFLAGS += --no-print-directory

define print_colored
	@echo "$(COLOR_GREEN)$(1)$(COLOR_BLUE)$(2)$(COLOR_RESET)$(3)"
endef

.SILENT:

all: $(LIBFT_ARCH) $(NAME)

$(NAME): $(OBS)
	$(CC) $^ -L$(LIBFT_PATH) -lft -lreadline -lhistory -o $@
	$(call print_colored, "[SUCCESS]", "./$(NAME)", "Ready")

$(LIBFT_ARCH):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBS)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re