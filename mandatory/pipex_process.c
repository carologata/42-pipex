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

int	get_exit_status(int status)
{
	int	new;

	new = (status & 0xff00) >> 8;
	return (new);
}

void	process_heredoc_cmd(t_cmd *sys, int index)
{
	int	fork_id;

	if (pipe(sys->fds[index]) == -1)
		exit_free_error(sys);
	fork_id = fork();
	if (fork_id == -1)
		exit_free_error(sys);
	else if (fork_id == 0)
		execute_heredoc_cmd(sys, sys->fds, index);
	else
	{
		wait(NULL);
		close(sys->fds[index][1]);
	}
}

void	process_first_cmd(t_cmd *sys, int i, int index)
{
	int	fork_id;

	if (pipe(sys->fds[index]) == -1)
		exit_free_error(sys);
	fork_id = fork();
	if (fork_id == -1)
		exit_free_error(sys);
	else if (fork_id == 0)
		execute_first_cmd(sys, sys->fds, i, index);
	else
	{
		wait(NULL);
		close(sys->fds[index][1]);
	}
}

void	process_middle_cmd(t_cmd *sys, int i, int index)
{
	int	fork_id;

	if (pipe(sys->fds[index]) == -1)
		exit_free_error(sys);
	fork_id = fork();
	if (fork_id == -1)
		exit_free_error(sys);
	else if (fork_id == 0)
		execute_middle_cmd(sys, sys->fds, i, index);
	else
	{
		wait(NULL);
		close(sys->fds[index - 1][0]);
		close(sys->fds[index][1]);
	}
}

void	process_last_cmd(t_cmd *sys, int i, int index)
{
	int	fork_id;
	int	status;

	fork_id = fork();
	if (fork_id == -1)
		exit_free_error(sys);
	else if (fork_id == 0)
		execute_last_cmd(sys, sys->fds, i, index);
	else
	{
		waitpid(fork_id, &status, 0);
		close(sys->fds[index - 1][0]);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			free_all(sys);
			status = get_exit_status(status);
			exit(status);
		}
	}
}
