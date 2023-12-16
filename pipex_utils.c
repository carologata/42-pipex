/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:27:33 by cogata            #+#    #+#             */
/*   Updated: 2023/12/16 17:27:34 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free_all(sys);
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
