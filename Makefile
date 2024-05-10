NAME := minishell

RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RESET := \033[0m

BUILD_DIR := build
LIBFT_DIR := libft

VPATH :=	src \
			src/builtin \
			src/initialization

LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAG := -g -Wall -Wextra -I$(LIBFT_DIR) -I/usr/include

SOURCES :=	main.c \
			ft_echo.c \
			ft_env.c \
			ft_exit.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \
			init_minishell.c \
			clean_up.c

OBJECTS := $(SOURCES:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(BUILD_DIR) $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAG) $(OBJECTS) $(LIBFT) -lreadline -o $@
	@echo "$(YELLOW)$@$(RESET) created."

$(BUILD_DIR):
	@mkdir -p $@
	@echo "Compiling ..."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --silent
	@echo "$(YELLOW)$(LIBFT)$(RESET) created."

$(BUILD_DIR)/%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@echo "$(LIBFT) deleted."
	@rm -rf $(BUILD_DIR)
	@rm -f $(NAME)
	@echo "$(NAME) deleted."

