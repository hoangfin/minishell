/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:58:46 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/29 20:27:16 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

typedef enum e_redir_type
{
	REDIR_NO,
	REDIR_INPUT,
	REDIR_HEREDOC,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_PIPE,
}	t_redir_type;

typedef struct s_io
{
	t_redir_type	redi_type;
	char			*token;
	int				pipedes;
}	t_io;

t_io	*new_io(const char *str, int redir_symbol);
void	delete_io(void *io);

#endif
