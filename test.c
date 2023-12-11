#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	char *infile;
	char *cmd1;
	char *cmd2;
	char *outfile;
	int tube[2];
	// int status;

	char **args1;
	char **args2;
	char *cmd1_path;
	char *cmd2_path;

	if(argc == 1)
	{
		printf("Error");
	}
	infile = argv[1];
	outfile = argv[4];

	args1 = ft_split(argv[2], ' ');
	cmd1 = args1[0];
	args2 = ft_split(argv[3], ' ');
	cmd2 = args2[0];

	cmd1_path = "/usr/bin/cat";
	cmd2_path = "/usr/bin/cut";

	int fd_input = open(infile, O_RDONLY);
	int fd_output = open(outfile, O_RDWR);
	pipe(tube);

	//cmd1
	int pid = fork();
	if (pid == 0)
	{
		// close(tube[0]);

		//input
		dup2(fd_input, STDIN_FILENO);
		close(fd_input);
		//output
		dup2(tube[1], STDOUT_FILENO);
		// close(tube[1]);
		// fprintf(stderr, "child 1: %d\n", getpid());
		// fprintf(stderr, "child parent1: %d\n", getppid());
		close(tube[0]);
		write(1, "Hello", 5);
		exit(1);
		// execve(cmd1_path, args1, envp);
	}
	else
	{
		// fprintf(stderr, "parent 1: %d\n", getpid());
		wait(NULL);
		close(tube[1]); //write
						// close(tube[0]); //read
	}
	if (pid != 0)
	{
		pid = fork();
		if (pid == 0)
		{
			// close(tube[1]);

			//input
			dup2(tube[0], STDIN_FILENO);
			// fprintf(stderr, "1\n");

			dup2(fd_output, STDOUT_FILENO);
			// close(tube[0]);
			// fprintf(stderr, "2\n");

			close(fd_output);
			// close(tube[1]);
			// fprintf(stderr, "child 2: %d\n", getpid());
			// fprintf(stderr, "child parent2: %d\n", getppid());
			// fprintf(stderr, "3\n");
			// sleep(5);

			// fprintf(stderr, "4\n");
			// char buffer[500];
			// int bytes_read = read(1, buffer, 10);
			// fprintf(stderr, "aqui: %s\n", buffer);
			if(execve(cmd2_path, args2, envp) == -1)
				fprintf(stderr, "FAILEEEEEED");
			exit(1);
		}
		else
		{
			fprintf(stderr, "parent 2: %d\n", getpid());

			wait(NULL);
		}
	}

	printf("Done");
}