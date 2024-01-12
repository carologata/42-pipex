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

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_cmd	*sys;
	int		index;

	check_num_args(argc);
	sys = (t_cmd *)malloc(sizeof(t_cmd));
	if (argv[1] && ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
		fill_when_heredoc(sys, argc, argv, envp);
	else
		fill_when_standard(sys, argc, argv, envp);
	i = 0;
	index = 0;
	while (i < sys->count_cmds)
	{
		if (index == 0 && sys->is_heredoc)
			process_heredoc_cmd(sys, index++);
		else if (index == 0 && !sys->is_heredoc)
			process_first_cmd(sys, i++, index++);
		else if (i == sys->count_cmds - 1)
			process_last_cmd(sys, i++, index++);
		else
			process_middle_cmd(sys, i++, index++);
	}
	free_all(sys);
	return (0);
}
