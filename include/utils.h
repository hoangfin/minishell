/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:06:08 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/27 17:59:45 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

t_bool		is_builtin_cmd(const char *str);
t_bool		is_valid_env_key(const char *str);
const char	*find_env(const char *key, t_list *env_list);
int			update_env(const char *key, const char *value, t_list *env_list);
t_list		*clone_env_list(t_list *src_list);

#endif
