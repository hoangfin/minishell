cc -g \
	-Iinclude -Ilibft \
	src/io/*.c \
	src/command/new_cmd.c src/command/delete_cmd.c \
	src/test/new_cmd_test.c \
	libft/libft.a \
	-lreadline

./a.out