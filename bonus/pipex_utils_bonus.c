/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:42:01 by cogata            #+#    #+#             */
/*   Updated: 2024/01/20 18:42:02 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_num_args(int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("Number of arguments is invalid.", 2);
		exit(EXIT_FAILURE);
	}
}

void	exit_free_error(t_cmd *sys)
{
	free_all(sys);
	perror("Error");
	exit(EXIT_FAILURE);
}

void	error_file(char *file, t_cmd *sys)
{
	free_all(sys);
	perror(file);
	exit(EXIT_FAILURE);
}

void	free_cmd_args(t_cmd *sys)
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
}

void	free_all(t_cmd *sys)
{
	int	i;

	free_cmd_args(sys);
	i = 0;
	while (sys->paths[i] != NULL)
	{
		free(sys->paths[i]);
		i++;
	}
	free(sys->paths);
	i = 0;
	while (i < sys->number_of_fds)
	{
		free(sys->fds[i]);
		i++;
	}
	free(sys->fds);
	free(sys);
}
