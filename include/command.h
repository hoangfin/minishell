/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:18:49 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/15 16:36:50 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"

typedef enum s_operator
{
	NO_OP,
    OP_INPUT_REDIRECT,
	OP_INPUT_HEREDOC,
	OP_OUTPUT_REDIRECT,
    OP_OUTPUT_APPEND,
    OP_PIPE,
    OP_AND,
    OP_OR,
}	t_operator;

typedef struct s_io
{
	char		*name;
	t_operator	operator;
}	t_io;

typedef struct s_command
{
	char	**argv;
	t_list	*input_list;
	t_list	*output_list;
}	t_command;

typedef struct s_command_line
{
	t_command	*cmds;
	int			pipes_count;
}	t_command_line;

t_command	*parse_command(char *cmd_str);
int			exe_cmd(t_command cmd);
// size_t		count_arguments(t_command *cmd);

#endif
