/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:40:33 by cogata            #+#    #+#             */
/*   Updated: 2024/01/09 17:40:37 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	char	**envp;
}			t_cmd;

typedef struct s_flags
{
	char	character;
	char	status;
	int		count;
}			t_flags;

typedef struct s_word
{
	char	*s;
	int		count_letters;
	int		i;
	int		j;
}			t_word;

void		fill_args(t_cmd *sys, int argc, char *argv[], int constants);
void		fill_paths(t_cmd *sys, char *envp[]);
void		fill_cmds(t_cmd *sys, int argc, int constants);
void		fill_when_standard(t_cmd *sys, int argc, char **argv, char **envp);
void		fill_when_heredoc(t_cmd *sys, int argc, char **argv, char **envp);
void		free_fill_args(t_cmd *sys, int j);

int			check_access(char *path_name);
void		ft_put_strjoin_fd(char *str1, char *str2, int fd);
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
void		free_cmd_args(t_cmd *sys);
void		free_all(t_cmd *sys);

void		init_quote_structs(t_flags *sing_quote, t_flags *doub_quote);
void		is_quote(t_flags *quote, char c, int count_flag, int *count_word);
void		is_delimiter(int single_count_quote, int double_count_quote,
				int *count_flag, int *count_word);
void		is_word(int *count_word, int *count_flag);
int			ft_modified_count_words(char *s, char delimiter);
void		is_quote_letter(char *first_status, char second_status,
				int *count_letters);
void		check_character(t_flags *sing, t_flags *doub, int *count_letters,
				char c);
void		ft_count_letters(char *s, char **words, char delimiter,
				int count_word);
void		is_quote_init_letter(char **words, t_word *aux, t_flags *first,
				t_flags *second);
void		check_and_init_letters(char **words, t_word *aux, t_flags *sing,
				t_flags *doub);
void		ft_init_modified_words(char *s, char **words, char delimiter,
				int count_word);
char		**ft_split_modified(char *s, char delimiter);

#endif