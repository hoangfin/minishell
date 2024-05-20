#include "command.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	print_list_item(t_node *node, size_t index)
{
	(void)index;
	printf(
		"    item[%lu]: [redirection-type=%d, token=%s]\n",
		index,
		((t_io *)node->data)->redi_type,
		((t_io *)node->data)->token
	);
}

static void print_cmd(t_command *cmd)
{
	int	i;

	i = 0;
	printf("- argvs: [");
	while (cmd->argv[i] != NULL)
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			printf(", ");
		i++;
	}
	printf("]\n");

	if (cmd->input_list->length == 0)
		printf("- input_list EMPTY\n");
	else
	{
		printf("- input_list (%lu items): [\n", cmd->input_list->length);
		ft_list_foreach(cmd->input_list, print_list_item);
		printf("]\n");
	}

	if (cmd->output_list->length == 0)
		printf("- output_list EMPTY\n");
	else
	{
		printf("- output_list (%lu items): [\n", cmd->output_list->length);
		ft_list_foreach(cmd->output_list, print_list_item);
		printf("]\n");
	}
}

int main(void) {
	// const char	*case_1 = "echo > hello.txt";
	// const char	*case_2 = "cmd_1<h\"ell\"o.txt";
	// const char	*case_3 = "cmd_1<h\"'ell'\"o.txt";
	// const char	*case_4 = "cmd_1<h\"'''ell'''\"o.txt";
	// const char	*case_5 = "cmd_1<h'\"\"ell\"\"'o.txt";
	// const char	*case_6 = "cmd_1<h'\"ell\"'\"   \"o.txt";
	t_command	*cmd;
	char		*line;

	while (1)
	{
		line = readline("minishell> ");
		if (strcmp(line, "exit") == 0)
			break ;
		cmd = new_cmd(line);
		print_cmd(cmd);
		delete_cmd(cmd);
		free(line);
	}
	return (0);
}