/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:06:08 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/14 16:07:50 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include "libft.h"

t_bool		is_delimiter(const char *str, const char *dollar);
t_bool		is_directory(const char *pathname);
t_bool		is_key_exist(t_node *node, void *data);
t_bool		is_valid_env_key(const char *str);

const char	*find_env(const char *key, t_list *env_list);
int			update_env(const char *key, const char *value, t_list *list);
t_list		*clone_env_list(t_list *src_list);
t_list		*parse_cmd_list(const char *str);
char		*find_symbol(const char *str, const char *symbol);
char		*find_logical_op(const char *str);
char *const	*get_envp(t_list *env_list);
const char	**get_path(t_list *env_list);
void		ungroup(char *str);
int			wait_all(pid_t *pids, int number_of_pids);
int			dup2_close(int oldfd, int newfd);
size_t		count_str_array(const char **str_array);
int			replace_wildcard(char **str);
int			print_export_list(t_list *export_list);
int			is_underscore_var(char *cmd_arg);
void		find_redirect_op(\
				const char *str, \
				int redirect_op, \
				char **start, \
				char **end \
			);

#endif
