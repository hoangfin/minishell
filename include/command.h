/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:18:49 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/28 23:46:16 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"

typedef struct s_command
{
	char	**argv;
	t_list	*input_list;
	t_list	*output_list;
	t_bool	is_builtin;
}	t_command;

t_command	*new_cmd(const char *str);
void		delete_cmd(void *cmd);
t_list		*parse_cmd(const char *str);
size_t		count_arguments(t_command *cmd);

#endif
