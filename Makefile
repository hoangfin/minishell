NAME := minishell

BUILD_DIR := build
LIBFT_DIR := libft

VPATH :=	src \
			src/builtin \
			src/initialization

LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAG := -Wall -Wextra -I$(LIBFT_DIR)

SOURCES :=	main.c \
			ft_echo.c \
			ft_env.c \
			ft_exit.c \
			ft_export.c \
			ft_pwd.c \
			ft_unset.c \
			init_minishell.c

OBJECTS := $(SOURCES:%.c=$(BUILD_DIR)/%.o)

$(info OBJECTS = $(OBJECTS))

all: $(NAME)

$(NAME): $(BUILD_DIR) $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAG) $(OBJECTS) $(LIBFT) -o $@

$(BUILD_DIR):
	@mkdir -p $@
	@echo "Compiling ..."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft.a has been created."

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(LIBFT) deleted."
	@rm -rf $(BUILD_DIR)

