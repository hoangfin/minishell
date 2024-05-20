/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:21:35 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/20 00:27:37 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "utils.h"
#include <stdio.h>
#include "builtin.h"

// cmd1 && (cmd2 || cmd3)
// cmd1 && cmd2 || cmd3
// (cmd1 && (cmd2 || cmd3)) || (cmd4 && cmd5) && cmd6
// (cmd1 && cmd2) || (cmd3 && cmd4) || cmd5 && cmd6

// static char	*get_log_op(const char *str)
// {
// 	int	depth;

// 	depth = 0;
// 	while (*str != '\0')
// 	{
// 		if (*str == '(')
// 			depth++;
// 		if (*str == ')')
// 			depth--;
// 		if (*str == '&' && *(str + 1) == '&' && depth == 0)
// 			return ((char *)str);
// 		if (*str == '|' && *(str + 1) == '|' && depth == 0)
// 			return ((char *)str);
// 		str++;
// 	}
// 	return (NULL);
// }

static int	handle_task(const char *str, t_minishell *minishell)
{
	t_list	*cmd_list;

	cmd_list = parse_cmd(str);
	if (cmd_list == NULL)
		return (-1);
	if (
		cmd_list->length == 1
		&& is_builtin_cmd(((t_command *)cmd_list->head->data)->argv[0])
	)
		return (exe_builtin(
			((t_command *)cmd_list->head->data),
			minishell->env_list,
			minishell->exit_status
		));
	return (0);
}

int	exe_cmd(const char *str, t_minishell *minishell)
{
	return (handle_task(str, minishell));
}

// int main(void)
// {
// 	const char	*str = "(cmd1 && (cmd2 || cmd3)) || (cmd4 && cmd5) && cmd6";
// 	printf("%s\n", get_log_op(str));
// 	return (0);
// }