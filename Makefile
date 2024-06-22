NAME := minishell

RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RESET := \033[0m

BUILD_DIR := build
LIBFT_DIR := libft
READLINE_DIR := /usr/include

VPATH :=	src \
			src/builtin \
			src/command \
			src/io \
			src/minishell \
			src/signal \
			src/utils \
			src/validation \
			src/executor

LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAG := -g -Wall -Wextra -Iinclude -I$(LIBFT_DIR) -I$(READLINE_DIR)

SOURCES :=	main.c \
			ft_cd.c \
			ft_echo.c \
			ft_env.c \
			ft_exit.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \
			\
			close_pipes.c \
			delete_executor.c \
			delete_minishell.c \
			execute_command.c \
			execute.c \
			exit_on_error.c \
			expand_cmd.c \
			expand_dollar.c \
			init_minishell.c \
			new_executor.c \
			resolve_env.c \
			run_executor.c \
			set_exit_status.c \
			run_minishell.c \
			heredoc.c \
			redirect.c \
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
			is_valid_env_key.c \
			parse_cmd_list.c \
			print_export_list.c \
			set_env.c \
			ungroup.c \
			update_env.c \
			wait_all.c \
			is_underscore_var.c \
			update_underscore_var.c \
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
			validate_arrow.c \
			validate_input.c \
			validate_quotes.c \
			validate_vertical_bar.c \
			validate_ampersand.c \
			\
			reset_signals.c \
			set_signal_handler.c \
			signal_handlers.c

OBJECTS := $(SOURCES:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(BUILD_DIR) $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAG) $(OBJECTS) $(LIBFT) -lreadline -o $@
	@echo -e "$(YELLOW)$@$(RESET) created."

$(BUILD_DIR):
	@mkdir -p $@
	@echo "Compiling ..."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --silent
	@echo -e "$(YELLOW)$(LIBFT)$(RESET) created."

$(BUILD_DIR)/%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@echo -e "$(RED)$(LIBFT)$(RESET) deleted."
	@rm -rf $(BUILD_DIR)
	@rm -f $(NAME)
	@echo -e "$(RED)$(NAME)$(RESET) deleted."

re: fclean all
