NAME := minishell

RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RESET := \033[0m

BUILD_DIR := build
LIBFT_DIR := libft

VPATH :=	src \
			src/builtin \
			src/command \
			src/io \
			src/minishell \
			src/signal \
			src/utils \

LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAG := -g -Wall -Wextra -Iinclude -I$(LIBFT_DIR)

SOURCES :=	main.c \
			ft_echo.c \
			ft_exit.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \
			exe_builtin.c \
			\
			init_minishell.c \
			clean_up.c \
			add_signal_handler.c \
			is_builtin_cmd.c \
			\
			count_arguments.c \
			delete_cmd.c \
			exe_cmd.c \
			new_cmd.c \
			parse_cmd.c \
			\
			delete_io.c \
			new_io.c
#			ft_cd.c
#			ft_env.c


OBJECTS := $(SOURCES:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(BUILD_DIR) $(LIBFT) $(OBJECTS)
#	@$(CC) $(CFLAG) $(OBJECTS) $(LIBFT) -L/Users/$(USER)/.brew/Cellar/readline/8.2.10/lib -lreadline -o $@
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
	@echo "$(RED)$(LIBFT)$(RESET) deleted."
	@rm -rf $(BUILD_DIR)
	@rm -f $(NAME)
	@echo "$(RED)$(NAME)$(RESET) deleted."

