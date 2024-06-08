/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:36:57 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/07 22:21:46 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static int	reduce(char **result, const char *str, t_minishell *minishell)
{
	const char	*dollar;
	const char	*value;
	int			i;

	dollar = find_param_exp(str);
	if (dollar == NULL)
	{
		if (ft_concat(result, 1, str) < 0)
			return (-1);
		return (0);
	}
	i = 1;
	while (
		dollar[i] != '\0' && !ft_isspace(dollar[i])
		&& dollar[i] != '"' && dollar[i] != '\''
	)
		i++;
	value = resolve_env(&dollar[1], i - 1, minishell);
	if (value != NULL)
	{
		if (ft_concat(result, 1, value) < 0)
			return (-1);
	}
	return (reduce(result, &dollar[i], minishell));
}

int	expand(char **str, t_minishell *minishell)
{
	const char	*dollar;
	char		*result;

	dollar = find_param_exp(*str);
	if (dollar == NULL)
		return (0);
	result = ft_substr(*str, 0, dollar - (*str));
	if (result == NULL)
		return (-1);
	if (reduce(&result, dollar, minishell) < 0)
	{
		free(result);
		return (-1);
	}
	if (result != NULL)
	{
		free(*str);
		*str = result;
	}
	return (0);
}
