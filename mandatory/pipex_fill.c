/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:39:43 by cogata            #+#    #+#             */
/*   Updated: 2024/01/09 11:39:48 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_args(t_cmd *sys, int argc, char *argv[], int constants)
{
	int	i;
	int	j;

	i = constants - 1;
	j = 0;
	while (i < argc - 1)
	{
		sys->args[j] = ft_split_modified(argv[i], ' ');
		if (sys->args[j] == NULL)
			free_fill_args(sys, j);
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
		sys->cmd[sys->count_cmds] = ft_strjoin("/",
				sys->args[sys->count_cmds][0]);
		sys->count_cmds++;
		i++;
	}
}

void	fill_when_standard(t_cmd *sys, int argc, char **argv, char **envp)
{
	int	i;

	sys->constant_args = 3;
	sys->infile = argv[1];
	sys->outfile = argv[argc - 1];
	sys->is_heredoc = 0;
	sys->number_of_fds = argc - sys->constant_args - 1;
	sys->fds = malloc(sys->number_of_fds * sizeof(int *));
	i = 0;
	while (i < sys->number_of_fds)
	{
		sys->fds[i] = malloc(2 * sizeof(int));
		i++;
	}
	sys->args = malloc((argc - sys->constant_args) * sizeof(char ***));
	fill_args(sys, argc, argv, sys->constant_args);
	fill_paths(sys, envp);
	sys->cmd = malloc((argc - sys->constant_args) * sizeof(char *));
	fill_cmds(sys, argc, sys->constant_args);
	sys->envp = envp;
}

void	fill_when_heredoc(t_cmd *sys, int argc, char **argv, char **envp)
{
	int	i;

	sys->constant_args = 4;
	sys->limiter = argv[2];
	sys->outfile = argv[argc - 1];
	sys->is_heredoc = 1;
	sys->number_of_fds = argc - sys->constant_args;
	sys->fds = malloc(sys->number_of_fds * sizeof(int *));
	i = 0;
	while (i < sys->number_of_fds)
	{
		sys->fds[i] = malloc(2 * sizeof(int));
		i++;
	}
	sys->args = malloc((argc - sys->constant_args) * sizeof(char ***));
	fill_args(sys, argc, argv, sys->constant_args);
	fill_paths(sys, envp);
	sys->cmd = malloc((argc - sys->constant_args) * sizeof(char *));
	fill_cmds(sys, argc, sys->constant_args);
	sys->envp = envp;
}
