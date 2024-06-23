NAME := minishell

RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RESET := \033[0m

BUILD_DIR := build
LIBFT_DIR := libft
READLINE_DIR := /usr/include

LIBFT := $(LIBFT_DIR)/libft.a

VPATH :=	src \
			src/builtin \
			src/command \
			src/io \
			src/minishell \
			src/signal \
			src/utils \
			src/validation

CC := cc
CFLAG := -Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR) -I$(READLINE_DIR)

SOURCES :=	main.c \
			ft_cd.c \
			ft_echo.c \
			ft_env.c \
			ft_exit.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \
			\
			check_builtin.c \
			check_wildcard.c \
			count_arguments.c \
			delete_cmd.c \
			new_cmd.c \
			parse_cmd.c \
			\
			delete_io.c \
			new_io.c \
			\
			close_pipes.c \
			delete_executor.c \
			delete_minishell.c \
			execute_command.c \
			execute.c \
			exit_on_error.c \
			expand_cmd.c \
			expand_dollar.c \
			heredoc.c \
			init_minishell.c \
			new_executor.c \
			redirect.c \
			resolve_env.c \
			run_executor.c \
			run_minishell.c \
			set_exit_status.c \
			\
			reset_signals.c \
			set_signal_handler.c \
			signal_handlers.c \
			\
			clone_env_list.c \
			count_str_array.c \
			dup2_close.c \
			expand_wildcard.c \
			find_env.c \
			find_logical_op.c \
			find_redirect_op.c \
			find_symbol.c \
			ft_readline.c \
			get_envp.c \
			get_path.c \
			is_delimiter.c \
			is_directory.c \
			is_key_exist.c \
			is_underscore_var.c \
			is_valid_env_key.c \
			parse_cmd_list.c \
			print_export_list.c \
			ungroup.c \
			update_env.c \
			update_underscore_var.c \
			wait_all.c \
			\
			validate_ampersand.c \
			validate_arrow.c \
			validate_input.c \
			validate_parentheses.c \
			validate_quotes.c \
			validate_vertical_bar.c

OBJECTS := $(SOURCES:%.c=$(BUILD_DIR)/%.o)
BONUS_OBJECTS := $(patsubst $(BUILD_DIR)/main.o, $(BUILD_DIR)/main_bonus.o, $(OBJECTS))

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(BUILD_DIR) $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAG) $(OBJECTS) $(LIBFT) -lreadline -o $@
	@printf "$(YELLOW)$@$(RESET) created.\n"

$(BUILD_DIR):
	@mkdir -p $@
	@echo "Compiling ..."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --silent
	@printf "$(YELLOW)$(LIBFT)$(RESET) created.\n"

$(BUILD_DIR)/%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@

bonus: .bonus

.bonus: $(BUILD_DIR) $(LIBFT) $(BONUS_OBJECTS)
	@$(CC) $(CFLAG) $(BONUS_OBJECTS) $(LIBFT) -lreadline -o $(NAME)
	@touch .bonus
	@printf "$(YELLOW)$(NAME)$(RESET) created.\n"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@rm -rf $(BUILD_DIR)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@printf "$(RED)$(LIBFT)$(RESET) deleted.\n"
	@rm -rf $(BUILD_DIR)
	@rm -rf .bonus
	@rm -f $(NAME)
	@printf "$(RED)$(NAME)$(RESET) deleted.\n"

re: fclean all
