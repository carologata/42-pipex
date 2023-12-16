/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:27:15 by cogata            #+#    #+#             */
/*   Updated: 2023/12/16 17:27:16 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_first_cmd(t_cmd *sys, int (*fds)[2], int i)
{
	int	fork_id;
	int	status;

	if (pipe(fds[i]) == -1)
		exit_free_error(sys);
	fork_id = fork();
	if (fork_id == -1)
		exit_free_error(sys);
	else if (fork_id == 0)
		execute_first_cmd(sys, fds, i);
	else
	{
		waitpid(fork_id, &status, 0);
		close(fds[i][1]);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			free_all(sys);
			exit(ERROR);
		}
	}
}

void	process_last_cmd(t_cmd *sys, int (*fds)[2], int i)
{
	int	fork_id;
	int	status;

	fork_id = fork();
	if (fork_id == -1)
		exit_free_error(sys);
	else if (fork_id == 0)
		execute_last_cmd(sys, fds, i);
	else
	{
		waitpid(fork_id, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			free_all(sys);
			exit(ERROR);
		}
		free_all(sys);
		exit(OK);
	}
}

void	process_middle_cmd(t_cmd *sys, int (*fds)[2], int i)
{
	int	fork_id;
	int	status;

	if (pipe(fds[i]) == -1)
		exit_free_error(sys);
	fork_id = fork();
	if (fork_id == -1)
		exit_free_error(sys);
	else if (fork_id == 0)
		execute_middle_cmd(sys, fds, i);
	else
	{
		waitpid(fork_id, &status, 0);
		close(fds[i - 1][0]);
		close(fds[i][1]);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			free_all(sys);
			exit(ERROR);
		}
	}
}
