/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:06:08 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/08 12:17:05 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include "libft.h"

t_bool		is_valid_env_key(const char *str);
t_bool		is_directory(const char *pathname);
const char	*find_env(const char *key, t_list *env_list);
int			update_env(const char *key, const char *value, t_list *env_list);
t_list		*clone_env_list(t_list *src_list);
t_list		*parse_cmd_list(const char *str);
const char	*find_logical_op(const char *str);
const char	*find_param_exp(const char *str);
char *const	*get_envp(t_list *env_list);
const char	**get_path(t_list *env_list);
void		ungroup(char *str);
int			redirect_input(t_list *input_list, int pipedes);
int			redirect_output(t_list *output_list, int pipedes);
int			close_pipes(int **pipes);
int			wait_all(pid_t *pids, int number_of_pids);
int			dup2_close(int oldfd, int newfd);
size_t		count_str_array(const char **str_array);
int			replace_wildcard(char **str);

#endif
