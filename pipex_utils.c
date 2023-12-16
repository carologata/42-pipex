#include "pipex.h"

void	check_num_args(int argc)
{
	if (argc != 5)
	{
		perror("Number of arguments is invalid.");
		exit(ERROR);
	}
}

void	exit_free_error(t_cmd *sys)
{
	perror("Error");
	free_all(sys);
	exit(ERROR);
}

void	exit_child_error(void)
{
	perror("Error");
	exit(ERROR);
}

void	free_all(t_cmd *sys)
{
	int	i;
	int	j;

	i = 0;
	while (i < sys->count_cmds)
	{
		j = 0;
		while (sys->args[i][j] != NULL)
		{
			free(sys->args[i][j]);
			j++;
		}
		free(sys->cmd[i]);
		free(sys->args[i]);
		i++;
	}
	free(sys->cmd);
	free(sys->args);
	i = 0;
	while (sys->paths[i] != NULL)
	{
		free(sys->paths[i]);
		i++;
	}
	free(sys->paths);
}
