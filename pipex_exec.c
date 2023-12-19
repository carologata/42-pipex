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

void execute_heredoc_cmd(t_cmd *sys, int **fds, int order, int index)
{
	char *gnl_line;

	// close(fds[index - 1][0]); //close read
	gnl_line = get_next_line(0);
	printf("gnl_line: %s\n", gnl_line);
	while(ft_strncmp(gnl_line, sys->limiter, ft_strlen(sys->limiter)) != 0)
	{
		write(fds[index - 1][1], gnl_line, ft_strlen(gnl_line));
		free(gnl_line);
		gnl_line = get_next_line(0);
	}
	free(gnl_line);
	close(fds[index - 1][1]); //close write
	close(fds[index][0]); //close read
	if (dup2(fds[index - 1][0], STDIN_FILENO) == -1)
		exit_free_error(sys);
	if (dup2(fds[index][1], STDOUT_FILENO) == -1)
		exit_free_error(sys);

	exit(OK);
}

void	execute_first_cmd(t_cmd *sys, int **fds, int order, int index)
{
	int		i;
	int		fd_in;
	char	*path_name;

	fd_in = open(sys->infile, O_RDONLY);
	if (fd_in < 0)
		exit_free_error(sys);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_free_error(sys);
	close(fd_in);
	if (dup2(fds[index][1], STDOUT_FILENO) == -1)
		exit_free_error(sys);
	close(fds[index][0]);
	path_name = check_paths(sys, order);
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_free_error(sys);
}

void	execute_middle_cmd(t_cmd *sys, int **fds, int order, int index)
{
	int		i;
	int		fd_in;
	char	*path_name;

	if (dup2(fds[index - 1][0], STDIN_FILENO) == -1)
		exit_free_error(sys);
	if (dup2(fds[index][1], STDOUT_FILENO) == -1)
		exit_free_error(sys);
	close(fds[index][0]);
	path_name = check_paths(sys, order);
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_free_error(sys);
}

void	execute_last_cmd(t_cmd *sys, int **fds, int order, int index)
{
	int		i;
	int		fd_out;
	char	*path_name;

	if (dup2(fds[index - 1][0], STDIN_FILENO) == -1)
		exit_free_error(sys);
	fd_out = open(sys->outfile, O_RDWR);
	if (fd_out < 0)
		exit_free_error(sys);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit_free_error(sys);
	path_name = check_paths(sys, order);
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_free_error(sys);
}
