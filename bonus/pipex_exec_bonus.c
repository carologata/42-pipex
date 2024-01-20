/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:40:13 by cogata            #+#    #+#             */
/*   Updated: 2024/01/20 18:40:15 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_heredoc_cmd(t_cmd *sys, int **fds, int index)
{
	char	*gnl_line;

	close(fds[index][0]);
	gnl_line = get_next_line(0);
	while (ft_strncmp(gnl_line, sys->limiter, ft_strlen(sys->limiter)) != 0)
	{
		write(fds[index][1], gnl_line, ft_strlen(gnl_line));
		free(gnl_line);
		gnl_line = get_next_line(0);
	}
	free(gnl_line);
	get_next_line(-1);
	close(fds[index][1]);
	free_all(sys);
	exit(EXIT_SUCCESS);
}

void	execute_first_cmd(t_cmd *sys, int **fds, int order, int index)
{
	int		fd_in;
	char	*path_name;

	fd_in = open(sys->infile, O_RDONLY);
	if (fd_in < 0)
		error_file(sys->infile, sys);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fds[index][1], STDOUT_FILENO);
	close(fds[index][0]);
	path_name = check_paths(sys, order);
	if (path_name == NULL)
	{
		free_all(sys);
		exit(127);
	}
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_free_error(sys);
}

void	execute_middle_cmd(t_cmd *sys, int **fds, int order, int index)
{
	char	*path_name;

	if (dup2(fds[index - 1][0], STDIN_FILENO) == -1)
		exit_free_error(sys);
	if (dup2(fds[index][1], STDOUT_FILENO) == -1)
		exit_free_error(sys);
	close(fds[index][0]);
	path_name = check_paths(sys, order);
	if (path_name == NULL)
	{
		free_all(sys);
		exit(127);
	}
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_free_error(sys);
}

void	execute_last_cmd(t_cmd *sys, int **fds, int order, int index)
{
	int		fd_out;
	char	*path_name;

	dup2(fds[index - 1][0], STDIN_FILENO);
	fd_out = open(sys->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		error_file(sys->outfile, sys);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	path_name = check_paths(sys, order);
	if (path_name == NULL)
	{
		free_all(sys);
		exit(127);
	}
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_free_error(sys);
}
