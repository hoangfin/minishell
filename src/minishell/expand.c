/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:36:57 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/13 23:32:58 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static int	update_result(char **result, char *substr, char *env_value)
{
	if (substr == NULL)
		return (-1);
	if (env_value == NULL)
	{
		if (ft_concat(result, 1, substr) < 0)
			return (free(substr), -1);
		free(substr);
		return (0);
	}
	if (ft_concat(result, 2, substr, env_value) < 0)
		return (free(substr), -1);
	free(substr);
	return (0);
}

static char	*resolve(const char **dollar, t_minishell *mns)
{
	const char	*start = *dollar;

	(*dollar)++;
	if (**dollar == '?')
	{
		(*dollar)++;
		return (mns->exit_status_str);
	}
	if (
		**dollar == '\0'
		|| **dollar == '\''
		|| **dollar == '"'
		|| ft_isspace(**dollar)
	)
		return ("$");
	while (
		**dollar != '\0'
		&& **dollar != '"'
		&& **dollar != '\''
		&& !ft_isspace(**dollar)
	)
		(*dollar)++;
	return (resolve_env(start + 1, *dollar - (start + 1), mns));
}

static void	update_quote(char *quote, int value)
{
	if (value == '\'' || value == '"')
	{
		if (*quote == 0)
			*quote = value;
		else if (*quote == value)
			*quote = 0;
	}
}

static int	get_result(char **result, const char *str, t_minishell *minishell)
{
	const char	*start = str;
	const char	*end = str;
	char		*substr;
	char		*env_value;
	char		quote;

	quote = 0;
	while (*end != '\0')
	{
		update_quote(&quote, *end);
		if (*end == '$' && (quote == 0 || quote == '"')
			&& !is_delimiter(str, end))
		{
			substr = ft_substr(start, 0, end - start);
			env_value = resolve(&end, minishell);
			if (update_result(result, substr, env_value) < 0)
				return (-1);
			start = end;
			continue ;
		}
		end++;
	}
	if (ft_concat(result, 1, start) < 0)
		return (-1);
	return (0);
}

int	expand(char **str, t_minishell *minishell)
{
	char	*result;

	result = NULL;
	if (get_result(&result, *str, minishell) < 0)
	{
		free(result);
		return (-1);
	}
	free(*str);
	*str = result;
	return (0);
}
