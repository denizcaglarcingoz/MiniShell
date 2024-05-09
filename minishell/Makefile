EXECUTABLE := minishell
SRC_DIR = ./src
OBJ_DIR = ./obj
INC_DIR = ./includes
BT_DIR = ./builtins

INCLUDES = $(wildcard $(INC_DIR)/*)
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)  $(wildcard $(SRC_DIR)/*/*/*.c)
OBJ = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CFLAGS := -Wall -Wextra -Werror -fPIE -g -Iincludes

RM := rm -f

LIBFT_PATH = includes/libft

LIBFT_ARCH = $(LIBFT_PATH)/libft.a

CC := cc

OBS := $(SRCS:.c=.o)

COLOR_RESET = \033[0m
COLOR_GREEN = \033[1;92m
COLOR_BLUE = \033[1;96m 

MAKEFLAGS += --no-print-directory

define print_colored
	@echo "$(COLOR_GREEN)$(1)$(COLOR_BLUE)$(2)$(COLOR_RESET)$(3)"
endef

.SILENT:

all: $(LIBFT_ARCH) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -L$(LIBFT_PATH) -lft -lreadline -lhistory -o $@ 
	$(call print_colored, "[SUCCESS]", "./$(EXECUTABLE)", "Ready")

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