/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:27:39 by cogata            #+#    #+#             */
/*   Updated: 2023/12/16 17:27:41 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_args(t_cmd *sys, int argc, char *argv[], int constants)
{
	int	i;
	int j;

	i = constants - 1;
	j = 0;
	while (i < argc - 1)
	{
		sys->args[j] = ft_split(argv[i], ' ');
		i++;
		j++;
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

void	fill_cmds(t_cmd *sys, int argc, int constants)
{
	int	i;

	i = constants - 1;
	sys->count_cmds = 0;
	while (i < argc - 1)
	{
		sys->cmd[sys->count_cmds] = ft_strjoin("/", sys->args[sys->count_cmds][0]);
		sys->count_cmds++;
		i++;
	}
}
// ./pipex infile.txt cmd1 cmd2 cmd3 outfile.txt
// ./pipex here_doc LIMITER cmd1 cmd2 cmd3 outfile.txt

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_cmd	sys;
	int		constants;
	int		**fds;
	int		index;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		constants = 4;
		sys.limiter = argv[2];
		sys.is_heredoc = 1;
		fds = malloc((argc - constants) * sizeof(int *));
		i = 0;
		while (i < (argc - constants))
		{
			fds[i] = malloc(2 * sizeof(int));
			i++;
		}
	}
	else
	{
		constants = 3;
		sys.infile = argv[1];
		sys.is_heredoc = 0;
		fds = malloc((argc - constants - 1) * sizeof(int *));
		i = 0;
		while (i < (argc - constants - 1))
		{
			fds[i] = malloc(2 * sizeof(int));
			i++;
		}
	}
	sys.outfile = argv[argc - 1];
	sys.args = malloc((argc - constants) * sizeof(char ***));
	fill_args(&sys, argc, argv, constants);
	fill_paths(&sys, envp);
	sys.cmd = malloc((argc - constants) * sizeof(char *));
	fill_cmds(&sys, argc, constants);
	i = 0;
	index = 0;
	while (i < sys.count_cmds)
	{
		if (i == 0 && sys.is_heredoc)
			process_heredoc_cmd(&sys, fds, i, &index);
		else if (i == 0 && !sys.is_heredoc)
			process_first_cmd(&sys, fds, i, &index);
		else if (i == sys.count_cmds - 1)
			process_last_cmd(&sys, fds, i, &index);
		else
			process_middle_cmd(&sys, fds, i, &index);
		i++;
	}
}
