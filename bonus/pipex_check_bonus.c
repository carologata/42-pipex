/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:17:12 by cogata            #+#    #+#             */
/*   Updated: 2024/01/09 12:17:15 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_access(char *path_name)
{
	if (access(path_name, F_OK) == 0)
	{
		if (access(path_name, R_OK) == 0)
		{
			if (access(path_name, X_OK) == 0)
				return (FOUND);
			else
				return (free(path_name), X_NOK);
		}
		else
			return (free(path_name), R_NOK);
	}
	else
		return (free(path_name), NOT_FOUND);
}

void	check_status(int status, char *cmd)
{
	char	*cmd_no_slash;

	cmd_no_slash = &cmd[1];
	ft_putstr_fd(cmd_no_slash, 2);
	if (status == NOT_FOUND)
		ft_putstr_fd(": command not found\n", 2);
	else if (status == R_NOK)
		ft_putstr_fd(": command not readable\n", 2);
	else
		ft_putstr_fd(": command not executable\n", 2);
}

char	*check_paths(t_cmd *sys, int order)
{
	int		i;
	char	*path_name;
	int		status;

	i = 0;
	status = NOT_FOUND;
	while (sys->paths[i] != NULL && status == NOT_FOUND)
	{
		path_name = ft_strjoin(sys->paths[i], sys->cmd[order]);
		status = check_access(path_name);
		if (status == FOUND)
			break ;
		i++;
	}
	if (status != FOUND)
	{
		check_status(status, sys->cmd[order]);
		return (NULL);
	}
	return (path_name);
}
