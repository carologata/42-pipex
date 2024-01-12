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

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

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
	int		**fds;
	int		constant_args;
	char	*limiter;
	int		is_heredoc;
	int		number_of_fds;
}			t_cmd;

void		fill_args(t_cmd *sys, int argc, char *argv[], int constants);
void		fill_paths(t_cmd *sys, char *envp[]);
void		fill_cmds(t_cmd *sys, int argc, int constants);
void		fill_when_standard(t_cmd *sys, int argc, char **argv, char **envp);
void		fill_when_heredoc(t_cmd *sys, int argc, char **argv, char **envp);

int			check_access(char *path_name);
void		check_status(int status, char *cmd);
char		*check_paths(t_cmd *sys, int order);

void		process_heredoc_cmd(t_cmd *sys, int index);
void		process_first_cmd(t_cmd *sys, int i, int index);
void		process_middle_cmd(t_cmd *sys, int i, int index);
void		process_last_cmd(t_cmd *sys, int i, int index);

void		execute_heredoc_cmd(t_cmd *sys, int **fds, int index);
void		execute_first_cmd(t_cmd *sys, int **fds, int order, int index);
void		execute_middle_cmd(t_cmd *sys, int **fds, int order, int index);
void		execute_last_cmd(t_cmd *sys, int **fds, int order, int index);

void		check_num_args(int argc);
void		exit_free_error(t_cmd *sys);
void		error_file(char *file, t_cmd *sys);
void		free_all(t_cmd *sys);

#endif
