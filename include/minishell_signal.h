/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:29:40 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/07 13:35:11 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

# include <signal.h>

int		set_signal_handler(int signum, void (*handler)(int));
int		reset_signals(void);

void	newline_handler(int signum);

#endif
