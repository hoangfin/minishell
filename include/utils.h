/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:06:08 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/28 23:19:42 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

t_bool		is_valid_env_key(const char *str);
const char	*find_env(const char *key, t_list *env_list);
int			update_env(const char *key, const char *value, t_list *env_list);
t_list		*clone_env_list(t_list *src_list);
const char	*find_logical_op(const char *str);
const char	*find_param_exp(const char *str);
void		ungroup(char *str);

#endif
