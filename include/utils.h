/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:06:08 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/18 02:06:24 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include "libft.h"

t_bool		is_delimiter(const char *str, const char *symbol);
t_bool		is_directory(const char *pathname);
t_bool		is_key_exist(t_node *node, void *data);
t_bool		is_valid_env_key(const char *str);

t_list		*clone_env_list(t_list *src_list);
t_list		*parse_cmd_list(const char *str);

int			update_env(const char *key, const char *value, t_list *list);
int			wait_all(pid_t *pids, int number_of_pids);
int			dup2_close(int oldfd, int newfd);
int			expand_wildcard(char **cmd_arg);
int			print_export_list(t_list *export_list);
int			is_underscore_var(char *cmd_arg);

size_t		count_str_array(const char **str_array);

const char	*find_env(const char *key, t_list *env_list);
char *const	*get_envp(t_list *env_list);
const char	**get_path(t_list *env_list);

char		*find_logical_op(const char *str);
char		*find_symbol(const char *str, const char *symbol);
char		*ft_readline(const char *prompt);

void		ungroup(char *str);
void		find_redirect_op(const char *str, char **start, char **end);

#endif
