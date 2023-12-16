/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:27:06 by cogata            #+#    #+#             */
/*   Updated: 2023/12/16 17:27:08 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_first_cmd(t_cmd *sys, int (*fds)[2], int order)
{
	int		i;
	int		fd_in;
	char	*path_name;

	fd_in = open(sys->infile, O_RDONLY);
	if (fd_in < 0)
		exit_free_error();
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_free_error();
	close(fd_in);
	if (dup2(fds[order][1], STDOUT_FILENO) == -1)
		exit_free_error();
	close(fds[order][0]);
	path_name = check_paths(sys, order);
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_free_error();
}

void	execute_middle_cmd(t_cmd *sys, int (*fds)[2], int order)
{
	int		i;
	int		fd_in;
	char	*path_name;

	if (dup2(fds[order - 1][0], STDIN_FILENO) == -1)
		exit_free_error();
	if (dup2(fds[order][1], STDOUT_FILENO) == -1)
		exit_free_error();
	close(fds[order][0]);
	path_name = check_paths(sys, order);
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_free_error();
}

void	execute_last_cmd(t_cmd *sys, int (*fds)[2], int order)
{
	int		i;
	int		fd_out;
	char	*path_name;

	if (dup2(fds[order - 1][0], STDIN_FILENO) == -1)
		exit_free_error();
	fd_out = open(sys->outfile, O_RDWR);
	if (fd_out < 0)
		exit_free_error();
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit_free_error();
	path_name = check_paths(sys, order);
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_free_error();
}
