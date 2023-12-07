#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*infile_name;
	char	*outfile_name;
	char	**args1;
	char	**args2;
	char	*path_env;
	char	**paths;
	int		fork_pid;
	char	*path_name;
	char	*cmd_name;
	int		pipe_id;
	int		fds[2];
	int		fd_infile;
	int		fd_outfile;
	int		fork_id;
	int		i;

	int access_return ;
	if (argc != 5)
	{
		perror("Number of arguments is invalid.");
		exit(1);
	}
	//names
	infile_name = argv[1];
	outfile_name = argv[4];
	args1 = ft_split(argv[2], ' '); //"cat -e"
	args2 = ft_split(argv[3], ' '); //"grep -E"
	//
	//Bin env path
	i = 0;
	while (envp[i] != NULL)
	{
		path_env = ft_strnstr(envp[i], "PATH=", 5);
		if (path_env != NULL)
		{
			paths = ft_split(&path_env[5], ':');
			break ;
		}
		i++;
	}

	//cmd1
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_name = ft_strjoin("/", args1[0]);
		path_name = ft_strjoin(paths[i], cmd_name);
		access_return = access(path_name, R_OK & W_OK);
		if (access_return == 0)
			break ;
		i++;
	}
	if (access_return != 0)
	{
		perror("Access to bin file was denied.");
		exit(1);
	}
	fd_infile = open(infile_name, O_RDONLY);
	if (fd_infile < 0)
	{
		perror("Open file failed.");
		exit(1);
	}
	if (dup2(fd_infile, STDIN_FILENO) == -1)
	{
		perror("Infile dup failed.");
		exit(1);
	}
	pipe_id = pipe(fds);
	if (pipe_id == -1)
	{
		perror("Pipe attempt failed.");
		exit(1);
	}
	if (dup2(fds[1], STDOUT_FILENO) == -1)
	{
		perror("Pipe read dup failed.");
		exit(1);
	}
	//
	
	//fork
	fork_id = fork();
	if (fork_id == 0)
	{
		execve(path_name, args1, envp);
	}
	else
	{
		wait(NULL);
	}
	//end fork

	close(fd_infile);
	close(fds[1]);
	
	//cmd2
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_name = ft_strjoin("/", args2[0]);
		path_name = ft_strjoin(paths[i], cmd_name);
		access_return = access(path_name, R_OK & W_OK);
		if (access_return == 0)
			break ;
		i++;
	}
	if (access_return != 0)
	{
		perror("Access to bin file was denied.");
		exit(1);
	}
	if (dup2(fds[0], STDIN_FILENO) == -1)
	{
		perror("Infile dup failed.");
		exit(1);
	}
	fd_outfile = open(outfile_name, O_RDWR);
	if (fd_outfile < 0)
	{
		perror("Open file failed.");
		exit(1);
	}
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		perror("Outfile dup failed.");
		exit(1);
	}
	//
	fork_id = fork();
	if(fork_id == 0)
	{
		execve(path_name, args2, envp);
	}
	else
	{
		wait(NULL);
	}
}
