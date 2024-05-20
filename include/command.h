/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:18:49 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/20 00:08:00 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"
# include "io.h"
# include "minishell.h"

typedef struct s_command
{
	char	**argv;
	t_list	*input_list;
	t_list	*output_list;
}	t_command;

t_command	*new_cmd(const char *str);
void		delete_cmd(void *cmd);
t_list		*parse_cmd(const char *str);
int			exe_cmd(const char *str, t_minishell *minishell);

#endif
