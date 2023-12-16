#include "pipex.h"

int check_access(char *path_name)
{
	if(access(path_name, F_OK) == 0)
	{
		if(access(path_name, R_OK) == 0)
		{
			if(access(path_name, W_OK) == 0)
			{
				if(access(path_name, X_OK) == 0)
					return (FOUND);
				else
					return(free(path_name), X_NOK);
			}
			else
				return(free(path_name), W_NOK);
		}
		else
			return (free(path_name), R_NOK);
	}
	else
		return (free(path_name), NOT_FOUND);
}

char	*check_paths(t_cmd *sys, int order)
{
	int		i;
	char	*path_name;
	int		status;

	i = 0;
	while (sys->paths[i] != NULL && status == NOT_FOUND)
	{
		path_name = ft_strjoin(sys->paths[i], sys->cmd[order]);
		status = check_access(path_name);
		if(status == FOUND)
			break;
		i++;
	}
	if()


	return (path_name);
}

void	execute_first_cmd(t_cmd *sys, int (*fds)[2], int order)
{
	int		i;
	int		fd_in;
	char	*path_name;

	fd_in = open(sys->infile, O_RDONLY);
	if (fd_in < 0)
		exit_child_error();
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit_child_error();
	close(fd_in);
	if (dup2(fds[order][1], STDOUT_FILENO) == -1)
		exit_child_error();
	close(fds[order][0]);
	path_name = check_paths(sys, order);
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_child_error();
}

void	execute_middle_cmd(t_cmd *sys, int (*fds)[2], int order)
{
	int		i;
	int		fd_in;
	char	*path_name;

	if (dup2(fds[order - 1][0], STDIN_FILENO) == -1)
		exit_child_error();
	if (dup2(fds[order][1], STDOUT_FILENO) == -1)
		exit_child_error();
	close(fds[order][0]);
	path_name = check_paths(sys, order);
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_child_error();
}

void	execute_last_cmd(t_cmd *sys, int (*fds)[2], int order)
{
	int		i;
	int		fd_out;
	char	*path_name;

	if (dup2(fds[order - 1][0], STDIN_FILENO) == -1)
		exit_child_error();
	fd_out = open(sys->outfile, O_RDWR);
	if (fd_out < 0)
		exit_child_error();
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit_child_error();
	path_name = check_paths(sys, order);
	if (execve(path_name, sys->args[order], NULL) == -1)
		exit_child_error();
}
