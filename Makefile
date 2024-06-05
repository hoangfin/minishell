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
			src/validation \
			src/executor

LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAG := -g -Wall -Wextra -Iinclude -I$(LIBFT_DIR)

SOURCES :=	main.c \
			ft_cd.c \
			ft_echo.c \
			ft_env.c \
			ft_exit.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \
			\
			delete_executor.c \
			delete_minishell.c \
			execute_command.c \
			execute.c \
			expand.c \
			init_minishell.c \
			new_executor.c \
			resolve_env.c \
			run_executor.c \
			set_exit_status.c \
			start_minishell.c \
			\
			clone_env_list.c \
			close_pipes.c \
			count_str_array.c \
			dup2_close.c \
			find_env.c \
			find_logical_op.c \
			find_param_exp.c \
			get_envp.c \
			get_path.c \
			is_directory.c \
			is_valid_env_key.c \
			parse_cmd_list.c \
			redirect_input.c \
			redirect_output.c \
			ungroup.c \
			update_env.c \
			wait_all.c \
			\
			count_arguments.c \
			delete_cmd.c \
			new_cmd.c \
			\
			delete_io.c \
			new_io.c \
			\
			validate_arrow.c \
			validate_input.c \
			validate_quotes.c \
			validate_vertical_bar.c \
			validate_ampersand.c

OBJECTS := $(SOURCES:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(BUILD_DIR) $(LIBFT) $(OBJECTS)
	@$(CC) $(CFLAG) $(OBJECTS) $(LIBFT) -L/Users/$(USER)/.brew/Cellar/readline/8.2.10/lib -lreadline -o $@
#	@$(CC) $(CFLAG) $(OBJECTS) $(LIBFT) -lreadline -o $@
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
