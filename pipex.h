#ifndef PIPEX_H
#define PIPEX_H

#include "./libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct s_cmd
{
	char	*infile;
	char	*outfile;
	char	***args;
	char	**paths;
	char	**cmd;
	int		count_cmds;
}			t_cmd;

#endif 