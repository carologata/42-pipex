/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:28:13 by cogata            #+#    #+#             */
/*   Updated: 2023/12/16 17:28:14 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERROR 1
# define OK 0
# define NOT_FOUND -1
# define R_NOK -2
# define X_NOK -3
# define FOUND 1

typedef struct s_cmd
{
	char	*infile;
	char	*outfile;
	char	***args;
	char	**paths;
	char	**cmd;
	int		count_cmds;
	char	*limiter;
	int		*is_heredoc;
}			t_cmd;

void		fill_args(t_cmd *sys, int argc, char *argv[], int constants);
void		fill_paths(t_cmd *sys, char *envp[]);
void		fill_cmds(t_cmd *sys, int argc, int constants);

void		process_heredoc_cmd(t_cmd *sys, int **fds, int i, int *index);
void		process_first_cmd(t_cmd *sys, int **fds, int i, int *index);
void		process_last_cmd(t_cmd *sys, int **fds, int i, int *index);
void		process_middle_cmd(t_cmd *sys, int **fds, int i, int *index);

void		execute_heredoc_cmd(t_cmd *sys, int **fds, int order, int index);
void		execute_first_cmd(t_cmd *sys, int **fds, int order, int index);
void		execute_middle_cmd(t_cmd *sys, int **fds, int order, int index);
void		execute_last_cmd(t_cmd *sys, int **fds, int order, int index);

void		check_num_args(int argc);
void		free_all(t_cmd *sys);
void		error(void);

#endif
