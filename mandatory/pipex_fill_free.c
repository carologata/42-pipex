/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fill_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:42:02 by cogata            #+#    #+#             */
/*   Updated: 2024/01/20 19:42:04 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_fill_args(t_cmd *sys, int j)
{
	int	i;
	int	k;

	i = 0;
	while (i < sys->number_of_fds)
	{
		free(sys->fds[i]);
		i++;
	}
	free(sys->fds);
	i = j - 1;
	while (i >= 0)
	{
		k = 0;
		while (sys->args[i][k] != NULL)
		{
			free(sys->args[i][k]);
			k++;
		}
		free(sys->args[i]);
		i--;
	}
	free(sys->args);
	free(sys);
	exit(EXIT_FAILURE);
}
