/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_on_current_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:21:35 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/30 22:13:22 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "constants.h"
#include "execution.h"
#include "builtin.h"
#include "io.h"
#include "utils.h"

// static void	handle_execve_error(t_pipex *pipex, char *cmd_name)
// {
// 	ft_fprintf(2, "pipex: %s: ", cmd_name);
// 	if (errno == ENOENT)
// 	{
// 		if (pipex->paths == NULL)
// 			ft_exit(pipex, strerror(errno), false, 127);
// 		else
// 		{
// 			if (
// 				ft_starts_with(cmd_name, "/")
// 				|| ft_starts_with(cmd_name, "./")
// 				|| ft_ends_with(cmd_name, "/")
// 			)
// 				ft_exit(pipex, strerror(errno), false, 127);
// 			else
// 				ft_exit(pipex, "command not found", false, 127);
// 		}
// 	}
// 	if (errno == EACCES || errno == EISDIR)
// 		ft_exit(pipex, strerror(errno), false, 126);
// 	ft_exit(pipex, strerror(errno), false, 1);
// }

// static int	try_read(const char *pathname)
// {
// 	int		fd;
// 	char	buf;

// 	fd = open(pathname, O_RDONLY);
// 	if (fd < 0)
// 		return (-1);
// 	if (read(fd, &buf, 1) < 0)
// 	{
// 		close(fd);
// 		return (-1);
// 	}
// 	if (close(fd) < 0)
// 		return (-1);
// 	return (0);
// }

// static int	handle_pathname(char **envp, char **command)
// {
// 	if (command[0][0] == '\0')
// 		return (execve(command[0], command, NULL));
// 	// if (ft_starts_with(command[0], "/") || ft_starts_with(command[0], "./"))
// 	if (ft_strchr(command[0], '/') != NULL)
// 	{
// 		if (try_read(command[0]) < 0 && errno == EISDIR)
// 			return (-1);
// 		return (execve(command[0], command, envp));
// 	}
// 	return (0);
// }

// static int	call_execve(char **envp, char **paths, char **command)
// {
// 	char	*cmd_path;
// 	int		status;

// 	if (handle_pathname(envp, command) < 0)
// 		return (-1);
// 	status = 0;
// 	while (paths != NULL && *paths != NULL)
// 	{
// 		cmd_path = ft_join_strings(3, *paths, "/", command[0]);
// 		if (cmd_path == NULL)
// 			return (-1);
// 		if (access(cmd_path, X_OK) == 0)
// 			status = execve(cmd_path, command, envp);
// 		free(cmd_path);
// 		if (status == -1)
// 			return (-1);
// 		paths++;
// 	}
// 	errno = ENOENT;
// 	return (-1);
// }

static int	handle_error(const char *err_src, const char *err_msg)
{
	ft_fprintf(\
		STDERR_FILENO, \
		"minishell: %s: %s\n", \
		err_src, \
		err_msg \
	);
	return (1);
}

int	run_on_current_process(t_command *cmd, t_minishell *minishell)
{
	const int	stdin = dup(STDIN_FILENO);
	const int	stdout = dup(STDOUT_FILENO);
	int			exit_status;

	if (stdin < 0 || stdout < 0)
		return (handle_error("dup", strerror(errno)));
	if (
		redirect_input(cmd->input_list) < 0
		|| redirect_output(cmd->output_list) < 0
	)
		return (1);
	exit_status = run_builtin(cmd, minishell);
	unlink(HERE_DOC_TEMP_FILE);
	if (dup2(stdin, STDIN_FILENO) < 0 || dup2(stdout, STDOUT_FILENO) < 0)
		return (handle_error("dup2", strerror(errno)));
	if (close(stdin) < 0 || close(stdout) < 0)
		return (handle_error("close", strerror(errno)));
	return (exit_status);
}
