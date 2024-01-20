/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:26:53 by cogata            #+#    #+#             */
/*   Updated: 2023/12/16 17:26:57 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_put_strjoin_fd(char *str1, char *str2, int fd)
{
	int		buffer_size;
	char	*buffer;

	if (fd > 0 && str1 != 0 && str2 != 0)
	{
		buffer_size = ft_strlen(str1) + ft_strlen(str2);
		buffer = ft_strjoin(str1, str2);
		write(fd, buffer, buffer_size);
		free(buffer);
	}
	else if (fd > 0 && str1 != 0)
	{
		buffer_size = ft_strlen(str1);
		buffer = str1;
		write(fd, buffer, buffer_size);
	}
}

void	check_status(int status, char *cmd)
{
	char	*cmd_no_slash;

	cmd_no_slash = &cmd[1];
	if (status == NOT_FOUND)
		ft_put_strjoin_fd(cmd_no_slash, ": command not found\n", 2);
	else if (status == R_NOK)
		ft_put_strjoin_fd(cmd_no_slash, ": command not readable\n", 2);
	else
		ft_put_strjoin_fd(cmd_no_slash, ": command not executable\n", 2);
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
