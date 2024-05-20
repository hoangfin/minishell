#include "io.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	const char	*case_1 = "cmd_1<hello.txt";
	const char	*case_2 = "cmd_1<h\"ell\"o.txt";
	const char	*case_3 = "cmd_1<h\"'ell'\"o.txt";
	const char	*case_4 = "cmd_1<h\"'''ell'''\"o.txt";
	const char	*case_5 = "cmd_1<h'\"\"ell\"\"'o.txt";
	const char	*case_6 = "cmd_1<h'\"ell\"'\"   \"o.txt";
	t_io		*io;

	io = new_io(case_1, '<');
	assert(io != NULL);
	assert(io->redi_type == REDIR_INPUT);
	assert(strcmp(io->token, "hello.txt") == 0);
	delete_io(io);

	io = new_io(case_2, '<');
	assert(io != NULL);
	assert(io->redi_type == REDIR_INPUT);
	assert(strcmp(io->token, "hello.txt") == 0);
	delete_io(io);

	io = new_io(case_3, '<');
	assert(io != NULL);
	assert(io->redi_type == REDIR_INPUT);
	assert(strcmp(io->token, "h'ell'o.txt") == 0);
	delete_io(io);

	io = new_io(case_4, '<');
	assert(io != NULL);
	assert(io->redi_type == REDIR_INPUT);
	assert(strcmp(io->token, "h'''ell'''o.txt") == 0);
	delete_io(io);

	io = new_io(case_5, '<');
	assert(io != NULL);
	assert(io->redi_type == REDIR_INPUT);
	assert(strcmp(io->token, "h\"\"ell\"\"o.txt") == 0);
	delete_io(io);

	io = new_io(case_6, '<');
	assert(io != NULL);
	assert(io->redi_type == REDIR_INPUT);
	printf("%s\n", io->token);
	assert(strcmp(io->token, "h\"ell\"   o.txt") == 0);
	delete_io(io);
}