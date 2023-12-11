#include "pipex.h"

void error()
{
    perror("oi");
}

void	execute_first_cmd(t_cmd *sys, int (*fds)[2], int order)
{
	int		i;
	int		fd_in;
	char	*path_name;

	fd_in = open(sys->infile, O_RDONLY);
	if (fd_in < 0)
		error();
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error();
	close(fd_in);
	if (dup2(fds[order][1], STDOUT_FILENO) == -1)
		error();
	close (fds[order][0]);
	i = 0;
	while (sys->paths[i] != NULL)
	{
		path_name = ft_strjoin(sys->paths[i], sys->cmd[order]);
		if (access(path_name, R_OK & W_OK) == 0)
			break ;
		i++;
	}
	if(execve(path_name, sys->args[order], NULL) == -1)
        perror("error");
}

void	execute_middle_cmd(t_cmd *sys, int (*fds)[2], int order)
{
	int		i;
	int		fd_in;
	char	*path_name;

	if (dup2(fds[order - 1][0], STDIN_FILENO) == -1)
		error();
	if (dup2(fds[order][1], STDOUT_FILENO) == -1)
		error();
	close(fds[order][0]);
	i = 0;
	while (sys->paths[i] != NULL)
	{
		path_name = ft_strjoin(sys->paths[i], sys->cmd[order]);
		if (access(path_name, R_OK & W_OK) == 0)
			break ;
		i++;
	}
	execve(path_name, sys->args[order], NULL);
}

void	execute_last_cmd(t_cmd *sys, int (*fds)[2], int order)
{
	int		i;
	int		fd_out;
	char	*path_name;

	if (dup2(fds[order - 1][0], STDIN_FILENO) == -1)
		error();
	fd_out = open(sys->outfile, O_RDWR);
	if (fd_out < 0)
		error();
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		error();
	i = 0;
	while (sys->paths[i] != NULL)
	{
		path_name = ft_strjoin(sys->paths[i], sys->cmd[order]);
		if (access(path_name, R_OK & W_OK) == 0)
			break ;
		i++;
	}
	execve(path_name, sys->args[order], NULL);
}