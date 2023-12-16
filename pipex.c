#include "pipex.h"

void	fill_args(t_cmd *sys, int argc, char *argv[])
{
	int	i;

	i = 2;
	while (i < argc - 1)
	{
		sys->args[i - 2] = ft_split(argv[i], ' ');
		i++;
	}
}

void	fill_paths(t_cmd *sys, char *envp[])
{
	int		i;
	char	*env_path;

	i = 0;
	while (envp[i] != NULL)
	{
		env_path = ft_strnstr(envp[i], "PATH=", 5);
		if (env_path != NULL)
		{
			sys->paths = ft_split(&env_path[5], ':');
			return ;
		}
		i++;
	}
}

void	fill_cmds(t_cmd *sys, int argc)
{
	int	i;

	i = 2;
	sys->count_cmds = 0;
	while (i < argc - 1)
	{
		sys->cmd[sys->count_cmds] = ft_strjoin("/",
				sys->args[sys->count_cmds][0]);
		sys->count_cmds++;
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_cmd	sys;
	int		fds[argc - 4][2];

	// check_num_args(argc);
	sys.infile = argv[1];
	sys.outfile = argv[argc - 1];
	sys.args = malloc((argc - 3) * sizeof(char ***));
	fill_args(&sys, argc, argv);
	fill_paths(&sys, envp);
	sys.cmd = malloc((argc - 3) * sizeof(char *));
	fill_cmds(&sys, argc);
	i = 0;
	while (i < sys.count_cmds)
	{
		if (i == 0)
			process_first_cmd(&sys, fds, i);
		else if (i == sys.count_cmds - 1)
			process_last_cmd(&sys, fds, i);
		else
			process_middle_cmd(&sys, fds, i);
		i++;
	}
}
