#include "pipex.h"
#include <stdio.h>

void	exec(char *cmd, char **envp)
{
	char	**cmd_parse;
	char	**paths;
	char	*this_path;
	char	*temp;
	int		i;

	cmd_parse = ft_split (cmd, ' ');
	paths = get_paths(envp);
	if (paths == NULL)
		perror("Error (no PATH)");
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		this_path = ft_strjoin(temp, cmd_parse[i]);
		free(temp);
		if (access(this_path, F_OK) == 0)
		{
			if (execve(this_path, cmd_parse, NULL) == -1)
				perror("Error");
		}
		free(this_path);
		i++;
	}
	free_cmd_and_paths(paths, cmd_parse);
	perror("Error");
}

void	child_one_process(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open (argv[1], O_RDONLY);
	if (fd_in < 0)
		perror("Error (input file)");
	if (dup2(fd[1], 1) == -1)
		perror("Error");
	if (dup2(fd_in, 0) == -1)
		perror("Error");
	close(fd[0]);
	close(fd_in);
	close(fd[1]);
	exec(argv[2], envp);
}

void	child_two_process(int *fd, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_out < 0)
		perror("Error (output file)");
	if (dup2(fd[0], 0) == -1)
		perror("Error");
	if (dup2(fd_out, 1) == -1)
		perror("Error");
	close(fd[1]);
	close(fd_out);
	close(fd[0]);
	exec(argv[3], envp);
}

void	pipex(char **argv, char **envp)
{
	int		fd[2];
	int 	status;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		perror("Error");
	pid1 = fork();
	if (pid1 < 0)
		perror("Error");
	if (pid1 == 0)
		child_one_process(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		perror("Error");
	if (pid2 == 0)
		child_two_process(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}

int main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write (1, "Usage : ./pipex infile cmd1 cmd2 outfile\n",
			   ft_strlen("Usage : ./pipex infile cmd1 cmd2 outfile\n"));
		return (0);
	}
	pipex(argv, envp);
	return (0);
}