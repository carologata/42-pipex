#include "pipex.h"



int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_cmd	sys;
	char	*env_path;
	int		fork_id;
	int		fds[argc - 4][2];

	// if (argc != 5)
	// {
	// 	perror("Number of arguments is invalid.");
	// 	exit(1);
	// }
	sys.infile = argv[1];
	sys.outfile = argv[argc - 1];
	sys.args = malloc((argc - 3) * sizeof(char ***));
	i = 2;
	while (i < argc - 1)
	{
		sys.args[i - 2] = ft_split(argv[i], ' ');
		i++;
	}
	i = 0;
	while (envp[i] != NULL)
	{
		env_path = ft_strnstr(envp[i], "PATH=", 5);
		if (env_path != NULL)
		{
			sys.paths = ft_split(&env_path[5], ':');
			break ;
		}
		i++;
	}
	sys.cmd = malloc((argc - 3) * sizeof(char *));
	i = 2;
	sys.count_cmds = 0;
	while (i < argc - 1)
	{
		sys.cmd[sys.count_cmds] = ft_strjoin("/", sys.args[sys.count_cmds][0]);
		sys.count_cmds++;
		i++;
	}
	i = 0;
	while (i < sys.count_cmds)
	{
		if (i == 0) 
		{
			pipe(fds[i]);
			fork_id = fork();
			if (fork_id == 0)
				execute_first_cmd(&sys, fds, i);
			else
			{
				wait(NULL);
				close(fds[i][1]);
			}
		}
		else if (i == sys.count_cmds - 1) 
		{
			fork_id = fork();
			if (fork_id == 0)
				execute_last_cmd(&sys, fds, i);
			else
			{
				wait(NULL);
				printf("Done!\n");
			}
		}
		else 
		{
			pipe(fds[i]);
			fork_id = fork();
			if (fork_id == 0)
				execute_middle_cmd(&sys, fds, i);
			else
			{
				wait(NULL);
				close(fds[i - 1][0]);
				close(fds[i][1]);
			}
		}
		i++;
	}
}
